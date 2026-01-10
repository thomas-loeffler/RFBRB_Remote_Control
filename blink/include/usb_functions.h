

#include <stdint.h>

// Struct containing all DS4 controller inputs
typedef struct {
    uint8_t LjoyX, LjoyY, RjoyX, RjoyY; // Analog stick positions
    uint8_t L2, R2;                     // Trigger positions
    uint8_t buttons1, buttons2;         // All button states (facebuttons, dpad, bumpers, stick-click, share, options, ps, touchpad)
    bool ready;                         // for tracking if new data is available/ready to be processed
    bool connected; // for tracking connection status (displayed on screen)
} ds4_report;

extern ds4_report ds4; // Global instance of DS4 report struct



void tuh_hid_mount_cb(uint8_t dev_addr,
                      uint8_t instance,
                      uint8_t const* desc_report,
                      uint16_t desc_len);

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance);

void tuh_hid_report_received_cb(uint8_t dev_addr,
                                uint8_t instance,
                                uint8_t const* report,
                                uint16_t len);

