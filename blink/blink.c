/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


 // I think this is the pico SDK library that has all the shortcuts
#include "pico/stdlib.h"
#include "hardware/i2c.h"




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
    
    int ret = i2c_write_blocking(i2c0, 0x3C, buf, 2, false);
    gpio_put(25, true);
    

    if (ret != 2) {
        // handle error
        gpio_put(25, true);
    }
}


void send_i2c_data(uint8_t data) {
    uint8_t buf[2] = {0x40, data};
    int ret = i2c_write_blocking(i2c0, 0x3C, buf, 2, false);
    if (ret != 2) {
        // handle error
        gpio_put(25, true);
    }
}

void clear_display(void) {
    for (int i = 0; i < 128 * 8; i++) { // 128 columns * 8 pages
        send_i2c_data(0x00);
    }
}

void set_col_addr(uint8_t start, uint8_t end) {
    send_i2c_command(0x21); // Column address command
    send_i2c_command(start);
    send_i2c_command(end);
}

void set_page_addr(uint8_t start, uint8_t end) {
    send_i2c_command(0x22); // Page address command
    send_i2c_command(start);
    send_i2c_command(end);
}

void screen_init(void){
    
    send_i2c_command(0xAE); // Display OFF

    send_i2c_command(0xA8); // Set MUX Ratio
    send_i2c_command(0x3F); // sets to 63

    send_i2c_command(0xD3); // Set display offset
    send_i2c_command(0x00); // no offset

    send_i2c_command(0x40); // Set display start line

    send_i2c_command(0xA1); // column address mapped to 127 // Left to right

    send_i2c_command(0xC8); // COM output scan direction // Start top

    send_i2c_command(0xDA); // COM pin hardware configuration
    send_i2c_command(0x12); // 128x64 configuration

    send_i2c_command(0x81); // contrast control
    send_i2c_command(0x7F);

    send_i2c_command(0xA4); // Entire display ON (resume RAM)

    send_i2c_command(0xA6); // Normal display mode

    send_i2c_command(0xD5); // set oscolation frequency
    send_i2c_command(0x80);

    send_i2c_command(0x8D); // set charge pump
    send_i2c_command(0x14); // enable charge pump

    send_i2c_command(0x20); // Set memory addressing mode
    send_i2c_command(0x00); // Horizontal addressing

    send_i2c_command(0xAF); // Display ON

}

void ssd1306_test_display(void){

    set_col_addr(0, 127);
    set_page_addr(0, 7);

    // Write solid pixels across the page
    for (int i = 0; i < 512; i++){
        send_i2c_data(0xFF);     // 8 vertical pixels ON
        send_i2c_data(0x00);     // 8 vertical pixels OFF
    }
    
}






int main() {
    led_init();
    i2c_setup();
    screen_init();
    clear_display();
    ssd1306_test_display();


    while (1) {
        //blinky();
    }
}
