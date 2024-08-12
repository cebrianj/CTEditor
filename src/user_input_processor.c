#include "user_input_processor.h"

USER_EVENT process_key(char c) {
    switch (c) {
        case CTRL_WITH('q'):
            clean_terminal();
            exit(0);
        case 'w':
            return MOVE_CURSOR_UP;
        case 's':
            return MOVE_CURSOR_DOWN;
        case 'a':
            return MOVE_CURSOR_LEFT;
        case 'd':
            return MOVE_CURSOR_RIGHT;
        default:
            return NONE;
            break;
    }
}