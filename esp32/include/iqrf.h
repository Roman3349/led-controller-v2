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

#include <driver/gpio.h>
#include <driver/uart.h>
#include <string.h>
#include <stdlib.h>
#include <esp_log.h>

#include "adc.h"
#include "ledc.h"

/**
 * Initializes UART connection to IQRF module
 */
void iqrfInit(void);

/**
 * Receive task
 * @param arg Argument
 */
void iqrfRxTask(void *arg);

/**
 * Sends data over UART
 * @param buffer Data to send
 * @param size Size of data to send
 */
void uartSend(char *buffer, size_t size);
