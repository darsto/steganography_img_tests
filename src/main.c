#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "ImageBitCrypt.h"

/**
 * Just algorithm tests
 * @return 
 */
int main() {
    struct Image image;
    image_init_from_file(&image, "me.png");

    const char *str1_raw = "This is a test number one.";
    image_bit_crypt_encrypt(&image, str1_raw);
    
    char *str1_decoded = image_bit_crypt_decrypt(&image);
    
    if (strcmp(str1_raw, str1_decoded) != 0) {
        printf("Encode/Decode error: \"%s\" != \"%s\" (length %ld instead of %ld)\n", str1_decoded, str1_raw, strlen(str1_decoded), strlen(str1_raw));
        return 1;
    }
    
    printf("All fine\n");

    free(str1_decoded);
    return 0;
}