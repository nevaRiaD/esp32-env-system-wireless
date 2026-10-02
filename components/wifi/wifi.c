#include "wifi.h"
#include "esp_err.h"
#include "esp_wifi.h"

esp_err_t wifi_init(wifi_init_config_t *config)
{
	if (config == NULL) return ESP_ERR_INVALID_ARG;

	WIFI_INIT_CONFIG_DEFAULT(config);
	esp_wifi_init

	return ESP_OK;
}

