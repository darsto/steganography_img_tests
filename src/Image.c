/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void image_init_from_file(Image *image, const char *filename) {
    image->data = stbi_load(filename, &image->width, &image->height, &image->channels, 0);
}
