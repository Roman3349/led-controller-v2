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

#pragma once

#include <driver/i2c.h>

#define INA2019_ADDRESS 0x40

/// Mask for bus voltage range
#define INA219_CONFIG_BUS_VOLTAGE_MASK 0x2000

/// Bus voltage range values
enum INA219_CONFIG_BUS_VOLTAGE {
    /// Bus voltage range 0-16 V
    INA219_CONFIG_BUS_VOLTAGE_16V = 0x0000,
    /// Bus voltage range 0-32 V
    INA219_CONFIG_BUS_VOLTAGE_32V = 0x2000,
};

/// Mask for gain bits
#define INA219_CONFIG_GAIN_MASK 0x1800

/// Gain values
enum INA219_CONFIG_GAIN {
    /// Gain 1, 40mV Range
    INA219_CONFIG_GAIN_1_40MV = 0x0000,
    /// Gain 2, 80mV Range
    INA219_CONFIG_GAIN_2_80MV = 0x0800,
    /// Gain 4, 160mV Range
    INA219_CONFIG_GAIN_4_160MV = 0x1000,
    /// Gain 8, 320mV Range
    INA219_CONFIG_GAIN_8_320MV = 0x1800,
};

/**
 * Initializes the I2C master
 */
void i2cInit(void);