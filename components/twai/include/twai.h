#ifndef TWAI_H
#define TWAI_H

#include "esp_err.h"
#include "esp_twai.h"
#include "esp_twai_onchip.h"

/**
 * @brief Creates a twai instance using handle and node_cfg
 *
 * @param[in] node_hdl : Pass a null instance of node_hdl for handle
 * @param[out] node_cfg : Creates cfg of twai instance for onchip
 *
 * @return Status of execution
*/
esp_err_t twai_init(twai_node_handle_t *node_hdl, twai_onchip_node_config_t *node_cfg);



#endif /* TWAI_H */