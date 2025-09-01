#include "ble_mouse.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "BLE_MOUSE";

void ble_mouse_init(void)
{
    // Basit BLE HID mouse başlat
    ESP_LOGI(TAG, "BLE Mouse başlatıldı (dummy init)");
    // Burada ESP-IDF BLE HID stack setup yapılacak
}

void ble_mouse_move(int8_t x, int8_t y, int8_t wheel)
{
    // BLE üzerinden X/Y ve scroll gönder
}

void ble_mouse_buttons(uint8_t buttons)
{
    // BLE üzerinden tıklamaları gönder
}
