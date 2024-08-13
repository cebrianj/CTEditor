#include "user_input_processor.h"

USER_EVENT process_event(key_event event);
USER_EVENT process_value(char value);

USER_EVENT process_input(user_input user_input) {
    if (user_input.event != KEY_NONE) {
        return process_event(user_input.event);
    }

    return process_value(user_input.value);
}

USER_EVENT process_event(key_event event) {
    switch (event) {
        case KEY_ARROW_UP:
            return MOVE_CURSOR_UP;
        case KEY_ARROW_DOWN:
            return MOVE_CURSOR_DOWN;
        case KEY_ARROW_LEFT:
            return MOVE_CURSOR_LEFT;
        case KEY_ARROW_RIGHT:
            return MOVE_CURSOR_RIGHT;
        default:
            return NONE;
            break;
    }
}

USER_EVENT process_value(char value) {
    switch (value) {
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