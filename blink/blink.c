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
    gpio_set_function(0, GPIO_FUNC_I2C);   // SDA
    gpio_set_function(1, GPIO_FUNC_I2C);   // SCL

    // Enable pull-ups (typical for I2C)
    gpio_pull_up(0);
    gpio_pull_up(1);
}



void send_i2c_command(uint8_t cmd) {

    // first byte of the buffer is 0x00 for the control byte (signifying a command)
    // Bit 7	= Co (Continuation)     Co = 0 → last byte in a transmission (or just sending one command)
    //                                  Co = 1 → more bytes to follow (for sending multiple commands in one I²C write)
    // Bit 6	= D/C (Data/Command)    D/C = 0 → the next byte is a command
    //                                  D/C = 1 → the next byte is data
    // Bit 5-0	 = ignored, must be 0
    uint8_t buf[2] = {0x00, cmd};

    // i2c_write_blocking sends a byte, taking care of start and stop conditions
    // argument 1: which i2c peripheral 
    // argument 2: device adress
    // argument 3: pointer to the buffer of bytes you want to send
    // argument 4: number of bytes in the array
    // argument 5: false at the end means a stop condition will be sent
    // returns number of bytes written, should be 2
    int ret = i2c_write_blocking(i2c0, 0x03, buf, 2, false);
    if (ret != 2) {
        // handle error
    }
}


void send_i2c_data(uint8_t data) {
    uint8_t buf[2] = {0x40, data};
    int ret = i2c_write_blocking(i2c0, 0x03, buf, 2, false);
    if (ret != 2) {
        // handle error
    }
}

void clear_display(void) {
    for (int i = 0; i < 128 * 8; i++) { // 128 columns * 8 pages
        send_data(0x00);
    }
}

void set_col_addr(uint8_t start, uint8_t end) {
    send_command(0x21); // Column address command
    send_command(start);
    send_command(end);
}

void set_page_addr(uint8_t start, uint8_t end) {
    send_command(0x22); // Page address command
    send_command(start);
    send_command(end);
}






int main() {
    led_init();

    while (1) {
        blinky();
    }
}
