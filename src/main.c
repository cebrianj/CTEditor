#include <errno.h>
#include <stdlib.h>

#include "buffer.h"
#include "editor_state.h"
#include "escape_sequences.h"
#include "rendering_controller.h"
#include "terminal.h"
#include "user_input_processor.h"
#include "user_input_reader.h"
#include "utils.h"

editor_state state;
void initialize_editor_state();
int handle_event(USER_EVENT event, terminal_size term_size);

int main() {
    char c;
    USER_EVENT event;

    setup_terminal_io();
    terminal_size term_size = get_terminal_size();
    while (1) {
        refresh_screen(term_size, state);
        c = read_key();
        event = process_key(c);
        handle_event(event, term_size);
    }
    return 0;
}

void initialize_editor_state() {
    state.cursor_x = 0;
    state.cursor_y = 0;
}

int handle_event(USER_EVENT event, terminal_size term_size) {
    switch (event) {
        case NONE:
            break;
        case MOVE_CURSOR_UP:
            state.cursor_y = max(state.cursor_y - 1, 0);
            break;
        case MOVE_CURSOR_DOWN:
            state.cursor_y = min(state.cursor_y + 1, term_size.rows);
            break;
        case MOVE_CURSOR_LEFT:
            state.cursor_x = max(state.cursor_x - 1, 0);
            break;
        case MOVE_CURSOR_RIGHT:
            state.cursor_x = min(state.cursor_x + 1, term_size.cols);
            break;
        default:
            return 1;
    }
    return 0;
}