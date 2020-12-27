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

#include "ina219.h"
#include "../include/ble.h"

void ina219Init(void) {
    i2c_config_t config = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = 21,
            .sda_pullup_en = GPIO_PULLUP_DISABLE,
            .scl_io_num = 22,
            .scl_pullup_en = GPIO_PULLUP_DISABLE,
            .master.clk_speed = 100000,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, config.mode, 0, 0, 0));
    ina219WriteCalibration();
    ina219WriteConfiguration();
    uint8_t configuration[2] = {0,};
    ESP_ERROR_CHECK(i2cRead(INA219_REG_CONFIG, configuration, 2));
    ESP_LOGI("INA219", "Configuration read: ");
    ESP_LOG_BUFFER_HEXDUMP("INA219", &configuration, 2, ESP_LOG_INFO);
    uint8_t calibration[2] = {0,};
    ESP_ERROR_CHECK(i2cRead(INA219_REG_CALIBRATION, calibration, 2));
    ESP_LOGI("INA219", "Calibration read: ");
    ESP_LOG_BUFFER_HEXDUMP("INA219", &calibration, 2, ESP_LOG_INFO);
}

esp_err_t i2cRead(uint8_t reg, uint8_t *buffer, size_t size) {
    if (size == 0) {
        return ESP_OK;
    }
    // Creates and initializes I2C command link
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    // Sends device address
    i2c_master_write_byte(cmd, (INA219_ADDRESS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    // Sends register we want
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    i2c_master_start(cmd);
    // Sends device address
    i2c_master_write_byte(cmd, (INA219_ADDRESS << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
    // Read data
    if (size > 1) {
        i2c_master_read(cmd, buffer, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, buffer + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t i2cWrite(uint8_t reg, uint8_t *buffer, size_t size) {
    // Creates and initializes I2C command link
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    // Sends device address
    i2c_master_write_byte(cmd, (INA219_ADDRESS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    // Sends register we want
    i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    // Writes the data
    i2c_master_write(cmd, buffer, size, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "Could not write to device: %d", ret);
    }
    i2c_cmd_link_delete(cmd);
    return ret;
}

int16_t ina219ReadCurrent() {
    uint8_t buffer[2] = {0,};
    ESP_ERROR_CHECK(i2cRead(INA219_REG_CURRENT, buffer, 2));
    ESP_LOGI("INA219", "Current read: ");
    ESP_LOG_BUFFER_HEXDUMP("INA219", &buffer, 2, ESP_LOG_INFO);
    return ((buffer[0] << 8) | (buffer[1])) / 10;
}

uint16_t ina219ReadBusVoltage() {
    uint8_t buffer[2] = {0,};
    ESP_ERROR_CHECK(i2cRead(INA219_REG_BUS_VOLTAGE, buffer, 2));
    return ((buffer[0] << 5) | (buffer[1] >> 3)) << 2;
}

int16_t ina219ReadShuntVoltage() {
    uint8_t buffer[2] = {0,};
    ESP_ERROR_CHECK(i2cRead(INA219_REG_SHUNT_VOLTAGE, buffer, 2));
    return ((buffer[0] << 8) | (buffer[1]));
}

void ina219WriteCalibration() {
    // VSHUNT_MAX = 0.32 V; RSHUNT = 0.1 Ω
    // MaxPossibleCurrent = VSHUNT_MAX / RSHUNT = 3.2 A
    // MaxExpectedCurrent = 3.2 A
    // MinimumLSB = MaxExpectedCurrent/32767 = 0.000097656 (97.65625uA per bit)
    // MaximumLSB = MaxExpectedCurrent/4096 = 0,00078125 (781.25uA per bit)
    // CurrentLSB = 0.0001 (100uA per bit)
    // Cal = trunc(0.04096 / (CurrentLSB * RSHUNT)) = 4096 (0x1000)
    uint8_t buffer[2] = {0x10, 0x00};
    i2cWrite(INA219_REG_CALIBRATION, buffer, 2);
}

void ina219WriteConfiguration() {
    uint16_t configuration = INA219_CONFIG_BUS_VOLTAGE_16V
            | INA219_CONFIG_GAIN_8_320MV
            | INA219_CONFIG_BUS_ADC_RES_12BIT_4S
            | INA219_CONFIG_SHUNT_ADC_RES_12BIT_128S
            | INA219_CONFIG_MODE_SHUNT_AND_BUS_CONTINUOUS;
    ESP_LOGE("INA219", "Configuration: %x", configuration);
    uint8_t buffer[2] = {configuration >> 8, configuration & 0xff};
    i2cWrite(INA219_REG_CONFIG, buffer, 2);
}