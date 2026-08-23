#include <stdio.h>
#include "twai.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_log_args.h"
#include "esp_twai.h"
#include "esp_twai_types.h"
#include "env_evt_enums.h"
#include <stdint.h>

#define TWAI_LOOPBACK_ENABLED 1

static const char *TAG = "TWAI";

// STATIC FUNCTION PROTOTYPES

/**
 * @brief Event handler that activates from twai rx_msg from ISR
 * 
 * @param handle   : 
 * @param edata    : 
 * @param user_ctx : 
 * @return true  : Message successfully received and sent to Raspberry Pi
 * @return false : Message did not successfully receive
 */
static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx);


esp_err_t twai_init(twai_node_handle_t *node_hdl, twai_onchip_node_config_t *node_cfg)
{
	// Checks if pointers are NULL
	if (!node_hdl || !node_cfg) {
		ESP_LOGE(TAG, "twai_init: Parameter pointer arguments are NULL.");
		return ESP_ERR_INVALID_ARG;
	}

	// Twai node config setup
	node_cfg->io_cfg.tx = 4;							 // TWAI TX GPIO PIN
	node_cfg->io_cfg.rx = 5;							 // TWAI RX GPIO PIN
	node_cfg->bit_timing.bitrate = 500000; // 500 kbps bitrate
	node_cfg->tx_queue_depth = 5; 				 // Transmit queue depth set to 5

#ifdef TWAI_LOOPBACK_ENABLED
	// Node will receive own transmitted msgs if enabled
	ESP_LOGI(TAG, "twai_init: Loopback is enabled.");
	node_cfg->flags.enable_loopback = true;
#else // TWAI_LOOPBACK_DISABLED
	ESP_LOGI(TAG, "twai_init: Loopback is disabled.");
	node_cfg->flags.enable_loopback = false;
#endif
	// Create a new TWAI controller driver instance
	ESP_ERROR_CHECK(twai_new_node_onchip(node_cfg, node_hdl));

	// Register event call backs for rx_msg's before starting controller
	twai_event_callbacks_t user_cbs = {
    .on_rx_done = twai_rx_cb,
	};
	ESP_ERROR_CHECK(twai_node_register_event_callbacks(*node_hdl, &user_cbs, NULL));

	// Start the TWAI controller
	ESP_ERROR_CHECK(twai_node_enable(*node_hdl));
	ESP_LOGI(TAG, "twai_init: TWAI controller started.");

	return ESP_OK;
}


esp_err_t twai_send(twai_node_handle_t *node_hdl, const twai_frame_t *tx_msg)
{
	// Check if pointers are NULL
	if (!node_hdl || !tx_msg) {
		ESP_LOGE(TAG, "twai_send: Parameter pointer arguments are NULL.");
		return ESP_ERR_INVALID_ARG;
	}

	// Check if buffer length is valid
	if (tx_msg->buffer_len > 8 || tx_msg->buffer_len == 0) {
		ESP_LOGE(TAG, 
			"twai_send: Buffer Length:%i is invalid, needs to be 0 <-> 8.",
			tx_msg->buffer_len
		);
		return ESP_ERR_INVALID_SIZE;
	}

	// Check if ID is part of ESP messages
	if (tx_msg->header.id < EVT_ESP_DEVICE_STATUS || tx_msg->header.id > EVT_ESP_ERR) {
		ESP_LOGE(TAG, 
			"twai_send: id:%i is invalid, needs to be part of ESP enums for sending.",
			tx_msg->header.id
		);
		return ESP_ERR_INVALID_ARG;
	}

	// Timeout = 0: returns immediately if queue is full
	ESP_ERROR_CHECK(twai_node_transmit(*node_hdl, tx_msg, 0));

	// Wait for transmission to finish
	ESP_ERROR_CHECK(twai_node_transmit_wait_all_done(*node_hdl, -1));

	ESP_LOGI(TAG, "twai_send: Successfully transmitted tx_msg.");

	return ESP_OK;
}


// STATIC FUNCTION DEFINITIONS

static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx)
{
	// Return if pointers are NULL
	if (!edata || !user_ctx) {
		ESP_LOGE(TAG, "twai_rx_cb: Parameter pointer arguments are NULL.");
		return false;
	}

	uint8_t recv_buff[8];
	twai_frame_t rx_frame = {
		.buffer = recv_buff,
		.buffer_len = sizeof(recv_buff),
	};

	if (ESP_OK != twai_node_receive_from_isr(handle, &rx_frame)) {
		ESP_LOGE(TAG, "twai_rx_cb: Messaged received from twai ISR failed.");
		return false;
	}

	ESP_LOGI(TAG, "twai_rx_cb: Received message from STM32.");

	// Return false if event id is not part of STM32 enums
	if (rx_frame.header.id < EVT_STM_DEVICE_STATUS || rx_frame.header.id > EVT_STM_ERR) {
		ESP_LOGE(TAG, 
			"twai_send: id:%i is invalid, needs to be part of ESP enums for sending.",
			rx_frame.header.id
		);
		return false;
	}

	// Send rx_msg from STM32 wirelessly to Raspberry Pi
	// TODO: Implement WIFI

	ESP_LOGI(TAG, "twai_rx_cb: Successfully received TWAI msg and sent to Raspberry Pi wirelessly.");
	return true;
}