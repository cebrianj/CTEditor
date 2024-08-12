#include "utils.h"

#define ERROR 1

int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }

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