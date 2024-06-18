#include "utils.h"

#include <errno.h>

#define ERROR 1

void panic(const char *message) {
    perror(message);
    exit(ERROR);
}