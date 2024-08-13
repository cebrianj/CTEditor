#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "key_event.h"

typedef struct {
    char value;
    key_event event;
} user_input;

user_input create_user_input_from_char(char ch);

user_input create_user_input_from_event(key_event event);
#endif
