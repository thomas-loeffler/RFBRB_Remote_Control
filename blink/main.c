/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


 // I think this is the pico SDK library that has all the shortcuts
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "display.h"





void led_init(void) {
    // GP 25 is the on-board LED for the Pico 2
    // set_dir sets the pin to be as an input or output
    gpio_set_dir(25, GPIO_OUT);
    // put sets the pin to high or low
    gpio_put(25, 0);
    // set_function sets the pin to be used as a GPIO pin (SIO = synchronized input/output)
    gpio_set_function(25, GPIO_FUNC_SIO);
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



void i2c_setup(void){
    // Use i2c0, 400 kHz speed
    i2c_init(i2c0, 400 * 1000);

    // Set up the GPIO pins to the I2C function
    gpio_set_function(4, GPIO_FUNC_I2C);   // SDA
    gpio_set_function(5, GPIO_FUNC_I2C);   // SCL

    // Enable pull-ups (typical for I2C)
    gpio_pull_up(4);
    gpio_pull_up(5);
}









int main() {
    led_init();
    i2c_setup();
    screen_init();
    clear_display();
    display_trine_logo();
    send_small_char('A', 0, 0);
    send_small_char('B', 10, 0);
    send_small_char('C', 20, 0);
    send_small_char('D', 30, 0);
    send_small_char('E', 40, 0);
    send_small_char('F', 50, 0);
    send_small_char('G', 60, 0);
    send_small_char('H', 70, 0);
    send_small_char('I', 80, 0);
    send_small_char('J', 90, 0);
    send_small_char('K', 100, 0);
    send_small_char('L', 110, 0);
    send_small_char('M', 120, 0);
    send_small_char('N', 0, 1);
    send_small_char('O', 10, 1);
    send_small_char('P', 20, 1);
    send_small_char('Q', 30, 1);
    send_small_char('R', 40, 1);
    send_small_char('S', 50, 1);
    send_small_char('T', 60, 1);
    send_small_char('U', 70, 1);
    send_small_char('V', 80, 1);
    send_small_char('W', 90, 1);
    send_small_char('X', 100, 1);
    send_small_char('Y', 110, 1);
    send_small_char('Z', 120, 1);
    send_small_char('0', 0, 2);
    send_small_char(1, 10, 2);
    send_small_char(2, 0, 3);
    send_small_char(3, 10, 3);
    send_small_char('4', 0, 4);
    send_small_char('5', 10, 4);
    send_small_char('6', 0, 5);
    send_small_char('7', 10, 5);
    send_small_char('8', 0, 6);
    send_small_char('9', 10, 6);


    send_big_char(0, 20, 6);
    send_big_char(1, 40, 6);
    send_big_char(2, 60, 6);




    while (1) {
        //blinky();
    }
}
