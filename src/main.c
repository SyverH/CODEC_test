#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "audio_codec_opus_api.h"

#define LOG_LEVEL LOG_LEVEL_DBG

LOG_MODULE_REGISTER(main, LOG_LEVEL);

int16_t testvar = 0;
m_audio_frame_t testvar2;

int main() {
    LOG_INF("Hello, World!");

    audio_codec_opus_init();

    // drv_audio_codec_encode(&testvar, &testvar2);
    // LOG_INF("Encoded data size: %d", testvar2.data_size);

    // drv_audio_codec_decode(&testvar2, &testvar);
    // LOG_INF("Decoded data: %d", testvar);
    // return 0;
}