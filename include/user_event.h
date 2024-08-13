#ifndef USER_EVENT_H
#define USER_EVENT_H

typedef enum _user_event {
    NONE = 0,
    MOVE_CURSOR_UP,
    MOVE_CURSOR_DOWN,
    MOVE_CURSOR_LEFT,
    MOVE_CURSOR_RIGHT,
    MOVE_PAGE_UP,
    MOVE_PAGE_DOWN
} user_event;

#endif