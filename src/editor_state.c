#include "editor_state.h"

#include <stdlib.h>

#include "utils.h"

editor_state* editor_state_create() {
    editor_state* state = (editor_state*)calloc(1, sizeof(editor_state));
    if (state == NULL) {
        panic("Failed to allocate memory for editor state");
    }
    return state;
}

void editor_state_destroy(editor_state* state) {
    if (state != NULL) {
        free(state);
    }
}