#include <mems_mic.h>
#include <stdint.h>
#include <stdlib.h>
#include <dmac.h>
#include <i2s.h>
#include <fpioa.h>


mems_mic_device_t mems_mic_init_hal(int8_t mic_bck, int8_t mic_ws, int8_t mic_dat3) {
  DEFAULT_MEMS_MIC_DEVICE_INIT(device);
  device.mic_bck   = mic_bck;
  device.mic_ws    = mic_ws;
  device.mic_dat3  = mic_dat3;
  return device;
}

void mems_mic_init(mems_mic_device_t *device) {
  fpioa_set_function(device->mic_bck, device->bck_function);
  fpioa_set_function(device->mic_ws, device->ws_function);
  fpioa_set_function(device->mic_dat3, device->dat3_function);
  device->audio_buffer = (uint32_t *) malloc(sizeof(uint32_t) * DEFAULT_AUDIO_BUFFER_SIZE);
  i2s_init(device->i2s_device_number, device->i2s_transmit_mode, device->i2s_channel_mask);
  i2s_rx_channel_config(device->i2s_device_number, device->i2s_rx_channel, RESOLUTION_16_BIT, SCLK_CYCLES_32, TRIGGER_LEVEL_4, STANDARD_MODE);
}

void sample_audio(mems_mic_device_t *device) {
  i2s_recv_data_dma(
      device->i2s_device_number,
      device->audio_buffer,
      device->audio_buffer_size,
      device->dma_rx_channel
      );
}
