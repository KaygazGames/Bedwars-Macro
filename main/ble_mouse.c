#include "ble_mouse.h"
#include "esp_log.h"
#include "nimble/nimble_port.h"
#include "host/ble_hs.h"
#include "host/util/util.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "esp_nimble_hci.h"

static const char *TAG = "BLE_MOUSE";

static uint16_t conn_handle = 0;
static uint8_t mouse_report[4]; // buttons, x, y, wheel

static void ble_app_on_sync(void)
{
    struct ble_gap_adv_params adv_params;
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC, NULL, 0, &adv_params, NULL, NULL);
    ESP_LOGI(TAG, "BLE Advertising başladı");
}

static int ble_gap_event(struct ble_gap_event *event, void *arg)
{
    switch(event->type)
    {
        case BLE_GAP_EVENT_CONNECT:
            if(event->connect.status == 0){
                conn_handle = event->connect.conn_handle;
                ESP_LOGI(TAG,"BLE bağlandı: %d", conn_handle);
            }
            break;
        case BLE_GAP_EVENT_DISCONNECT:
            conn_handle = 0;
            ESP_LOGI(TAG,"BLE bağlantı kesildi");
            ble_app_on_sync();
            break;
        default:
            break;
    }
    return 0;
}

void ble_mouse_init(void)
{
    ESP_LOGI(TAG, "BLE HID Mouse başlatılıyor...");
    esp_nimble_hci_and_controller_init();
    nimble_port_init();

    ble_hs_cfg.sync_cb = ble_app_on_sync;
    ble_hs_cfg.gatts_register_cb = NULL;
    ble_hs_cfg.gatts_enable = NULL;
}

static void ble_send_report(void)
{
    if(conn_handle != 0){
        struct os_mbuf *om = ble_hs_mbuf_from_flat(mouse_report, sizeof(mouse_report));
        ble_gattc_notify_custom(conn_handle, 0x0011, om); // 0x0011 = HID rapor char handle (örnek)
    }
}

void ble_mouse_move(int8_t x, int8_t y, int8_t wheel)
{
    mouse_report[1] = x;
    mouse_report[2] = y;
    mouse_report[3] = wheel;
    ble_send_report();
}

void ble_mouse_buttons(uint8_t buttons)
{
    mouse_report[0] = buttons;
    ble_send_report();
}
