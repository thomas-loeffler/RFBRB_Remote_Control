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
    sleep_ms(3000);
    clear_display();
    sleep_ms(500);
    send_small_char('A', 0, 0);
    send_small_char('B', 7, 0);
    send_small_char('C', 14, 0);
    send_small_char('D', 21, 0);
    send_small_char('E', 28, 0);
    send_small_char('F', 35, 0);
    send_small_char('G', 42, 0);
    send_small_char('H', 49, 0);
    send_small_char('I', 56, 0);
    send_small_char('J', 63, 0);
    send_small_char('K', 70, 0);
    send_small_char('L', 77, 0);
    send_small_char('M', 84, 0);
    send_small_char('N', 91, 0);
    send_small_char('O', 98, 0);
    send_small_char('P', 105, 0);
    send_small_char('Q', 112, 0);
    send_small_char('R', 119, 0);
    send_small_char('S', 0, 1);
    send_small_char('T', 7, 1);
    send_small_char('U', 14, 1);
    send_small_char('V', 21, 1);
    send_small_char('W', 28, 1);
    send_small_char('X', 35, 1);
    send_small_char('Y', 42, 1);
    send_small_char('Z', 49, 1);
    send_small_char('0', 56, 1);
    send_small_char('1', 63, 1);
    send_small_char('2', 70, 1);
    send_small_char('3', 77, 1);
    send_small_char('4', 84, 1);
    send_small_char('5', 91, 1);
    send_small_char('6', 98, 1);
    send_small_char('7', 105, 1);
    send_small_char('8', 112, 1);
    send_small_char('9', 119, 1);


    send_big_char('A', 0, 2);
    send_big_char('B', 9, 2);
    send_big_char('C', 18, 2);
    send_big_char('D', 27, 2);
    send_big_char('E', 36, 2);
    send_big_char('F', 45, 2);
    send_big_char('G', 54, 2);
    send_big_char('H', 63, 2);
    send_big_char('I', 72, 2);
    send_big_char('J', 81, 2);
    send_big_char('K', 90, 2);
    send_big_char('L', 99, 2);
    send_big_char('M', 108, 2);
    send_big_char('N', 117, 2);
    send_big_char('O', 0, 4);
    send_big_char('P', 9, 4);
    send_big_char('Q', 18, 4);
    send_big_char('R', 27, 4);
    send_big_char('S', 36, 4);
    send_big_char('T', 45, 4);
    send_big_char('U', 54, 4);
    send_big_char('V', 63, 4);
    send_big_char('W', 72, 4);
    send_big_char('X', 81, 4);
    send_big_char('Y', 90, 4);
    send_big_char('Z', 99, 4);
    send_big_char('0', 107, 4);
    send_big_char('1', 114, 4);
    send_big_char('2', 120, 4);

    send_big_char('3', 0, 6);
    send_big_char('4', 8, 6);
    send_big_char('5', 16, 6);
    send_big_char('6', 24, 6);
    send_big_char('7', 32, 6);
    send_big_char('8', 40, 6);
    send_big_char(':', 54, 6);
    send_big_char('9', 48, 6);

    send_PS_symbol('X', 61, 6);
    send_PS_symbol('S', 78, 6);
    send_PS_symbol('O', 95, 6);
    send_PS_symbol('T', 112, 6);
    
    
    


    while (1) {
        //blinky();
    }
}
