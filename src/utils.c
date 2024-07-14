#include "utils.h"

#define ERROR 1

void clean_terminal() {
    write(STDOUT_FILENO, CLEAR_SCREEN_SEQUENCE, CLEAR_SCREEN_SEQUENCE_BYTES);
    write(STDOUT_FILENO, CURSOR_TO_BEGINNING_SEQUENCE,
          CURSOR_TO_BEGINNING_SEQUENCE_BYTES);
}

void panic(const char *message) {
    clean_terminal();
    perror(message);
    exit(ERROR);
}