#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

#include "io.h"

#define FB_GREEN 2
#define FB_RED 4
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8

int fb_write(char *buf, unsigned int len);

#endif /* INCLUDE_IO_H */
