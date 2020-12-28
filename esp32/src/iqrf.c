/**
 * Copyright 2020 Roman Ondráček <ondracek.roman@centrum.cz>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "iqrf.h"

static const int RX_BUF_SIZE = 1024;

#define TXD_PIN (GPIO_NUM_10)
#define RXD_PIN (GPIO_NUM_9)

void iqrfInit(void) {
    const uart_config_t config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .parity = UART_PARITY_DISABLE,
            .source_clk = UART_SCLK_APB,
            .stop_bits = UART_STOP_BITS_1,
    };
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
}

void uartSend(char *buffer, size_t size) {
    static const char *TX_TASK = "IQRF_TX";
    const int bytes = uart_write_bytes(UART_NUM_1, buffer, size);
    ESP_LOGI(TX_TASK, "Sent %d bytes: '%s'", bytes, buffer);
    ESP_LOG_BUFFER_HEXDUMP(TX_TASK, buffer, bytes, ESP_LOG_INFO);
}

void iqrfRxTask(void *arg) {
    static const char *RX_TAG = "IQRF_RX";
    esp_log_level_set(RX_TAG, ESP_LOG_INFO);
    uint8_t *buffer = malloc(RX_BUF_SIZE + 1);
    while (true) {
        const int bytes = uart_read_bytes(UART_NUM_1, buffer, RX_BUF_SIZE, 1000 / portTICK_RATE_MS);
        if (bytes == 0) {
            continue;
        }
        buffer[bytes] = 0;
        ESP_LOGI(RX_TAG, "Read %d bytes: '%s'", bytes, buffer);
        ESP_LOG_BUFFER_HEXDUMP(RX_TAG, buffer, bytes, ESP_LOG_INFO);
        char *string = (char *) buffer;
        while (string != NULL) {
            iqrfExecute(string);
            string = strchr(string, '\n');
            if (string == NULL || string[1] == '\0') {
                break;
            }
            string++;
        };
    }
    free(buffer);
}

void iqrfExecute(char *buffer) {
    char string[RX_BUF_SIZE + 1];
    strcpy(string, buffer);
    char *end = strchr(string, '\n');
    if (end != NULL) {
        end[0] = '\0';
    }
    if (strcmp(string, "getAdcVoltage") == 0) {
        uint16_t voltage = adcReadVoltage();
        char txBuffer[2] = {(voltage >> 8) & 0xff, voltage & 0xff};
        uartSend(txBuffer, 2);
        return;
    }
    if (strcmp(string, "getInaVoltage") == 0) {
        uint16_t voltage = ina219ReadBusVoltage();
        char txBuffer[2] = {(voltage >> 8) & 0xff, voltage & 0xff};
        uartSend(txBuffer, 2);
        return;
    }
    if (strcmp(string, "getCurrent") == 0) {
        int16_t current = ina219ReadCurrent();
        char txBuffer[2] = {(current >> 8) & 0xff, current & 0xff};
        uartSend(txBuffer, 2);
        return;
    }
    if (strncmp(string, "setChannel,", 8) == 0) {
        uint8_t channel = string[8] - '0';
        if (channel >= LED_CHANNELS) {
            return;
        }
        unsigned long duty = strtoul((char *) &string[10], NULL, 10) * 10;
        ledcSetDutyCycle(channel, duty > 1023 ? 1023 : duty);
        return;
    }
    if (strcmp(string, "getChannels") == 0) {
        char txBuffer[LED_CHANNELS] = {0,};
        for (uint8_t channel = 0; channel < LED_CHANNELS; channel++) {
            uint32_t duty = ledcGetDutyCycle(channel) / 10;
            txBuffer[channel] = duty & 0xff;
        }
        uartSend(txBuffer, LED_CHANNELS);
        return;
    }
    if (strncmp(string, "getChannel,", 8) == 0) {
        uint8_t channel = string[8] - '0';
        if (channel >= LED_CHANNELS) {
            return;
        }
        uint32_t duty = ledcGetDutyCycle(channel) / 10;
        char txBuffer[1] = {duty & 0xff};
        uartSend(txBuffer, 1);
        return;
    }
}
