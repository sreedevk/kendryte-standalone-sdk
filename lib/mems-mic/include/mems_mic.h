#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <i2s.h>
#include <fpioa.h>
#include <dmac.h>

#define DEFAULT_MIC_I2S_DEV_NUM             I2S_DEVICE_0
#define DEFAULT_MIC_I2S_TRANSMIT_TYPE       I2S_RECEIVER
#define DEFAULT_MIC_I2S_RX_CHANNEL_MASK     0x3

#define DEFAULT_AUDIO_BUFFER_SIZE           8

#define DEFAULT_BCK_FUNCTION                FUNC_I2S0_SCLK
#define DEFAULT_WS_FUNCTION                 FUNC_I2S0_WS
#define DEFAULT_DAT3_FUNCTION               FUNC_I2S0_IN_D0
#define DEFAULT_MIC_RX_CHANNEL              I2S_CHANNEL_0

#define DEFAULT_MIC_RX_DMA_CHANNEL          DMAC_CHANNEL1

#define DEFAULT_MEMS_MIC_DEVICE_INIT(x) mems_mic_device_t x = { \
  .mic_bck           = -1, \
  .mic_ws            = -1, \
  .mic_dat3          = -1, \
  .bck_function      = DEFAULT_BCK_FUNCTION,   \
  .ws_function       = DEFAULT_WS_FUNCTION,    \
  .dat3_function     = DEFAULT_DAT3_FUNCTION,  \
  .i2s_device_number = DEFAULT_MIC_I2S_DEV_NUM,       \
  .i2s_transmit_mode = DEFAULT_MIC_I2S_TRANSMIT_TYPE, \
  .i2s_channel_mask  = DEFAULT_MIC_I2S_RX_CHANNEL_MASK, \
  .i2s_rx_channel    = DEFAULT_MIC_RX_CHANNEL,        \
  .audio_buffer_size = DEFAULT_AUDIO_BUFFER_SIZE      \
}

typedef struct {
  int8_t                 mic_bck;   /* clock signal */
  int8_t                 mic_ws;    /* channel selection signal */
  int8_t                 mic_dat3;  /* Serial Data Signal */
  fpioa_function_t       bck_function;
  fpioa_function_t       ws_function;
  fpioa_function_t       dat3_function;
  i2s_device_number_t    i2s_device_number;
  i2s_transmit_t         i2s_transmit_mode;
  uint32_t               i2s_channel_mask;
  uint32_t               *audio_buffer;
  size_t                 audio_buffer_size;
  dmac_channel_number_t  dma_rx_channel;
  i2s_channel_num_t      i2s_rx_channel;
} mems_mic_device_t;

mems_mic_device_t mems_mic_init_hal(int8_t mic_bck, int8_t mic_ws, int8_t mic_dat3);
void mems_mic_init(mems_mic_device_t *device);
