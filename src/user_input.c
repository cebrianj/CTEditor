

#include "user_input.h"

user_input create_user_input() {
    return (user_input){.event = KEY_NONE, .value = '\0'};
}

user_input create_user_input_from_char(char ch) {
    user_input ui = create_user_input();
    ui.value = ch;
    return ui;
}

user_input create_user_input_from_event(key_event event) {
    user_input ui = create_user_input();
    ui.event = event;
    return ui;
}
