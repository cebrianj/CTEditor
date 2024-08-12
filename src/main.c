#include <errno.h>
#include <stdlib.h>

#include "buffer.h"
#include "escape_sequences.h"
#include "rendering_controller.h"
#include "terminal.h"
#include "user_input_processor.h"
#include "user_input_reader.h"
#include "utils.h"

int main() {
    char c;
    setup_terminal_io();
    terminal_size term_size = get_terminal_size();
    while (1) {
        refresh_screen(term_size);
        c = read_key();
        process_key(c);
    }
    return 0;
}
