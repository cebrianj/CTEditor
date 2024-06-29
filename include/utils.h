#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define CTRL_WITH(key) ((key) & 0x1f)

void panic(const char *message);

#endif
