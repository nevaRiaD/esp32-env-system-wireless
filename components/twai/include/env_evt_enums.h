/**
 * @file env_evt_enums.h
 * @author Jaycee Alipio (jaycee.alipio@gmail.com)
 * @brief Enums shared between STM32 and ESP32 for CAN ID events
 * @date 2026-08-23
 * 
 */

#ifndef ENV_EVT_ENUMS_H
#define ENV_EVT_ENUMS_H

/**
 * @brief Standard (11-bits) id for TWAI/CAN event struct
 *
 * @note When adding new events, add it in between device status
 *       and error. The indexing is based off of these values
 */
typedef enum {
	EVT_NONE = 0,

	// STM32 events sent to ESP32
	EVT_STM_DEVICE_STATUS,
	EVT_STM_STATS,
	EVT_STM_AUTO_CMD,
	EVT_STM_MANUAL_CMD,
	EVT_STM_ERR,

	// ESP32 events sent to STM32
	EVT_ESP_DEVICE_STATUS,
	EVT_ESP_CMD_ISSUE,
	EVT_ESP_WIFI_ERR,
	EVT_ESP_ERR,
} env_evts_t;

#endif // ENV_EVT_ENUMS_H