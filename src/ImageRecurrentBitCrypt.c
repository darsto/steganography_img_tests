/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <stdio.h>
#include <gmp.h>
#include "ImageRecurrentBitCrypt.h"

const int IMAGE_RECURRENT_BIT_CRYPT_STORAGE_BITS_PER_BYTE = 2;

#define assert_xy(image, x, y)  assert(x >= 0); \
                                assert(x < image->width); \
                                assert(y >= 0); \
                                assert(y < image->height)

static inline unsigned int read_value_from_pixel(Image *image, int x, int y) {
    unsigned char *image_data = image->data + (y * image->width + x) * image->channels;
    unsigned int ret = 0;
    
    assert_xy(image, x, y);
    
    ret += ((*(image_data + 0)) ^ x);
    ret += ((*(image_data + 1)) ^ y);
    
    return ret;
}

static inline void offset_pos_by_pixel(Image *image, int *x, int *y, const union ImageRecurrentBitCryptKey *key) {
    unsigned char *image_data = image->data + (*y * image->width + *x) * image->channels;
    
    assert_xy(image, *x, *y);
    
    *x = (*x + ((*(image_data + 2)) & key->offsetX)) % image->width;
    *y = (*y + ((*(image_data + 3)) & key->offsetY)) % image->height;
}

// (1) modify values of some pixels so that read_value will return some bigger values for them, so that remaining_val would be 0 by this point
// (2) also modify values of some pixels so that offset_pos will return different values, so that by now x == image->width-1, y == image->height-1
static int adjust_image(Image *image, int x, int y, unsigned int *hits, unsigned long remaining_val) {
    size_t i, j, base_i = 0, hits_num = image->width * image->height;
    unsigned long remaining_val_tmp = remaining_val;
    
    assert_xy(image, x, y);
    
    // pre (1)
    while (remaining_val_tmp) {
        remaining_val_tmp = remaining_val; //retry
        
        for (i = base_i; i < hits_num; ++i) { //iterate through hits
            if (hits[i] > 0 && hits[i] < remaining_val_tmp) { //if amount of hits at i-th pixel is larger than remaining_val_tmp, we can't do anything with it (incrementing it by one would be already too much)
                for (j = 1; hits[i] * (j + 1) <= remaining_val_tmp; ++j); //find best value j, so that (remaining_val - j * hits[i]) is the smallest possible non-negative number. this will get us closer to the result
                remaining_val_tmp -=  j * hits[i];
            }
        }
        
        ++base_i;
        if (base_i >= hits_num) {
            return -1;
        }
    }
    // TODO (1) (redo steps from upper loop with i = base_i-1
    
    // TODO (2)
    
    return 0;
}

size_t image_recurrent_bit_crypt_encrypt(Image *image, const char *data, size_t data_len, uint64_t key_val) {
    union ImageRecurrentBitCryptKey key = { .val = key_val };
    unsigned int *hits = calloc((size_t) image->width * image->height, 4);
    mpz_t base_sum, remaining_sum, encoded_sum;
    int x = key.offsetX, y = key.offsetY; /* current position on the image */
    unsigned int pixel_value;
    int rc;
    
    if (hits == NULL) {
        return 0;
    }

    mpz_init(base_sum);
    mpz_import(base_sum, data_len, 1, 1, 0, 0, data);
    mpz_init_set(remaining_sum, base_sum);
    mpz_init(encoded_sum);
    
    while (mpz_sgn(remaining_sum) >= 0) {
        pixel_value = read_value_from_pixel(image, x, y);
        mpz_add_ui(encoded_sum, encoded_sum, pixel_value);
        ++hits[y * image->width + x];
        offset_pos_by_pixel(image, &x, &y, &key);
        mpz_sub_ui(remaining_sum, remaining_sum, pixel_value);
    }
    
    rc = adjust_image(image, x, y, hits, mpz_get_ui(remaining_sum));
    
    mpz_clear(encoded_sum);
    mpz_clear(remaining_sum);
    mpz_clear(base_sum);
    free(hits);
    
    return rc == 0 ? data_len : 0;
}

size_t image_recurrent_bit_crypt_decrypt(const Image *image, char *data, uint64_t key) {
    
    //TODO !!
    
    return 0;
}

#undef assert_xy