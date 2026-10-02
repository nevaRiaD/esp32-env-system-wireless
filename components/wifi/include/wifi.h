#ifndef WIFI_H
#define WIFI_H

#include "esp_err.h"
#include "esp_wifi.h"

/**
 * @brief Initializes the connection for wifi and sets up wifi init
 *        config variable.
 * 
 * @param[in] config : 
 * @return esp_err_t 
 */
esp_err_t wifi_init(wifi_init_config_t *config);

#endif // WIFI_H