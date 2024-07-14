#include <errno.h>
#include <stdlib.h>

#include "buffer.h"
#include "escape_sequences.h"
#include "terminal.h"
#include "user_input_processor.h"
#include "user_input_reader.h"
#include "utils.h"

void draw_rows(buffer* buffer, terminal_size term_size) {
    for (int i = 0; i < term_size.rows; i++) {
        buffer_append(buffer, "~", 1);
        if (i < term_size.rows - 1) {
            buffer_append(buffer, "\r\n", 2);
        }
    }
}

void refresh_screen(terminal_size term_size) {
    buffer buffer = BUF_INIT;
    buffer_append(&buffer, CLEAR_SCREEN_SEQUENCE, CLEAR_SCREEN_SEQUENCE_BYTES);
    buffer_append(&buffer, CURSOR_TO_BEGINNING_SEQUENCE,
                  CURSOR_TO_BEGINNING_SEQUENCE_BYTES);
    draw_rows(&buffer, term_size);
    buffer_append(&buffer, CURSOR_TO_BEGINNING_SEQUENCE,
                  CURSOR_TO_BEGINNING_SEQUENCE_BYTES);
    write(STDOUT_FILENO, buffer.string, buffer.len);
    buffer_free(&buffer);
}

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