#pragma once
#include <stdint.h>

#define OV2640_ADDR         0x60

int ov2640_init(void);
int ov2640_read_id(uint16_t *manuf_id, uint16_t *device_id);
