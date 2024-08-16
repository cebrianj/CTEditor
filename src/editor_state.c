#include "editor_state.h"

#include <stdlib.h>
#include <string.h>

#include "row.h"
#include "utils.h"

editor_state* editor_state_create() {
    editor_state* state = (editor_state*)calloc(1, sizeof(editor_state));
    if (state == NULL) {
        panic("Failed to allocate memory for editor state");
    }
    return state;
}

void editor_state_append_row(editor_state* state, char* line, int len) {
    state->file_loaded_rows =
        realloc(state->file_loaded_rows,
                sizeof(row) * (state->file_loaded_num_rows + 1));
    int at = state->file_loaded_num_rows;
    state->file_loaded_rows[at].size = len;
    state->file_loaded_rows[at].chars = malloc(len + 1);
    memcpy(state->file_loaded_rows[at].chars, line, len);
    state->file_loaded_rows[at].chars[len] = '\0';
    state->file_loaded_num_rows++;
}

void editor_state_destroy(editor_state* state) {
    if (state != NULL) {
        free(state);
    }
}