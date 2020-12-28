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

#include <stdio.h>
#include "sdkconfig.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <esp_spi_flash.h>

#include <esp_err.h>

#include "adc.h"
#include "ble.h"
#include "ina219.h"
#include "iqrf.h"
#include "ledc.h"

/**
 * Prints chip information
 */
void printChipInfo(void) {
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    printf("silicon revision %d, ", chip_info.revision);
    printf("%u MB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded"
                                                         : "external");
    printf("Minimum free heap size: %u bytes\n",
           esp_get_minimum_free_heap_size());
}

void app_main(void) {
    printChipInfo();
    adcInit();
    ledcInit();
    ina219Init();
    iqrfInit();
    bleInit();
    xTaskCreate(iqrfRxTask, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);
    /*while(1) {
        ESP_LOGI("INA219", "Bus voltage: %u mV", ina219ReadBusVoltage());
        ESP_LOGI("INA219", "Shunt voltage: %d0 uV", ina219ReadShuntVoltage());
        ESP_LOGI("INA219", "Current: %d mA", ina219ReadCurrent());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }*/
}