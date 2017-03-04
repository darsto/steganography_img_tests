#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "ImageBitCrypt.h"

enum {
    MODE_ENCRYPT = 0,
    MODE_DECRYPT = 1
};

void printUsage(void);

int main(int argc, char *argv[]) {
    struct Image image;
    char *str1_decoded = NULL;
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
            image_bit_crypt_encrypt(&image, message);
            image_save_to_file(&image, "me_encrypted.png");
            printf("Message encrypted successfully.\n");
            break;
        case MODE_DECRYPT:
            image_init_from_file(&image, "me_encrypted.png");
            str1_decoded = image_bit_crypt_decrypt(&image);
            printf("Decrypted message: %s\n", str1_decoded);
            break;
        default:
            fprintf(stderr, "Invalid mode. ");
            printUsage();
            return EXIT_FAILURE;
    }

    free(str1_decoded);
    return EXIT_SUCCESS;
}

void printUsage(void) {
    fprintf(stderr, "Usage: ./steganography_image <mode> [text_to_encode]\n"
        "<mode> can be either:\n"
        "\t0 - encryption (encrypts file me.png and writes it to me_encrypted.png)\n"
        "\t1 - decryption (reads file me_encrypted.png and prints out decrypted message)\n"
        "[text_to_encode] must be a single word (no whitespaces)\n");
}