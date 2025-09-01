#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "usb_host.h"
#include "ble_mouse.h"

static const char *TAG = "BedwarsMacro";

void app_main(void)
{
    ESP_LOGI(TAG, "Başlatılıyor...");

    // USB Host başlat
    ESP_LOGI(TAG, "USB Host başlatılıyor...");
    usb_host_init();

    // BLE Mouse başlat
    ESP_LOGI(TAG, "BLE Mouse başlatılıyor...");
    ble_mouse_init();

    while(1) {
        // USB fareyi oku ve BLE üzerinden gönder
        usb_mouse_poll();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
