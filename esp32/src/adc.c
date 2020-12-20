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

#include "adc.h"

/// ADC Channel number
static const adc_channel_t adcChannel = ADC_CHANNEL_0;
/// ADC characteristics
static esp_adc_cal_characteristics_t *adcChars;

void adcInit(void) {
    static adc_atten_t attenuation = ADC_ATTEN_DB_11;
    static adc_bits_width_t width = ADC_WIDTH_BIT_12;
    ESP_ERROR_CHECK(adc1_config_width(width));
    // Sets the range to 0-VDD
    ESP_ERROR_CHECK(adc1_config_channel_atten(adcChannel, attenuation));

    //Characterize ADC
    adcChars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, attenuation, width, ESP_ADC_CAL_VAL_DEFAULT_VREF, adcChars);
}

uint32_t adcReadVoltage() {
    const uint8_t adcSamples = 16;
    const float r1 = 10000;
    const float r2 = 2700;
    uint32_t adcReading = 0;
    // Multisampling
    for (uint8_t i = 0; i < adcSamples; i++) {
        adcReading += adc1_get_raw(adcChannel);
    }
    adcReading /= adcSamples;
    // Converts adcReading to voltage in mV
    return esp_adc_cal_raw_to_voltage(adcReading, adcChars) * (r1 + r2) / r2;
}