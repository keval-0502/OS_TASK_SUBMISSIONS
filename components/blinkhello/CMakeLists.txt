idf_component_register(SRCS "blinkhello.c"
                       INCLUDE_DIRS "include"
                       REQUIRES nvs_flash driver
                       )