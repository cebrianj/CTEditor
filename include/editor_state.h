#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

typedef struct {
    int cursor_x, cursor_y;
} editor_state;

editor_state* editor_state_create();

#endif