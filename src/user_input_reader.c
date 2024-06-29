#include "user_input_reader.h"

char read_key() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            panic("read");
        }
    }
    return c;
}