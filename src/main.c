
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_state.h"
#include "event_handler.h"
#include "file_io.h"
#include "rendering_controller.h"
#include "terminal.h"
#include "user_input_processor.h"
#include "user_input_reader.h"
#include "utils.h"

void load_file_rows(char *filename, editor_state *state, int rows);

int main(int argc, char *argv[]) {
    editor_state *state = editor_state_create();
    user_input user_input;
    user_event event;

    setup_terminal_io();
    terminal_size term_size = get_terminal_size();

    if (argc >= 2) {
        load_file_rows(argv[1], state, term_size.rows);
    }

    while (1) {
        refresh_screen(term_size, state);
        user_input = read_input();
        event = process_input(user_input);
        handle_event(event, state, term_size);
    }
    return 0;
}

void load_file_rows(char *filename, editor_state *state, int rows) {
    int offset = 0;
    row *readed_rows = file_io_read(filename, rows, offset);
    for (int i = 0; i < rows; i++) {
        editor_state_append_row(state, readed_rows[i].chars,
                                readed_rows[i].size);
        row_free(&readed_rows[i]);
    }
    free(readed_rows);
}