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

#include <driver/ledc.h>
#include <esp_err.h>
#include <esp_log.h>

//#define LED_CHANNELS 6
#define LED_CHANNELS 4

#define LED_STRIP0_GREEN    26
#define LED_STRIP0_RED      25
#define LED_STRIP0_BLUE     33
#define LED_STRIP1_GREEN    32
#define LED_STRIP1_RED      35
#define LED_STRIP1_BLUE     34

#define LEDC_TAG "LEDC"

/**
 * LED Controller channels configuration
 */
extern ledc_channel_config_t ledc_channels[LED_CHANNELS];

/**
 * Initializes LED Controller
 */
void ledcInit(void);

/**
 * Returns the duty cycle of the LED controller channel
 * @param channel LED Controller channel number
 * @return Channel's duty cycle
 */
uint32_t ledcGetDutyCycle(uint8_t channel);

/**
 * Sets the channel's duty cycle
 * @param channel LED Controller channel number
 * @param duty Duty cycle
 */
void ledcSetDutyCycle(uint8_t channel, uint32_t duty);