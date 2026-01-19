#ifndef FILENAME_H
#define FILENAME_H

#include <stdint.h>

const char *getfileext(const char *filename);
const char *getfileprefix(const char *filename);
char* encfilename(const char *filename, uint8_t strsize);

#endif
