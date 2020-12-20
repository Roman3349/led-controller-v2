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

#include <string.h>
#include <esp_gap_ble_api.h>
#include <esp_gatts_api.h>
#include <esp_gatt_common_api.h>
#include <esp_gatt_defs.h>
#include <esp_log.h>

#include "adc.h"

#define GATTS_TAG "GATTS"

#define GATTS_SERVICE_UUID_TEST_A   0x00FF
#define GATTS_CHAR_UUID_TEST_A      0xFF01
#define GATTS_NUM_HANDLE_TEST_A     4

#define GATTS_SERVICE_UUID_TEST_B   0x00EE
#define GATTS_CHAR_UUID_TEST_B      0xEE01
#define GATTS_NUM_HANDLE_TEST_B     4

#define GATTS_SERVICE_UUID_VOLTAGE  0x183B
#define GATTS_CHAR_UUID_VOLTAGE     0x2B18
#define GATTS_NUM_HANDLE_VOLTAGE    4

/// Device name
#define DEVICE_NAME                 "LED Controller v2.0"
/// Manufacturer data length
#define MANUFACTURER_DATA_LEN       0

#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x40

#define PREPARE_BUF_MAX_SIZE        1024

/**
 * Registers GATTS services
 */
void gatts_register(void);
