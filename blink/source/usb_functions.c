
#include <stdint.h>
#include "tusb.h"


typedef struct {
    uint8_t LjoyX, LjoyY, RjoyX, RjoyY;
    uint8_t L2, R2;
    uint8_t buttons1, buttons2;
    bool ready;
    bool connected;
} ds4_report_t;

ds4_report_t ds4;

static uint8_t count = 0;



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




// Device disconnected
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
{
    ds4.connected = false;
}




// A HID report is received
void tuh_hid_report_received_cb(uint8_t dev_addr,
                                uint8_t instance,
                                uint8_t const* report,
                                uint16_t len)
{
    count++;

    if (count >= 10){
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
