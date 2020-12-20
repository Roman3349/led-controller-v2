#include "ledc.h"

ledc_channel_config_t ledc_channels[LED_CHANNELS] = {
        {
                .channel = LEDC_CHANNEL_0,
                .duty = 0,
                .gpio_num = LED_STRIP0_GREEN,
                .speed_mode = LEDC_HIGH_SPEED_MODE,
                .hpoint = 0,
                .timer_sel = LEDC_TIMER_0,
        },
        {
                .channel = LEDC_CHANNEL_1,
                .duty = 0,
                .gpio_num = LED_STRIP0_RED,
                .speed_mode = LEDC_HIGH_SPEED_MODE,
                .hpoint = 0,
                .timer_sel = LEDC_TIMER_0,
        },
        {
                .channel = LEDC_CHANNEL_2,
                .duty = 0,
                .gpio_num = LED_STRIP0_BLUE,
                .speed_mode = LEDC_HIGH_SPEED_MODE,
                .hpoint = 0,
                .timer_sel = LEDC_TIMER_0,
        },
        {
                .channel = LEDC_CHANNEL_3,
                .duty = 0,
                .gpio_num = LED_STRIP1_GREEN,
                .speed_mode = LEDC_HIGH_SPEED_MODE,
                .hpoint = 0,
                .timer_sel = LEDC_TIMER_0,
        },
        /*{
                .channel = LEDC_CHANNEL_4,
                .duty = 0,
                .gpio_num = LED_STRIP1_RED,
                .speed_mode = LEDC_HIGH_SPEED_MODE,
                .hpoint = 0,
                .timer_sel = LEDC_TIMER_0,
        },
        {
                .channel = LEDC_CHANNEL_5,
                .duty = 0,
                .gpio_num = LED_STRIP1_BLUE,
                .speed_mode = LEDC_HIGH_SPEED_MODE,
                .hpoint = 0,
                .timer_sel = LEDC_TIMER_0,
        },*/
};

void ledcInit(void) {
    // Sets configuration for LED Controller timer
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 5000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
    
    // Sets configuration for LED Controller channels
    for (uint8_t channel = 0; channel < LED_CHANNELS; channel++) {
        printf("Settings LEDC channel #%u\n", channel);
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channels[channel]));
    }
}

void ledcSetDutyCycle(ledc_channel_config_t *channel, uint32_t duty) {
    ESP_ERROR_CHECK(ledc_set_duty(channel->speed_mode, channel->channel, duty));
    ESP_ERROR_CHECK(ledc_update_duty(channel->speed_mode, channel->channel));
}

uint32_t ledcGetDutyCycle(ledc_channel_config_t *channel) {
    return ledc_get_duty(channel->speed_mode, channel->channel);
}