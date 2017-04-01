/*
 * Copyright (c) 2017 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"
#include "ImageBitCrypt.h"

enum {
    MODE_ENCRYPT = 0,
    MODE_DECRYPT = 1
};

void printUsage(void) {
    fprintf(stderr, "Usage: ./steganography_image <mode> [text_to_encode]\n"
        "<mode> can be either:\n"
        "\t0 - encryption (encrypts file me.png and writes it to me_encrypted.png)\n"
        "\t1 - decryption (reads file me_encrypted.png and prints out decrypted message)\n"
        "[text_to_encode] must be a single word (no whitespaces)\n");
}

void encrypt(Image *image, const char *data, size_t data_len) {
    size_t str_encrypted_len = image_bit_crypt_encrypt(image, data, data_len);
    
    if (str_encrypted_len == data_len) {
        printf("Message encrypted successfully.\n");
    } else {
        printf("Warning: Message encrypted just partially. Wrote %zu out of %zu bytes\n", str_encrypted_len, data_len);
    }
}

void decrypt(Image *image) {
    char *str_decoded = calloc((size_t) image->width * image->height * image->channels * IMAGE_BIT_CRYPT_STORAGE_BITS_PER_BYTE / 8, 1);
    size_t str_decoded_len = image_bit_crypt_decrypt(image, str_decoded);
    
    printf("Decrypted message: %.*s\n", (int) str_decoded_len, str_decoded);
    free(str_decoded);
}

int main(int argc, char *argv[]) {
    struct Image image;
    long mode;
    const char *message = NULL;

    switch (argc) {
        case 3:
            message = argv[2];
        case 2:
            mode = strtol(argv[1], NULL, 10);
            if (mode == 1 || argc != 2) break; //won't break with mode == 1 and argc == 2
        default:
            fprintf(stderr, "Invalid number of arguments. ");
            printUsage();
            return EXIT_FAILURE;
    }

    switch (mode) {
        case MODE_ENCRYPT:
            image_init_from_file(&image, "me.png");
            encrypt(&image, message, strlen(message) + 1);
            image_save_to_file(&image, "me_encrypted.png");
            break;
        case MODE_DECRYPT:
            image_init_from_file(&image, "me_encrypted.png");
            decrypt(&image);
            break;
        default:
            fprintf(stderr, "Invalid mode. ");
            printUsage();
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}