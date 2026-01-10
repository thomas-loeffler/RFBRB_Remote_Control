#pragma once

// Pico SDK provides these
#include "pico/stdlib.h"

// ---- TinyUSB configuration ----
#define CFG_TUSB_MCU              OPT_MCU_RP2040
#define CFG_TUSB_RHPORT0_MODE     OPT_MODE_HOST

// ---- USB Host configuration ----
#define CFG_TUH_ENUMERATION_BUFSIZE 256

// ---- HID Host ----
#define CFG_TUH_HID               1
#define CFG_TUH_HID_EP_BUFSIZE    64

// ---- Disable unused classes ----
#define CFG_TUH_CDC               0
#define CFG_TUH_MSC               0
#define CFG_TUH_MIDI              0
#define CFG_TUH_VENDOR            0
