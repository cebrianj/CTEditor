#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "terminal_io.h"
#include "utils.h"

int main() {
    setup_terminal_io();

    char c;
    while (1) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
            panic("Error trying to read from terminal");
        }
        if (iscntrl(c)) {
            // printf("%d\r\n", c);
        } else {
            printf("%c\n", c);
        }
        if (c == 'q') break;
    }
    return 0;
}