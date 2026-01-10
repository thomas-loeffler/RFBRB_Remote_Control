
#include <stdint.h>
#include "tusb.h"
#include "usb_functions.h"


ds4_report ds4; // Global instance of DS4 report struct

static uint8_t count = 0; // count for input report throttling
                          // ie. only update every 10th report



// Runs when device is connected & HID interface is claimed
void tuh_hid_mount_cb(uint8_t dev_addr,
                      uint8_t instance,
                      uint8_t const* desc_report,
                      uint16_t desc_len)
{
    ds4.connected = true;
    
    // Start receiving input reports
    tuh_hid_receive_report(dev_addr, instance);
}




// Runs when device is disconnected
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
{
    ds4.connected = false;
}




// Runs when a HID report is received
void tuh_hid_report_received_cb(uint8_t dev_addr,
                                uint8_t instance,
                                uint8_t const* report,
                                uint16_t len)
{
    count++; // increment report count for throttling

    if (count >= 10){ // only update every 10th report
        ds4.LjoyX = report[1];
        ds4.LjoyY = report[2];
        ds4.RjoyX = report[3];
        ds4.RjoyY = report[4];
        ds4.buttons1 = report[5];
        ds4.buttons2 = report[6];
        ds4.L2 = report[8];
        ds4.R2 = report[9];
        ds4.ready = true;

        count = 0;
    }

    // Request the next report
    tuh_hid_receive_report(dev_addr, instance);
}  
