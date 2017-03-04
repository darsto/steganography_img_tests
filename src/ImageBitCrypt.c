/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <stdlib.h>
#include "ImageBitCrypt.h"

const char STORAGE_BITS_PER_BYTE = 2; // 1 <= x <= 8

void image_bit_crypt_encrypt(Image *image, const char *text) {
    unsigned char *image_data = image->data;
    char image_bit_pos = 0;
    while (1) {
        for (int bit_id = 0; bit_id < 8; ++bit_id) {
            int data_bit = (*text >> bit_id) & 1;

            *image_data &= ~(1 << image_bit_pos);
            *image_data |= (data_bit << image_bit_pos);

            ++image_bit_pos;
            if (image_bit_pos >= STORAGE_BITS_PER_BYTE) {
                image_bit_pos = 0;
                ++image_data;
            }
        }

        if (*text == 0) {
            break;
        }
        
        ++text;
    }
}

char *image_bit_crypt_decrypt(Image *image) {
    size_t text_len = (size_t) image->width * image->height * image->channels * STORAGE_BITS_PER_BYTE / 8;
    char *text = (char *) calloc(text_len, 1);

    int text_bit_pos = 0;
    int text_byte_pos = 0;

    for (int image_channel_id = 0, size = image->width * image->height * image->channels; image_channel_id < size; ++image_channel_id) {
        for (int image_bit_id = 0; image_bit_id < STORAGE_BITS_PER_BYTE; ++image_bit_id) {
            int decoded_bit = (image->data[image_channel_id] >> image_bit_id) & 1;

            text[text_byte_pos] |= (decoded_bit << text_bit_pos);

            ++text_bit_pos;
            if (text_bit_pos >= 8) {
                text_bit_pos = 0;
                ++text_byte_pos;
            }
        }
    }
    
    text[text_len - 1] = NULL; //for safety reasons
    return text;
}
