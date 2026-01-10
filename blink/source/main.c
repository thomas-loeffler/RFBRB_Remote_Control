/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "tusb.h"

#include "display_functions.h"
#include "peripheral_setup.h"





int main() {


    tuh_init(0);  // Initialize USB host stack


    onboard_led_setup();
    i2c_setup();

    screen_init();

    clear_display();
    display_trine_logo();
    sleep_ms(3000);
    clear_display();
    sleep_ms(500);

    void display_all_fonts(void);
    

    while (1) {
        // simple cycle
        //tuh_task();  // REQUIRED: USB host polling
        //process_usb_report();
        //update_display();
        //
    }
}
