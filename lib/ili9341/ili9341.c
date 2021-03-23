#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ili9341.h>
#include <spi.h>
#include <dmac.h>
#include <fpioa.h>
#include <gpiohs.h>


static bool ili9341_pin_defined(int8_t gpio_num) { return gpio_num >= 0; }

ili9341_display_t ili9341_init_hal_struct(int8_t sclk, int8_t mosi, int8_t reset, int8_t cs, int8_t dc, int8_t bl) {
  ILI9341_INIT_HAL(display);
  display.sclk   = sclk;
  display.mosi   = mosi;
  display.reset  = reset;
  display.cs     = cs;
  display.dc     = dc;
  display.bl     = bl;
  return display;
}


void ili9341_comm_init(ili9341_display_t *dev) {
  if(pin_defined(dev->cs))    fpioa_set_function(dev->cs, dev->cs_io_func);
  if(pin_defined(dev->dc))    fpioa_set_function(dev->dc, dev->cs_io_func);  
  if(pin_defined(dev->reset)) fpioa_set_function(dev->reset, dev->reset_io_func);  
  if(pin_defined(dev->mosi))  fpioa_set_function(dev->mosi, dev->mosi_io_func);  
  if(pin_defined(dev->sclk))  fpioa_set_function(dev->sclk, dev->sclk_io_func);  

  spi_init(dev->spi_device, ILI9341_DEFAULT_SPI_WORK_MODE, ILI9341_DEFAULT_SPI_FRAME_FORMAT, 8, 0); 
}
