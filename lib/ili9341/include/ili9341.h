#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fpioa.h>
#include <spi.h>

#define ILI9314_DEFAULT_WIDTH  240
#define ILI9314_DEFAULT_HEIGHT 320

#define ILI9341_DEFAULT_XOFFSET 0
#define ILI9341_DEFAULT_YOFFSET 0

#define ILI9341_DEFAULT_DC_FUNC    FUNC_GPIOHS1
#define ILI9341_DEFAULT_CS_FUNC    FUNC_SPI0_SS0
#define ILI9341_DEFAULT_RES_FUNC   FUNC_GPIOHS3
#define ILI9341_DEFAULT_BL_FUNC    FUNC_GPIOHS4
#define ILI9341_DEFAULT_SCLK_FUNC  FUNC_SPI0_SCLK
#define ILI9341_DEFAULT_MOSI_FUNC  FUNC_SPI0_D0
#define ILI9341_DEFAULT_SPI_DEVICE SPI_DEVICE_0

#define ILI9341_DEFAULT_SPI_FRAME_FORMAT SPI_FF_STANDARD
#define ILI9341_DEFAULT_SPI_WORK_MODE    SPI_WORK_MODE_0

#define ILI9341_INIT_HAL(x) ili9341_display_t x = { \
  .width          = ILI9314_DEFAULT_WIDTH,   \
  .height         = ILI9314_DEFAULT_HEIGHT,  \
  .x_offset       = ILI9341_DEFAULT_XOFFSET, \
  .y_offset       = ILI9341_DEFAULT_YOFFSET, \
  .sclk           = -1,  \
  .mosi           = -1,  \
  .reset          = -1,  \
  .cs             = -1,  \
  .bl             = -1,  \
  .dc             = -1,  \
  .dc_io_func     = ILI9341_DEFAULT_DC_FUNC,    \
  .cs_io_func     = ILI9341_DEFAULT_CS_FUNC,    \
  .bl_io_func     = ILI9341_DEFAULT_BL_FUNC,    \
  .reset_io_func  = ILI9341_DEFAULT_RES_FUNC,   \
  .sclk_io_func   = ILI9341_DEFAULT_SCLK_FUNC,  \
  .mosi_io_func   = ILI9341_DEFAULT_MOSI_FUNC,  \
  .spi_device     = ILI9341_DEFAULT_SPI_DEVICE  \
}

typedef enum {
  RED    = 0XF800,
  GREEN  = 0X07E0,
  BLUE	 = 0X001F,
  BLACK	 = 0x0000,
  WHITE  = 0XFFFF,
  GRAY	 = 0X8C51,
  YELLOW = 0xFFE0,
  CYAN   = 0x07FF,
  PURPLE = 0xF81F
} ili9341_color_t;

typedef enum {
  DIRECTION_0   = 0,
  DIRECTION_90  = 1,
  DIRECTION_180 = 2,
  DIRECTION_270 = 3
} ili9341_direction_t;

typedef enum {
  ILI9341_SPI_COMMAND_MODE = 0,
  ILI9341_SPI_DATA_MODE    = 1
} ili9341_spi_write_mode_t;

typedef enum {
  ILI9341_SET_POWER_1         = 0xC0,
  ILI9341_SET_POWER_2         = 0xC1,
  ILI9341_SET_VCOMM_1         = 0xC5,
  ILI9341_SET_MEM_ACC         = 0x36,
  ILI9341_SET_INTRF_MOD       = 0xB0,
  ILI9341_SET_FRAME_RATE      = 0xB1,
  ILI9341_SET_DISPLAY_INV     = 0xB4,
  ILI9341_SET_DISPLAY_FUNC    = 0xB6,
  ILI9341_SET_ENTRY_MODE      = 0xB7,
  ILI9341_SET_INTRF_PIX_FRMT  = 0x3A,
  ILI9341_ADJ_CTRL_3          = 0xF7,
  ILI9341_SLEEP_OUT           = 0x11,
  ILI9341_SET_DISPLAY_ON      = 0x29,
  ILI9341_SET_DISPLAY_OFF     = 0x28,
  ILI9341_SET_INVERSION_OFF   = 0x20,
  ILI9341_SET_INVERSION_ON    = 0x21,
  ILI9341_SET_COLUMN_ADDR     = 0x2A,
  ILI9341_SET_PAGE_ADDR       = 0x2B, 
  ILI9341_MEM_WRITE           = 0x2C, 
} ili9341_cmd_t;

