#include "xor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define KEYSIZE 32

static const char *getfileext(const char *filename) {
	const char *dot = strrchr(filename, '.');
	return (dot && dot != filename) ? dot : "";
}

static const char *getfileprefix(const char *filename) {
	const char *lastdot = strrchr(filename, '.');
	if (lastdot == NULL || lastdot == filename) {
		return filename;
	}
	static char prefix[256]; //max length for filename is 255 anyways
	size_t prefixlen = lastdot - filename;
	strncpy(prefix, filename, prefixlen);
	prefix[prefixlen] = '\0';
	return prefix;
}

void encrypt(const char *filename, uint8_t *key) {
	const char *ext = getfileext(filename);
	const char *prefix = getfileprefix(filename);
	char encrypted_file_name[256 + 20]; //not so secure
	strcat(encrypted_file_name, prefix);
	strcat(encrypted_file_name, ext);
	strcat(encrypted_file_name, ext);

	printf("Encrypted file name :%s\n", encrypted_file_name);
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		perror("Error with source file\n");
		return;
	}
	FILE *fo = fopen(encrypted_file_name, "wb");
	if (fo == NULL) {
		fclose(f);
		perror("Error with destination file\n");
		return;
	}


	int c;
	size_t keyidx = 0;
	while ((c = fgetc(f)) != EOF) {
		fputc(c ^ key[keyidx], fo);
		keyidx = (keyidx + 1) % KEYSIZE;
	}

	if (ferror(f) || ferror(fo)) {
		perror("Error while handling files\n");
	}
	if (fclose(f) != 0) {
		perror("Error while closing src file\n");
	}
	if (fclose(fo) != 0)  {
		perror("Error while closing dest file\n");
	}
}
