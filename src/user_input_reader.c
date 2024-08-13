#include "user_input_reader.h"

user_input read_input() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            panic("read");
        }
    }

    if (c != ESCAPE_SEQUENCE_PREFIX) {
        return create_user_input_from_char(c);
    }

    char sequence[3];
    if (read(STDIN_FILENO, &sequence[0], 1) != 1 ||
        read(STDIN_FILENO, &sequence[1], 1) != 1) {
        return create_user_input_from_char(ESCAPE_SEQUENCE_PREFIX);
    }

    if (sequence[0] == '[') {
        switch (sequence[1]) {
            // Map arrows
            case 'A':
                return create_user_input_from_event(KEY_ARROW_UP);
            case 'B':
                return create_user_input_from_event(KEY_ARROW_DOWN);
            case 'C':
                return create_user_input_from_event(KEY_ARROW_RIGHT);
            case 'D':
                return create_user_input_from_event(KEY_ARROW_LEFT);
        }
    }

    return create_user_input_from_char(ESCAPE_SEQUENCE_PREFIX);
}