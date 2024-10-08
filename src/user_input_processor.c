#include "user_input_processor.h"

user_event process_event(key_event event);
user_event process_value(char value);

user_event process_input(user_input user_input) {
    if (user_input.event != KEY_NONE) {
        return process_event(user_input.event);
    }

    return process_value(user_input.value);
}

user_event process_event(key_event event) {
    switch (event) {
        case KEY_PAGE_UP:
            return MOVE_PAGE_UP;
        case KEY_PAGE_DOWN:
            return MOVE_PAGE_DOWN;
        case KEY_HOME:
            return MOVE_CURSOR_START;
        case KEY_END:
            return MOVE_CURSOR_END;
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

user_event process_value(char value) {
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