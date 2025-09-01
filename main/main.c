#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

#include "usb_host.h"
#include "tinyusb_host.h"
#include "ble_mouse.h"

static const char *TAG = "USB2BT_MOUSE";

void app_main(void)
{
    ESP_LOGI(TAG, "Başlatılıyor...");

    // 1. USB Host başlat
    ESP_LOGI(TAG, "USB Host başlatılıyor...");
    ESP_ERROR_CHECK(tuh_init());

    // 2. BLE Mouse başlat
    ESP_LOGI(TAG, "BLE Mouse başlatılıyor...");
    ble_mouse_init();

    while(1) {
        // USB Task
        tuh_task();

        // USB fare raporlarını oku
        usb_mouse_poll();

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
