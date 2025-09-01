#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "usb_host.h"
#include "ble_mouse.h"

static const char *TAG = "BedwarsMacro";

void app_main(void)
{
    ESP_LOGI(TAG, "Başlatılıyor...");

    usb_host_init();
    ble_mouse_init();

    while(1){
        usb_mouse_poll();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
