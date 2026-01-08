/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "display_functions.h"
#include "peripheral_setup.h"






int main() {
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
    }
}
