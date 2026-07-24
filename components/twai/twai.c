#include <stdio.h>
#include "twai.h"
#include "esp_err.h"
#include "esp_twai.h"

esp_err_t twai_init(twai_node_handle_t *node_hdl, twai_onchip_node_config_t *node_cfg)
{
	// Sets node handle to NULL if not null already
	if (*node_hdl != NULL) {
		*node_hdl = NULL;
	}

	// Twai node config setup
	node_cfg->io_cfg.tx = 4;	// TWAI TX GPIO PIN
	node_cfg->io_cfg.rx = 5;	// TWAI RX GPIO PIN
	node_cfg->bit_timing.bitrate = 500000; // 500 kbps bitrate
	node_cfg->tx_queue_depth = 5; // Transmit queue depth set to 5

#ifndef DEBUG_MODE
	// Node will receive own transmitted msgs if enabled
	node_cfg->flags.enable_loopback = true;
#endif

	// Create a new TWAI controller driver instance
	ESP_ERROR_CHECK(twai_new_node_onchip(node_cfg, node_hdl));

	// Start the TWAI controller
	ESP_ERROR_CHECK(twai_node_enable(*node_hdl));

	return ESP_OK;
}

// TODO: Include twai_frame_t initialization for tx_msg and rx_msg

esp_err_t twai_send()