#include "filename.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char *getfileext(char *filename) {
	const char *dot = strrchr(filename, '.');
	return (dot && dot != filename) ? dot : "";
}

const char *getfileprefix(char *filename) {
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

char* encfilename(char *filename, uint8_t strsize) {
	const char *ext = getfileext(filename);
	const char *prefix = getfileprefix(filename);
	if ((strlen(prefix) + strlen(ext) * 2) < strsize) {
		filename[0] = '\0';
		strcat(filename, prefix);
		strcat(filename, ext);
		strcat(filename, ext);
		printf("Encrypted file name :%s\n", filename);
		return filename;
	}
	printf("file name too long\n");
	return '\0';
} 
