/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef STEGANOGRAPHY_IMAGE_IMAGERECURRENTBITCRYPT_H
#define STEGANOGRAPHY_IMAGE_IMAGERECURRENTBITCRYPT_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "Image.h"

/** Amount of bits of each image byte used to hold hidden data */
extern const int IMAGE_RECURRENT_BIT_CRYPT_STORAGE_BITS_PER_BYTE; /* 1 <= x <= 8 */

union ImageRecurrentBitCryptKey {
    uint64_t val;
    struct {
        unsigned int version : 4; /* currently unused */
        unsigned int offsetX : 10;
        unsigned int offsetY : 10;
        int offsetDeltaX : 8;
        int offsetDeltaY : 8;
    };
};

/**
 * Encode raw data inside image
 * @param data raw data to encode
 * @param key key to encode the data with
 * @return number of encoded characters.
 * It will be either 0 (encoding failed), or sizeof(data)
 */
size_t image_recurrent_bit_crypt_encrypt(Image *image, const char *data, size_t data_len, uint64_t key);

/**
 * Decode raw data from image
 * @param data output buffer to store raw data into.
 * The buffer must be of at least the following size:
 * image->width * image->height * image->channels * IMAGE_RECURRENT_BIT_CRYPT_STORAGE_BITS_PER_BYTE / 8
 * @param key key to decode data with
 * @return number of decoded characters
 */
size_t image_recurrent_bit_crypt_decrypt(const Image *image, char *data, uint64_t key);

#endif //STEGANOGRAPHY_IMAGE_IMAGERECURRENTBITCRYPT_H
