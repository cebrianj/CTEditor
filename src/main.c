#include <errno.h>
#include <stdlib.h>

#include "terminal_io.h"
#include "user_input_processor.h"
#include "user_input_reader.h"
#include "utils.h"

int main() {
    char c;
    setup_terminal_io();
    clean_terminal();
    while (1) {
        c = read_key();
        process_key(c);
    }
    return 0;
}