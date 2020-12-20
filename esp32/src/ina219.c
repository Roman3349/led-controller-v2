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

void i2cInit(void) {
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
}