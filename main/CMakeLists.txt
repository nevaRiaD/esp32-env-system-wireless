idf_component_register(SRCS "app_main.c"
                       PRIV_REQUIRES spi_flash esp_driver_twai twai wifi nvs_flash
                       INCLUDE_DIRS "")
