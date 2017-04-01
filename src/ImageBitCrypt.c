/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "ImageBitCrypt.h"

const int IMAGE_BIT_CRYPT_STORAGE_BITS_PER_BYTE = 2;

size_t image_bit_crypt_encrypt(Image *image, const char *data, size_t data_len) {
    const char *org_data = data;
    unsigned char *image_data = image->data;
    int image_bit_pos = 0;
    int image_remaining_bytes = image->width * image->height * image->channels;
    int data_bit;
    int bit_id;
    
    while (data_len > 0 && image_remaining_bytes > 0) {
        for (bit_id = 0; bit_id < 8; ++bit_id) {
            data_bit = (*data >> bit_id) & 1;

            *image_data &= ~(1 << image_bit_pos);
            *image_data |= (data_bit << image_bit_pos);

            ++image_bit_pos;
            if (image_bit_pos >= IMAGE_BIT_CRYPT_STORAGE_BITS_PER_BYTE) {
                image_bit_pos = 0;
                ++image_data;
                --image_remaining_bytes;
            }
        }

        --data_len;
        ++data;
    }
    
    return data - org_data;
}

size_t image_bit_crypt_decrypt(const Image *image, char *data) {
    int text_bit_pos = 0;
    size_t text_byte_pos = 0;
    int image_channel_id, size;
    int image_bit_id, decoded_bit;

    for (image_channel_id = 0, size = image->width * image->height * image->channels; image_channel_id < size; ++image_channel_id) {
        for (image_bit_id = 0; image_bit_id < IMAGE_BIT_CRYPT_STORAGE_BITS_PER_BYTE; ++image_bit_id) {
            decoded_bit = (image->data[image_channel_id] >> image_bit_id) & 1;

            /* this would be naturally placed at the very end of the loop,
             * but it's right here, so that when both loops end,
             * text_bit_pos always points to the strlen(data) + 1 */
            if (text_bit_pos >= 8) {
                text_bit_pos = 0;
                ++text_byte_pos;
            }
            
            data[text_byte_pos] |= (decoded_bit << text_bit_pos);
            ++text_bit_pos;
        }
    }
    
    return text_byte_pos - 1;
}
