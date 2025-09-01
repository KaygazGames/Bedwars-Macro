#include "tusb.h"
#include "ble_mouse.h"
#include "esp_log.h"

static const char *TAG = "USB_HOST";

void usb_mouse_poll(void)
{
    tuh_task(); // USB host stack

    for (uint8_t dev_addr = 1; dev_addr <= CFG_TUH_DEVICE_MAX; dev_addr++)
    {
        if (!tuh_hid_mouse_is_mounted(dev_addr)) continue;

        uint8_t buttons;
        int8_t x, y, wheel;

        if (tuh_hid_mouse_read(dev_addr, &buttons, &x, &y, &wheel))
        {
            // BLE Mouse hareketlerini gönder
            ble_mouse_move(x, y, wheel);
            ble_mouse_buttons(buttons);
        }
    }
}
