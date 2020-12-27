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

/**
 * TODO: create library
 */

#include <driver/i2c.h>
#include <esp_log.h>
#include <math.h>

#ifndef INA219_ADDRESS
#define INA219_ADDRESS 0x40
#endif

/// I2C master will check ACK
#define ACK_CHECK_EN    0x1
/// I2C master will not check ACK
#define ACK_CHECK_DIS   0x0
/// I2C ACK value
#define ACK_VAL         0x0
/// I2C NACK value
#define NACK_VAL        0x1

enum INA219_REG {
    /// Configuration register
    INA219_REG_CONFIG = 0x00,
    /// Shunt voltage register
    INA219_REG_SHUNT_VOLTAGE = 0x01,
    /// Bus voltage register
    INA219_REG_BUS_VOLTAGE = 0x02,
    /// Power register
    INA219_REG_POWER = 0x03,
    /// Current register
    INA219_REG_CURRENT = 0x04,
    /// Calibration register
    INA219_REG_CALIBRATION = 0x05,
};

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

/// Mask for bus ADC resolution
#define INA219_CONFIG_BUS_ADC_RES_MASK 0x0780

/// Bus ADC resolution
enum INA219_CONFIG_BUS_ADC_RES {
    /// 9-bit bus ADC resolution
    INA219_CONFIG_BUS_ADC_RES_9BIT = 0x0000,
    /// 10-bit bus ADC resolution
    INA219_CONFIG_BUS_ADC_RES_10BIT = 0x0080,
    /// 11-bit bus ADC resolution
    INA219_CONFIG_BUS_ADC_RES_11BIT = 0x0100,
    /// 12-bit bus ADC resolution
    INA219_CONFIG_BUS_ADC_RES_12BIT = 0x0180,
    /// 12-bit bus ADC resolution (2 samples averages)
    INA219_CONFIG_BUS_ADC_RES_12BIT_2S = 0x0480,
    /// 12-bit bus ADC resolution (4 samples averages)
    INA219_CONFIG_BUS_ADC_RES_12BIT_4S = 0x0500,
    /// 12-bit bus ADC resolution (8 samples averages)
    INA219_CONFIG_BUS_ADC_RES_12BIT_8S = 0x0580,
    /// 12-bit bus ADC resolution (16 samples averages)
    INA219_CONFIG_BUS_ADC_RES_12BIT_16S = 0x0600,
    /// 12-bit bus ADC resolution (32 samples averages)
    INA219_CONFIG_BUS_ADC_RES_12BIT_32S = 0x0680,
    /// 12-bit bus ADC resolution (64 samples averages)
    INA219_CONFIG_BUS_ADC_RES_12BIT_64S = 0x0700,
    /// 12-bit bus ADC resolution (128 samples averages)
    INA219_CONFIG_BUS_ADC_RES_12BIT_128S = 0x0780,
};

/// Mask for shunt ADC resolution
#define INA219_CONFIG_SHUNT_ADC_RES_MASK 0x0078

/// Bus ADC resolution
enum INA219_CONFIG_SHUNT_ADC_RES {
    /// 9-bit shunt ADC resolution
    INA219_CONFIG_SHUNT_ADC_RES_9BIT = 0x0000,
    /// 10-bit shunt ADC resolution
    INA219_CONFIG_SHUNT_ADC_RES_10BIT = 0x0008,
    /// 11-bit shunt ADC resolution
    INA219_CONFIG_SHUNT_ADC_RES_11BIT = 0x0010,
    /// 12-bit shunt ADC resolution
    INA219_CONFIG_SHUNT_ADC_RES_12BIT = 0x0018,
    /// 12-bit shunt ADC resolution (2 samples averages)
    INA219_CONFIG_SHUNT_ADC_RES_12BIT_2S = 0x0048,
    /// 12-bit shunt ADC resolution (4 samples averages)
    INA219_CONFIG_SHUNT_ADC_RES_12BIT_4S = 0x0050,
    /// 12-bit shunt ADC resolution (8 samples averages)
    INA219_CONFIG_SHUNT_ADC_RES_12BIT_8S = 0x0058,
    /// 12-bit shunt ADC resolution (16 samples averages)
    INA219_CONFIG_SHUNT_ADC_RES_12BIT_16S = 0x0060,
    /// 12-bit shunt ADC resolution (32 samples averages)
    INA219_CONFIG_SHUNT_ADC_RES_12BIT_32S = 0x0068,
    /// 12-bit shunt ADC resolution (64 samples averages)
    INA219_CONFIG_SHUNT_ADC_RES_12BIT_64S = 0x0070,
    /// 12-bit shunt ADC resolution (128 samples averages)
    INA219_CONFIG_SHUNT_ADC_RES_12BIT_128S = 0x0078,
};

/// Mask for operating mode
#define INA219_CONFIG_MODE_MASK 0x0007

/// Operationg modes
enum INA219_CONFIG_MODE {
    /// Power-down
    INA219_CONFIG_MODE_POWER_DOWN = 0x00,
    /// Shunt voltage, triggered
    INA219_CONFIG_MODE_SHUNT_TRIGGERED = 0x01,
    /// Bus voltage, triggered
    INA219_CONFIG_MODE_BUS_TRIGGERED = 0x02,
    /// Shunt and bus voltage, triggered
    INA219_CONFIG_MODE_SHUNT_AND_BUS_TRIGGERED = 0x03,
    /// ADC off
    INA219_CONFIG_MODE_ADC_OFF = 0x04,
    /// Shunt voltage, continuous
    INA219_CONFIG_MODE_SHUNT_CONTINUOUS = 0x05,
    /// Bus voltage, continuous
    INA219_CONFIG_MODE_BUS_CONTINUOUS = 0x06,
    /// Shunt and bus voltage, continuous
    INA219_CONFIG_MODE_SHUNT_AND_BUS_CONTINUOUS = 0x07,
};

/**
 * Initializes the I2C master
 */
void ina219Init(void);

/**
 * Reads current
 * @return Current
 */
int16_t ina219ReadCurrent();

/**
 * Returns bus voltage in millivolts
 * @return Bus voltage in millivolts
 */
uint16_t ina219ReadBusVoltage();

/**
 * Returns shunt voltage in tens of microvolts
 * @return Shunt voltage in tens of microvolts
 */
int16_t ina219ReadShuntVoltage();

/**
 * Writes calibration data
 */
void ina219WriteCalibration();

/**
 * Writes configuration
 */
void ina219WriteConfiguration();

esp_err_t i2cRead(uint8_t reg, uint8_t *buffer, size_t size);

esp_err_t i2cWrite(uint8_t reg, uint8_t *buffer, size_t size);