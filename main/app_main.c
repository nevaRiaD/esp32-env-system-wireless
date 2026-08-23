/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_twai_types.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "twai.h"

static const char *TAG = "MAIN";

void app_main(void)
{
  ESP_LOGI(TAG, "app_main: started.");

  // TWAI INITIALIZATION
  ESP_LOGI(TAG, "app_main: twai initialization started.");
  twai_node_handle_t twai_hdl;
  twai_onchip_node_config_t twai_cfg;
  esp_err_t status = twai_init(&twai_hdl, &twai_cfg);
  if (status != ESP_OK) {
    ESP_LOGE(TAG, "app_main: twai initialization was unsuccessful.");
    ESP_LOGI(TAG, "app_main: ending program.");
    return;
  }
  ESP_LOGI(TAG, "app_main: twai initialization complete.");

  // WIFI INITIALIZATION
  ESP_LOGI(TAG, "app_main: wifi initialization started.");
  // TODO: Add wifi initialization here
  ESP_LOGI(TAG, "app_main: wifi initialization complete.");

  while(true) {
    // TODO: Insert sequential loop for now.
  }
}