#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"

#include "main.h"


static const uint8_t relay_pins[PLANT_NO] = {RELAY_IN0_PIN_NO, RELAY_IN2_PIN_NO, RELAY_IN3_PIN_NO};
static const uint8_t adc_channels[PLANT_NO] = {ADC0_CHANNEL_INPUT, ADC2_CHANNEL_INPUT, ADC3_CHANNEL_INPUT};
static const uint8_t adc_pins[PLANT_NO] = {ADC0_PIN_NO, ADC3_PIN_NO, ADC3_PIN_NO};

static const float thresholds[PLANT_NO] = {PLANT1_THRESHOLD, PLANT2_THRESHOLD, PLANT3_THRESHOLD};


/**
 * Disable relay continuing to water in case of reset.
*/
void reset_relay(void) {
    for (uint8_t i = 0; i < PLANT_NO; i++) {
        gpio_put(relay_pins[i], GPIO_OFF);
    }
}


/**
 * Initialise pins to act in ADC mode.
*/
void adc_pins_init(void) {
    for (uint8_t i = 0; i < PLANT_NO; i++) {
        adc_gpio_init(adc_pins[i]);
    }
}


/**
 * Initialise pins that are connected to the relay.
*/
void relay_pins_init(void) {
    for (uint8_t i = 0; i < PLANT_NO; i++) {
        gpio_init(relay_pins[i]);
        gpio_set_dir(relay_pins[i], GPIO_OUT);
    }
}


/**
 * Initialise and turn on the onboard LED.
*/
void led_pin_init(void) {
    gpio_init(LED_PIN_NO);
    gpio_set_dir(LED_PIN_NO, GPIO_OUT);

    gpio_put(LED_PIN_NO, GPIO_ON);
}


/**
 * Calculate the current moisture as a percentage.
*/
float compute_moisture(uint16_t adc_value) {
    return (SENSOR_MAX - adc_value) / SENSOR_MAX;
}


/**
 * Water a plant by making the corresponding relay pin go high.
*/
void service_plant(uint8_t relay_pin_no) {
    gpio_put(relay_pin_no, GPIO_ON);

    sleep_ms(WATERING_INTERVAL);

    gpio_put(relay_pin_no, GPIO_OFF);
}


/**
 * Callback for the timer interrupt.
*/
bool callback(repeating_timer_t *t) {
    uint16_t adc_value;

    // Check moisture of each plant
    for (uint8_t i = 0; i < PLANT_NO; i++) {
        adc_select_input(adc_channels[i]);
        adc_value = adc_read();

        if (adc_value == ADC_ERROR_RET) {
            printf("Error reading ADC%u!\n", i);
            gpio_put(LED_PIN_NO, GPIO_OFF);
            continue;
        }

        if (compute_moisture(adc_value) < thresholds[i]) {
            printf("ADC%u Value: %u\n", i, adc_value);
            service_plant(relay_pins[i]);
        }

        // float scaled_voltage = adc_value * 3.3 / (1 << 12);
    }

    return true;
}


int main() {
    reset_relay();

    adc_init();
    adc_pins_init();

    repeating_timer_t timer;
    add_repeating_timer_ms(SLEEP_INTERVAL, callback, NULL, &timer);

    while (true) {
        tight_loop_contents();
    }
}