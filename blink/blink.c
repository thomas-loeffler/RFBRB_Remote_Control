/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

 // I think this is the pico SDK library that has all the shortcuts
#include "pico/stdlib.h"
#include "hardware/i2c.h"



// Perform initialization
void led_init(void) {
    // GP 25 is the on-board LED for the Pico 2
    // set_dir sets the pin to be as an input or output
    gpio_set_dir(25, GPIO_OUT);
    // put sets the pin to high or low
    gpio_put(25, 0);
    // set_function sets the pin to be used as a GPIO pin (SIO = synchronized input/output)
    gpio_set_function(25, GPIO_FUNC_SIO);
}

void i2c_setup(void){
    // Use i2c0, 100 kHz speed
    i2c_init(i2c0, 100 * 1000);

    // Set up the GPIO pins to the I2C function
    gpio_set_function(0, GPIO_FUNC_I2C);   // SDA
    gpio_set_function(1, GPIO_FUNC_I2C);   // SCL

    // Enable pull-ups (typical for I2C)
    gpio_pull_up(0);
    gpio_pull_up(1);
}



void blinky(void){
    gpio_put(25, true);
    sleep_ms(200);
    gpio_put(25, false);
    sleep_ms(200);
    gpio_put(25, true);
    sleep_ms(200);
    gpio_put(25, false);
    sleep_ms(200);
    gpio_put(25, true);
    sleep_ms(200);
    gpio_put(25, false);
    sleep_ms(5000);
}



int main() {
    led_init();

    while (1) {
        blinky();
    }
}
