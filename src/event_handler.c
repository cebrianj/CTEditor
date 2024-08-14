
#include "event_handler.h"

#include "utils.h"

int handle_event(user_event event, editor_state* state,
                 terminal_size term_size) {
    switch (event) {
        case NONE:
            break;
        case MOVE_CURSOR_UP:
            state->cursor_y = max(state->cursor_y - 1, 0);
            break;
        case MOVE_CURSOR_DOWN:
            state->cursor_y = min(state->cursor_y + 1, term_size.rows);
            break;
        case MOVE_CURSOR_LEFT:
            state->cursor_x = max(state->cursor_x - 1, 0);
            break;
        case MOVE_CURSOR_RIGHT:
            state->cursor_x = min(state->cursor_x + 1, term_size.cols);
            break;
        case MOVE_CURSOR_START:
            state->cursor_x = 0;
            break;
        case MOVE_CURSOR_END:
            state->cursor_x = term_size.cols;
            break;
        default:
            return 1;
    }
    return 0;
}
