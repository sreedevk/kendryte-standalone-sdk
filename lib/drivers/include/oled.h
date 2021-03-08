#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <i2c.h>
#include <u8g2.h>

#define OLED_CLOCK_PIN  33
#define OLED_DATA_PIN   34

#define OLED_DC_VPIN      1
#define OLED_RESET_VPIN   2
#define OLED_CS_VPIN      3

#define OLED_I2C_ADDR     0x3C
#define OLED_FREQUENCY  100000
#define ADDRESS_LENGTH    7

#define ACK_CHECK_EN   0x1
#define ACK_CHECK_DIS  0x0

#define U8G2_KENDRYTE_HAL_UNDEFINED (-1)

#define U8G2_KENDRYTE_HAL_DEFAULT {U8G2_KENDRYTE_HAL_UNDEFINED, U8G2_KENDRYTE_HAL_UNDEFINED, U8G2_KENDRYTE_HAL_UNDEFINED, U8G2_KENDRYTE_HAL_UNDEFINED, U8G2_KENDRYTE_HAL_UNDEFINED, U8G2_KENDRYTE_HAL_UNDEFINED, U8G2_KENDRYTE_HAL_UNDEFINED }

typedef struct {
  int8_t clk;
	int8_t mosi;
	int8_t sda;
	int8_t scl;
	int8_t cs;
	int8_t reset;
	int8_t dc;
} u8g2_kendryte_hal_t ;

typedef enum {
  I2C_MASTER_WRITE = 0
} i2c_control_byte_t;

void u8g2_kendryte_hal_init(u8g2_kendryte_hal_t u8g2_kendryte_hal_param);
uint8_t u8g2_kendryte_i2c_byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8g2_esp32_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void initialize_display();
void initialize_u8g2(u8g2_t *display_handle);
