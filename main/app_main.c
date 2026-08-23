/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_err.h"
#include "esp_log.h"
#include "esp_twai_types.h"
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
  ESP_LOGI(TAG, "twai initialization complete.");

  // WIFI INITIALIZATION
  ESP_LOGI(TAG, "wifi initialization started.");
  // TODO: Add wifi initialization here
  ESP_LOGI(TAG, "wifi initialization complete.");

  while(true) {
    // TODO: Insert sequential loop for now.
  }
}