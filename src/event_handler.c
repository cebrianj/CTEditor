
#include "event_handler.h"

#include <stdbool.h>

#include "file_io.h"
#include "utils.h"

void init_file_buffer(editor_state *state, terminal_size term_size);
void editor_state_append_file_rows(char *filename, int offset, int rows,
                                   editor_state *state);
bool is_rendering_reaching_buffer_limit(editor_state *state,
                                        terminal_size term_size);

int handle_event(user_event event, editor_state *state,
                 terminal_size term_size) {
    switch (event) {
        case NONE:
            break;
        case MOVE_CURSOR_UP:
            if (state->cursor_y == 0) {
                state->rendering_rows_offset =
                    max(state->rendering_rows_offset - 1, 0);
                return 0;
            }
            state->cursor_y = max(state->cursor_y - 1, 0);
            break;
        case MOVE_CURSOR_DOWN:
            if (is_rendering_reaching_buffer_limit(state, term_size)) {
                editor_state_append_file_rows(
                    state->filename,
                    state->rendering_rows_offset + term_size.rows,
                    term_size.rows, state);
            }

            if (state->cursor_y + 1 == term_size.rows) {
                state->rendering_rows_offset++;
                return 0;
            }
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
        case INITIALIZE_FILE_BUFFER:
            init_file_buffer(state, term_size);
            break;
        default:
            return 1;
    }
    return 0;
}

void init_file_buffer(editor_state *state, terminal_size term_size) {
    int offset = 0;
    editor_state_append_file_rows(state->filename, offset, term_size.rows,
                                  state);
}

void editor_state_append_file_rows(char *filename, int offset, int rows,
                                   editor_state *state) {
    row *readed_rows = file_io_read(filename, rows, offset);
    for (int i = 0; i < rows; i++) {
        editor_state_append_row(state, readed_rows[i].chars,
                                readed_rows[i].size);
        row_free(&readed_rows[i]);
    }
    free(readed_rows);
}

bool is_rendering_reaching_buffer_limit(editor_state *state,
                                        terminal_size term_size) {
    return state->rendering_rows_offset + term_size.rows >=
           state->file_loaded_num_rows;
}
