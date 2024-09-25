#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/opus/audio_codec_opus_api.h"
#include "zephyr/logging/log.h"

#define INPUT_DATA_SIZE CONFIG_AUDIO_FRAME_SIZE_SAMPLES*CONFIG_CHANNELS
#define OUTPUT_DATA_SIZE CONFIG_AUDIO_FRAME_SIZE_SAMPLES*CONFIG_CHANNELS

void fill_with_constant_data(int16_t *data, size_t size, int16_t value) {
    for (size_t i = 0; i < size / sizeof(int16_t); i++) {
        data[i] = value;
    }
}

void print_data(const char *label, const uint8_t *data, size_t size) {
    fprintf(stderr, "%s\n", label);
    for (size_t i = 0; i < size; i++) {
        fprintf(stderr, "%02x ", data[i]);
    }
    fprintf(stderr, "\n");
}

int main() {
    // Initialize Opus codec
    audio_codec_opus_init();

    // Prepare buffers
    int16_t Data_In[INPUT_DATA_SIZE];
    int16_t Data_Out[OUTPUT_DATA_SIZE];
    
    m_audio_frame_t frame_OPUS_encode;
    m_audio_frame_t frame_OPUS_decode;

    // Fill with constant data for test
    fill_with_constant_data((int16_t *)Data_In, INPUT_DATA_SIZE, 60);

    // Prepare encoding frame
    frame_OPUS_encode.data_size = INPUT_DATA_SIZE;
    memcpy(frame_OPUS_encode.data, Data_In, INPUT_DATA_SIZE);

    // Encode data
    drv_audio_codec_encode((int16_t *)Data_In, &frame_OPUS_encode);

    // Log encoded data
    fprintf(stderr, "Encoded data size: %d\n", frame_OPUS_encode.data_size);
    print_data("Encoded data:", frame_OPUS_encode.data, frame_OPUS_encode.data_size);

    // Prepare decoding frame
    frame_OPUS_decode.data_size = frame_OPUS_encode.data_size;
    memcpy(frame_OPUS_decode.data, frame_OPUS_encode.data, frame_OPUS_encode.data_size);

    // Decode data
    drv_audio_codec_decode(&frame_OPUS_encode, (int16_t *)Data_Out);

    // Log decoded data
    print_data("Decoded data:", (uint8_t *)Data_Out, INPUT_DATA_SIZE);

    // Optionally compare original and decoded data
    int match = 1;
    for (size_t i = 0; i < INPUT_DATA_SIZE / sizeof(int16_t); i++) {
        if (((int16_t *)Data_In)[i] != ((int16_t *)Data_Out)[i]) {
            fprintf(stderr, "Mismatch at index %zu: Original = %d, Decoded = %d\n", i, ((int16_t *)Data_In)[i], ((int16_t *)Data_Out)[i]);
            match = 0;
        }
    }

    if (match) {
        fprintf(stderr, "Data match\n");
    } else {
        fprintf(stderr, "Data do not match\n");
    }

    return 0;
}
