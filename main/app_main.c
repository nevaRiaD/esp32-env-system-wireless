/**
 * @file app_main.c
 * @author Jaycee Alipio (jaycee.alipio@gmail.com)
 * @brief Sends/receives messages wirelessly from Raspberry Pi to send to STM32
 * @date 2026-08-23
 *
 */

#include "esp_err.h"
#include "esp_log.h"
#include "esp_twai_types.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "twai.h"

static const char *TAG = "APP_MAIN";

void app_main(void)
{
  ESP_LOGI(TAG, "started.");

  // TWAI INITIALIZATION
  ESP_LOGI(TAG, "twai initialization started.");

  twai_node_handle_t twai_hdl;
  twai_onchip_node_config_t twai_cfg;
  esp_err_t status = twai_init(&twai_hdl, &twai_cfg);
  if (status != ESP_OK) {
    ESP_LOGE(TAG, "twai initialization was unsuccessful.");
    ESP_LOGI(TAG, "ending program.");
    return;
  }

  // WIFI INITIALIZATION
  ESP_LOGI(TAG, "wifi initialization started.");
  wifi_init_config_t wifi_cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&wifi_cfg));
  ESP_LOGI(TAG, "wifi initialization complete.");

  while(true) {
    // TODO: Insert sequential loop for now.
  }
}