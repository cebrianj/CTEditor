#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "escape_sequences.h"

#define CTRL_WITH(key) ((key) & 0x1f)

void clean_terminal();
void panic(const char *message);

#endif
