/**
 * @file twai.h
 * @author Jaycee Alipio (jaycee.alipio@gmail.com)
 * @brief TWAI/CAN communication protocol init/send functions
 * @date 2026-08-23
 * 
 */

#ifndef TWAI_H
#define TWAI_H

#include "esp_err.h"
#include "esp_twai_onchip.h"

/**
 * @brief Initializes twai value handles
 *
 * @param[out] node_hdl : ESP TWAI Node handle (same format as CAN)
 * @param[out] node_cfg : ESP TWAI on-chip init structure with pin setup
 *
 * @return Status of execution.
 */
esp_err_t twai_init(twai_node_handle_t *node_hdl, twai_onchip_node_config_t *node_cfg);

/**
 * @brief Sends twai frame to CAN bus for the STM32 to receive tx_frame
 * 
 * @param[in] node_hdl : ESP TWAI Node handle (same format as CAN)
 * @param[in] tx_msg   : Carries id and data for TWAI frame
 * @return esp_err_t : Status of execution
 */
esp_err_t twai_send(twai_node_handle_t *node_hdl, const twai_frame_t *tx_msg);

#endif /* TWAI_H */