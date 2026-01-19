#ifndef FILENAME_H
#define FILENAME_H

#include <stdint.h>

const char *getfileext(char *filename);
const char *getfileprefix(char *filename);
char* encfilename(char *filename, uint8_t strsize);

#endif
