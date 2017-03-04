/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef STEGANOGRAPHY_IMAGE_IMAGEBITCRYPT_H
#define STEGANOGRAPHY_IMAGE_IMAGEBITCRYPT_H

#include "Image.h"

/**
 * Encode text inside image
 * @param text string to encode ending with NULL
 */
void image_bit_crypt_encrypt(Image *image, const char *text);

/**
 * Decode text from image
 * @return heap-allocated string ending with NULL. It has to deleted manually
 */
char *image_bit_crypt_decrypt(Image *image);

#endif //STEGANOGRAPHY_IMAGE_IMAGEBITCRYPT_H
