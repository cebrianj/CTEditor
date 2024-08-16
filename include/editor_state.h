#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "row.h"

typedef struct {
    int cursor_x, cursor_y;

    char* filename;
    int rendering_rows_offset;
    int file_loaded_num_rows;
    row* file_loaded_rows;
} editor_state;

editor_state* editor_state_create();

void editor_state_set_filename(editor_state* state, char* filename);
void editor_state_append_row(editor_state* state, char* line, int len);

#endif