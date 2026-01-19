#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "keymanager.h"
#include "xor.h"

#define MAX_CMD 256
#define MAX_ARGS 10

void print_banner() {
	printf(
        "███████╗██╗██╗     ███████╗    ████████╗ ██████╗  ██████╗ ██╗\n"
        "██╔════╝██║██║     ██╔════╝    ╚══██╔══╝██╔═══██╗██╔═══██╗██║\n"
        "█████╗  ██║██║     █████╗         ██║   ██║   ██║██║   ██║██║\n"
        "██╔══╝  ██║██║     ██╔══╝         ██║   ██║   ██║██║   ██║██║\n"
        "██║     ██║███████╗███████╗       ██║   ╚██████╔╝╚██████╔╝███████╗\n"
        "╚═╝     ╚═╝╚══════╝╚══════╝       ╚═╝    ╚═════╝  ╚═════╝ ╚══════╝\n\n"
    );
}


void command(char *input) {
	char *argv[MAX_ARGS];
	int argc = 0;

	char *token = strtok(input, " ");
	while (token && argc < MAX_ARGS - 1) {
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	argv[argc] = NULL;

	if (argc == 0) {
		return;
	}

	if (strcmp(argv[0], "about") == 0) {
		printf("See readme.md on github.com/maxence7z/file-tool\n");
	} else if (strcmp(argv[0], "encrypt") == 0) {
		char *file_to_encrypt = argv[1];
		uint8_t key[KEYSIZE];
		char keymode[256] = {0};

        printf("Keymodes:\n");
        printf("1. Press Enter to generate random key\n");
        printf("2. Type 'file' to use key from file\n");
        printf("3. Type any string to use as key (will be resized)\n");
        printf("Enter keymode: ");

        if (fgets(keymode, sizeof(keymode), stdin) == NULL) {
            perror("Error reading input");
            return;
        }

        keymode[strcspn(keymode, "\n")] = 0;

        if (strlen(keymode) == 0) {
            resizekey(key, "");
        }
        else if (strcmp(keymode, "file") == 0) {
			char file_key[256] = {0};
            printf("Enter path to key file: ");
            if (fgets(file_key, sizeof(file_key), stdin) == NULL) {
                perror("Error reading input");
                return;
            }
            file_key[strcspn(file_key, "\n")] = 0;
            extractkeyfromfile(key, file_key);
        }
        else {
            resizekey(key, keymode);
        }

        viewkey(key, 1);

		char encryptmode[256] = {0};

		printf("Enter cypher method\n");
		printf("Available methods :\n xor\n aes256 coming soon");

		if (fgets(encryptmode, sizeof(encryptmode), stdin) == NULL) {
			perror("Error reading input");
			return;
		}

		encryptmode[strcspn(encryptmode, "\n")] = 0;

		if (strcmp(encryptmode, "xor") == 0) {
			xorencrypt(file_to_encrypt, key);
		} else {
			printf("No other method available yet\n");
			return;
		}

    	printf("\nOperation completed.\n");
    	printf("Generated key is saved in key.txt (if random key was generated)\n");
    	printf("Encrypted file: <originalname>.<originalextension>.<originalextension>\n");
		printf("Encrypted file is located in the same repository as the original file\n"); 
	}
}


void shell() {
    char input[MAX_CMD];

    print_banner();

    while (1) {
        printf("file_tool> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        command(input);
    }
}
