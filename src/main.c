#include <zephyr/kernel.h>

// test_opus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/opus.h"

#define SAMPLE_RATE 48000
#define CHANNELS 2
#define FRAME_SIZE 960

void test_opus_encode_decode() {
    int err;
    OpusEncoder *encoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_AUDIO, &err);
    if (err != OPUS_OK) {
        printf("Failed to create encoder: %s\n", opus_strerror(err));
        return;
    }

    OpusDecoder *decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
    if (err != OPUS_OK) {
        printf("Failed to create decoder: %s\n", opus_strerror(err));
        opus_encoder_destroy(encoder);
        return;
    }

    // Test data: 1 second of silence
    opus_int16 in[FRAME_SIZE * CHANNELS] = {0};
    unsigned char encoded_data[4000];
    opus_int16 out[FRAME_SIZE * CHANNELS];

    int nbBytes = opus_encode(encoder, in, FRAME_SIZE, encoded_data, sizeof(encoded_data));
    if (nbBytes < 0) {
        printf("Encode failed: %s\n", opus_strerror(nbBytes));
        opus_encoder_destroy(encoder);
        opus_decoder_destroy(decoder);
        return;
    }

    int frame_size = opus_decode(decoder, encoded_data, nbBytes, out, FRAME_SIZE, 0);
    if (frame_size < 0) {
        printf("Decode failed: %s\n", opus_strerror(frame_size));
        opus_encoder_destroy(encoder);
        opus_decoder_destroy(decoder);
        return;
    }

    // Verify the decoded data matches the original data
    if (memcmp(in, out, FRAME_SIZE * CHANNELS * sizeof(opus_int16)) == 0) {
        printf("Test passed! Encoded and decoded data match.\n");
    } else {
        printf("Test failed! Encoded and decoded data do not match.\n");
    }

    opus_encoder_destroy(encoder);
    opus_decoder_destroy(decoder);
}

int main(void) {
    test_opus_encode_decode();
    return 0;
}