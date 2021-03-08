#include <oled.h>
#include <fpioa.h>
#include <i2c.h>
#include <u8g2.h>
#include <syslog.h>
#include <gpio.h>
#include <gpiohs.h>
#include <stdint.h>
#include <sleep.h>

/* POSSIBLE I2C ADDRES: 0x78 & 0x7A */

static u8g2_kendryte_hal_t  u8g2_kendryte_hal;

void u8g2_kendryte_hal_init(u8g2_kendryte_hal_t u8g2_kendryte_hal_param) {
  u8g2_kendryte_hal = u8g2_kendryte_hal_param;
}

uint8_t u8g2_kendryte_i2c_byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
  LOGI(__func__, "i2c_cb: Received a msg: %d, arg_int: %d, arg_ptr: %p", msg, arg_int, arg_ptr);
  switch(msg) {
    case U8X8_MSG_BYTE_SET_DC: {
      if(u8g2_kendryte_hal.dc != U8G2_KENDRYTE_HAL_UNDEFINED) {
        fpioa_set_function(u8g2_kendryte_hal.dc, FUNC_GPIOHS1);
        gpiohs_set_drive_mode(1, GPIO_DM_OUTPUT);
        gpiohs_set_pin (1, arg_int);
      }
      break;
    }
    case U8X8_MSG_BYTE_INIT: {
			if(u8g2_kendryte_hal.sda == U8G2_KENDRYTE_HAL_UNDEFINED ||
         u8g2_kendryte_hal.scl == U8G2_KENDRYTE_HAL_UNDEFINED) {
        break;
      }
      fpioa_set_function(u8g2_kendryte_hal.scl, FUNC_I2C0_SCLK);
      fpioa_set_function(u8g2_kendryte_hal.sda, FUNC_I2C0_SDA);
      i2c_init(I2C_DEVICE_0, OLED_I2C_ADDR, ADDRESS_LENGTH, OLED_FREQUENCY);
      break;
    }
    case U8X8_MSG_BYTE_SEND: {
      uint8_t *data_ptr = (uint8_t *) arg_ptr;
      i2c_send_data(I2C_DEVICE_0, data_ptr, arg_int);
      break;
    }
    case U8X8_MSG_BYTE_START_TRANSFER: {
      uint8_t i2c_address = u8x8_GetI2CAddress(u8x8);
      uint8_t payload     = i2c_address | I2C_MASTER_WRITE;
      i2c_send_data(I2C_DEVICE_0, &payload, 1);
      break;
    }
    case U8X8_MSG_BYTE_END_TRANSFER: {
      break;
    }
  }
  return 0;
}

uint8_t u8g2_esp32_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
  LOGI(__func__, "i2c_cb: Received a msg: %d, arg_int: %d, arg_ptr: %p", msg, arg_int, arg_ptr);
  switch(msg) {
    case U8X8_MSG_GPIO_AND_DELAY_INIT: {
      if(u8g2_kendryte_hal.dc != U8G2_KENDRYTE_HAL_UNDEFINED) {
        fpioa_set_function(u8g2_kendryte_hal.dc, FUNC_GPIOHS1);
        gpiohs_set_drive_mode(OLED_DC_VPIN, GPIO_DM_OUTPUT);
        gpiohs_set_pin (OLED_DC_VPIN, 0);
      }
      if(u8g2_kendryte_hal.reset != U8G2_KENDRYTE_HAL_UNDEFINED) {
        fpioa_set_function(u8g2_kendryte_hal.reset, FUNC_GPIOHS2);
        gpiohs_set_drive_mode(OLED_RESET_VPIN, GPIO_DM_OUTPUT);
        gpiohs_set_pin (OLED_RESET_VPIN, 0);
			}
      if(u8g2_kendryte_hal.cs != U8G2_KENDRYTE_HAL_UNDEFINED) {
        fpioa_set_function(u8g2_kendryte_hal.cs, FUNC_GPIOHS3);
        gpiohs_set_drive_mode(OLED_CS_VPIN, GPIO_DM_OUTPUT);
        gpiohs_set_pin (OLED_CS_VPIN, 0);
      }
      break;
    }
    case U8X8_MSG_GPIO_RESET: {
      if(u8g2_kendryte_hal.reset != U8G2_KENDRYTE_HAL_UNDEFINED) {
        gpiohs_set_pin (OLED_RESET_VPIN, arg_int);
      }
      break;
    }
    case U8X8_MSG_GPIO_CS: {
      if (u8g2_kendryte_hal.cs != U8G2_KENDRYTE_HAL_UNDEFINED) {
        gpiohs_set_pin (OLED_CS_VPIN, arg_int);
      }
      break;
    }
    case U8X8_MSG_GPIO_I2C_CLOCK: {
      if (u8g2_kendryte_hal.scl != U8G2_KENDRYTE_HAL_UNDEFINED) {}
      break;
    }
    case U8X8_MSG_GPIO_I2C_DATA: {
      if (u8g2_kendryte_hal.sda != U8G2_KENDRYTE_HAL_UNDEFINED) {}
      break;
    }
    case U8X8_MSG_DELAY_MILLI: {
      msleep(arg_int);
      break;
    }
  }
  return 0;
}

void initialize_display() {
  u8g2_kendryte_hal_t u8g2_kendryte_hal = U8G2_KENDRYTE_HAL_DEFAULT;
  u8g2_kendryte_hal.sda = OLED_DATA_PIN;
  u8g2_kendryte_hal.scl = OLED_CLOCK_PIN;
  u8g2_kendryte_hal_init(u8g2_kendryte_hal);
}

void initialize_u8g2(u8g2_t *display_handle) {
  u8g2_Setup_ssd1306_i2c_128x32_univision_f(display_handle, U8G2_R0, u8g2_kendryte_i2c_byte_cb, u8g2_esp32_gpio_and_delay_cb);
  u8x8_SetI2CAddress(&(display_handle->u8x8), 0x78);
  u8g2_InitDisplay(display_handle);
  u8g2_SetPowerSave(display_handle, 0);
  u8g2_ClearBuffer(display_handle);
}
