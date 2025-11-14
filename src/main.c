#include "keymanager.h"
#include "xor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_file encryption_mode\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file_to_encrypt = argv[1];
    uint8_t key[KEYSIZE];
    char keymode[256] = {0};
    char file_key[256] = {0};

    if (strcmp(argv[2], "xor") == 0) {
        printf("Keymodes:\n");
        printf("1. Press Enter to generate random key\n");
        printf("2. Type 'file' to use key from file\n");
        printf("3. Type any string to use as key (will be resized)\n");
        printf("Enter keymode: ");

        if (fgets(keymode, sizeof(keymode), stdin) == NULL) {
            perror("Error reading input");
            return EXIT_FAILURE;
        }

        keymode[strcspn(keymode, "\n")] = 0;

        if (strlen(keymode) == 0) {
            resizekey(key, "");
        }
        else if (strcmp(keymode, "file") == 0) {
            printf("Enter path to key file: ");
            if (fgets(file_key, sizeof(file_key), stdin) == NULL) {
                perror("Error reading input");
                return EXIT_FAILURE;
            }
            file_key[strcspn(file_key, "\n")] = 0;
            extractkeyfromfile(key, file_key);
        }
        else {
            resizekey(key, keymode);
        }

        viewkey(key, 1);
        encrypt(file_to_encrypt, key);
    }
    else {
        printf("No other method available yet!\n");
        return EXIT_FAILURE;
    }

    printf("\nOperation completed.\n");
    printf("Generated key is saved in key.txt (if random key was generated)\n");
    printf("Encrypted file: <originalname>.<originalextension>.<originalextension>\n");
	printf("Encrypted file is located in the same repository as the original file\n");
    return EXIT_SUCCESS;
}
