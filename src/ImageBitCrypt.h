/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef STEGANOGRAPHY_IMAGE_IMAGEBITCRYPT_H
#define STEGANOGRAPHY_IMAGE_IMAGEBITCRYPT_H

#include <stdlib.h>
#include "Image.h"

/** Amount of bits of each image byte used to hold hidden data */
extern const int IMAGE_BIT_CRYPT_STORAGE_BITS_PER_BYTE; /* 1 <= x <= 8 */

/**
 * Encode raw data inside image
 * @param data raw data to encode
 * @return number of encoded characters.
 * It will be equal or smaller than strlen(text)
 */
size_t image_bit_crypt_encrypt(Image *image, const char *data, size_t data_len);

/**
 * Decode raw data from image
 * @param data output buffer to store raw data into.
 * The buffer must be of at least the following size:
 * image->width * image->height * image->channels * IMAGE_BIT_CRYPT_STORAGE_BITS_PER_BYTE / 8
 * The outputted data will be null-terminated
 * @return number of decoded characters
 */
size_t image_bit_crypt_decrypt(const Image *image, char *data);

#endif //STEGANOGRAPHY_IMAGE_IMAGEBITCRYPT_H
