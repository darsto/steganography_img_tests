/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <gmp.h>
#include "ImageRecurrentBitCrypt.h"

const int IMAGE_RECURRENT_BIT_CRYPT_STORAGE_BITS_PER_BYTE = 2;

static const int MAGIC_PADDING_VALUE = 4 * 256; // must be at least max possible number returned by read_value_from_pixel

static inline unsigned int read_value_from_pixel(Image *image, int x, int y) {
    unsigned char *image_data = image->data + (y * image->width + x) * image->channels;
    unsigned int ret = 0;

    //TODO assert x,y

    ret += (*(image_data + 0)) ^ x;
    ret += (*(image_data + 1)) ^ y;
    ret += (*(image_data + 2)) | ((x ^ y) & 0xFF);
    ret += (*(image_data + 3)) & (x + y);
    
    return ret;
}

static inline void offset_pos_by_pixel(Image *image, int *x, int *y, const union ImageRecurrentBitCryptKey *key) {
    unsigned char *image_data = image->data + (*y * image->width + *x) * image->channels;

    //TODO !!
}

static int adjust_image(Image *image, int x, int y, unsigned int *hits_num, unsigned long remaining_val) {
    
    //TODO !!
    
    return 0;
}

size_t image_recurrent_bit_crypt_encrypt(Image *image, const char *data, size_t data_len, uint64_t key_val) {
    union ImageRecurrentBitCryptKey key = { .val = key_val };
    size_t image_size = (size_t) image->width * image->height * image->channels;  
    unsigned int *hits_num = calloc(image_size, 4);
    mpz_t base_sum, remaining_sum, encoded_sum;
    int x = key.offsetX, y = key.offsetY; /* current position on the image */
    unsigned int pixel_value;
    int rc;
    
    if (hits_num == NULL) {
        return 0;
    }
    
    mpz_import(base_sum, data_len, 1, 1, 0, 0, data);
    mpz_init_set(remaining_sum, base_sum);
    mpz_init(encoded_sum);
    
    while (mpz_cmp_si(remaining_sum, 0) >= 0) {
        pixel_value = read_value_from_pixel(image, x, y);
        mpz_add_ui(encoded_sum, encoded_sum, pixel_value);
        ++hits_num[y * image->width + x];
        offset_pos_by_pixel(image, &x, &y, &key);
        mpz_sub_ui(remaining_sum, remaining_sum, pixel_value);
    }

    rc = adjust_image(image, x, y, hits_num, mpz_get_ui(remaining_sum));
    
    mpz_clears(encoded_sum, remaining_sum, base_sum);
    free(hits_num);
    
    return rc == 0 ? data_len : 0;
}

size_t image_recurrent_bit_crypt_decrypt(const Image *image, char *data, uint64_t key) {
    
    //TODO !!
    
    return 0;
}