typedef enum {
  ILI9341_FR_61_HZ   = 0x1F,
  ILI9341_FR_63_HZ   = 0x1E,
  ILI9341_FR_65_HZ   = 0x1D,
  ILI9341_FR_68_HZ   = 0x1C,
  ILI9341_FR_70_HZ   = 0x1B,
  ILI9341_FR_73_HZ   = 0x1A,
  ILI9341_FR_76_HZ   = 0x19,
  ILI9341_FR_79_HZ   = 0x18,
  ILI9341_FR_83_HZ   = 0x17,
  ILI9341_FR_86_HZ   = 0x16,
  ILI9341_FR_90_HZ   = 0x15,
  ILI9341_FR_95_HZ   = 0x14,
  ILI9341_FR_100_HZ  = 0x13,
  ILI9341_FR_106_HZ  = 0x12,
  ILI9341_FR_112_HZ  = 0x11,
  ILI9341_FR_119_HZ  = 0x10
} ili9341_frame_rate_t;

typedef struct {
  uint16_t width;
  uint16_t height;
  uint16_t x_offset;
  uint16_t y_offset;
  /* physical GPIO Connections */
  int8_t  sclk;
  int8_t  mosi;
  int8_t  reset;
  int8_t  cs;
  int8_t  bl;
  int8_t  dc;

  /* GPIO Connection Functions */
  fpioa_function_t dc_io_func;
  fpioa_function_t cs_io_func;
  fpioa_function_t bl_io_func;
  fpioa_function_t reset_io_func;
  fpioa_function_t sclk_io_func;
  fpioa_function_t mosi_io_func;

  spi_device_num_t spi_device;
} ili9341_display_t;


/* SPI Device Communication Functions  */
ili9341_display_t ili9341_init_hal_struct(int8_t sclk, int8_t mosi, int8_t reset, int8_t cs, int8_t dc, int8_t bl);
void ili9341_comm_init(ili9341_display_t *dev);

bool ili9341_spi_master_write_byte(ili9341_display_t *dev, uint8_t *data, size_t datasize);

bool ili9341_spi_master_write_comm_byte(ili9341_display_t *dev, uint8_t command);
bool ili9341_spi_master_write_comm_word(ili9341_display_t *dev, uint16_t command);

bool ili9341_spi_master_write_data_byte(ili9341_display_t *dev, uint8_t data);
bool ili9341_spi_master_write_data_word(ili9341_display_t *dev, uint16_t data);

bool ili9341_spi_master_write_addr(ili9341_display_t *dev, uint16_t addr_1, uint16_t addr_2);

bool ili9341_spi_master_write_color(ili9341_display_t *dev, uint16_t color, uint16_t size);
bool ili9341_spi_master_write_colors(ili9341_display_t *dev, uint16_t *colors, uint16_t size);

void ili9341_write_register_word(ili9341_display_t *dev, uint16_t addr, uint16_t data);
void ili9341_write_register_byte(ili9341_display_t *dev, uint16_t addr, uint16_t data);

/* Graphics Implementation Functions */
void lcd_draw_filled_rect(ili9341_display_t *dev, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_draw_pixel(ili9341_display_t *dev, uint16_t x, uint16_t y, uint16_t color);
void lcd_fast_draw_pixels(ili9341_display_t *dev, uint16_t x, uint16_t y, uint16_t size, uint16_t *color);
