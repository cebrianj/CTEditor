
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_state.h"
#include "event_handler.h"
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
        editor_state_set_filename(state, argv[1]);
        handle_event(INITIALIZE_FILE_BUFFER, state, term_size);
    }

    while (1) {
        refresh_screen(term_size, state);
        user_input = read_input();
        event = process_input(user_input);
        handle_event(event, state, term_size);
    }
    return 0;
}