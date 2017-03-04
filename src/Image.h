/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef STEGANOGRAPHY_IMAGE_IMAGE_H
#define STEGANOGRAPHY_IMAGE_IMAGE_H

typedef struct Image {
    int width;
    int height;
    int channels;
    unsigned char *data;
} Image;

void image_init_from_file(Image *image, const char *filename);

#endif //STEGANOGRAPHY_IMAGE_IMAGE_H
