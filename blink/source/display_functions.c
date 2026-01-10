

//////////////////////////////////////
//	           INCLUDES             //
//////////////////////////////////////

// Standard includes / hardware headers
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// File includes
#include "display_functions.h"
#include "display_font.h"




//////////////////////////////////////
//	           FUNCTIONS            //
//////////////////////////////////////


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

    // if ret does nto return 2 (2 bytes written), there was an error
    if (ret != 2) {
        gpio_put(25, true);
    }
}



void send_i2c_data(uint8_t data) {
    // see notes in send_i2c_command
    uint8_t buf[2] = {0x40, data};

    int ret = i2c_write_blocking(i2c0, 0x3C, buf, 2, false);

    if (ret != 2) {
        gpio_put(25, true);
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



void clear_display(void) {
    // Setting window to the entire screen
    set_col_addr(0, 127);   
	set_page_addr(0, 7);

    // writting 0x00 to all locations clears the display
    for (int i = 0; i < 128 * 8; i++) { // 128 columns * 8 pages
        send_i2c_data(0x00);
    }
}



void screen_init(void){
    
    send_i2c_command(0xAE); // Display OFF

    send_i2c_command(0xA8); // Set MUX Ratio
    send_i2c_command(0x3F); // Sets to 63

    send_i2c_command(0xD3); // Set display offset
    send_i2c_command(0x00); // No offset

    send_i2c_command(0x40); // Set display start line

    send_i2c_command(0xA1); // Column address mapped to 127 // Left to right

    send_i2c_command(0xC8); // COM output scan direction // Start top

    send_i2c_command(0xDA); // COM pin hardware configuration
    send_i2c_command(0x12); // 128x64 configuration

    send_i2c_command(0x81); // Contrast control
    send_i2c_command(0x7F);

    send_i2c_command(0xA4); // Entire display ON (resume RAM)

    send_i2c_command(0xA6); // Normal display mode

    send_i2c_command(0xD5); // Set oscolation frequency
    send_i2c_command(0x80);

    send_i2c_command(0x8D); // Set charge pump
    send_i2c_command(0x14); // Enable charge pump

    send_i2c_command(0x20); // Set memory addressing mode
    send_i2c_command(0x00); // Horizontal addressing

    send_i2c_command(0xAF); // Display ON
}


// Obtained from microcontrollers class
void display_trine_logo(void){
	set_col_addr(14, 113);
	set_page_addr(2, 5);
	for (uint16_t i = 0; i<300; i++){
		send_i2c_data(Trine_Logo[i]);
	}
    set_col_addr(14, 113);
	set_page_addr(5, 5);
    for (uint8_t i = 0; i<100; i++){
        send_i2c_data(University_Logo[i]);
    }
}


// The small characters are 5x8 pixels (one page tall)
void send_small_char(int character, uint8_t col, uint8_t page){
    uint8_t index = (uint8_t)character;
    set_col_addr(col, col+5);
    set_page_addr(page, page);
    for (uint8_t i = 0; i<5; i++){
        send_i2c_data(font_8p[index][i]);
    }
}



// The big characters are 8x16 pixels (two pages tall)
void send_big_char(int character, uint8_t col, uint8_t page){
    uint8_t index = (uint8_t)character;
    set_col_addr(col, col+7);
    set_page_addr(page, page+1);
    for (uint8_t i = 0; i<16; i++){
        send_i2c_data(font_16p[index][i]);
    }

}


// The PlayStation symbols are 16x16 pixels (two pages tall)
void send_PS_symbol(int character, uint8_t col, uint8_t page){
    uint8_t index = 0;

    if (character == 'X'){
        index == 0;
    } else if (character == 'S'){
        index = 1;
    } else if (character == 'O'){
        index = 2;
    } else if (character == 'T'){
        index = 3;
    } else {
        index = 4;
    }

    set_col_addr(col, col+15);
    set_page_addr(page, page+1);
    for (uint8_t i = 0; i<32; i++){
        send_i2c_data(PS_symbols[index][i]);
    }
}


void display_all_fonts(void){
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
}