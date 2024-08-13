#include "user_input_reader.h"

#define SEQUENCE_HOME_0 "[1~"
#define SEQUENCE_HOME_1 "[7~"
#define SEQUENCE_HOME_2 "[H"
#define SEQUENCE_HOME_3 "OH"
#define SEQUENCE_END_0 "[4~"
#define SEQUENCE_END_1 "[8~"
#define SEQUENCE_END_2 "[F"
#define SEQUENCE_END_3 "OF"

#define SEQUENCE_PAGE_UP "[5~"
#define SEQUENCE_PAGE_DOWN "[6~"

#define SEQUENCE_ARROW_UP "[A"
#define SEQUENCE_ARROW_DOWN "[B"
#define SEQUENCE_ARROW_RIGHT "[C"
#define SEQUENCE_ARROW_LEFT "[D"

user_input read_sequence();

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

    return read_sequence();
}

user_input read_sequence() {
    char sequence[4] = {0};
    int sequence_bytes = read(STDIN_FILENO, sequence, sizeof(sequence) - 1);

    if (sequence_bytes <= 0) {
        return create_user_input_from_char(ESCAPE_SEQUENCE_PREFIX);
    }

    if (strcmp(sequence, SEQUENCE_PAGE_UP) == 0) {
        return create_user_input_from_event(KEY_PAGE_UP);
    }
    if (strcmp(sequence, SEQUENCE_PAGE_DOWN) == 0) {
        return create_user_input_from_event(KEY_PAGE_DOWN);
    }

    if (strcmp(sequence, SEQUENCE_ARROW_UP) == 0) {
        return create_user_input_from_event(KEY_ARROW_UP);
    }
    if (strcmp(sequence, SEQUENCE_ARROW_DOWN) == 0) {
        return create_user_input_from_event(KEY_ARROW_DOWN);
    }
    if (strcmp(sequence, SEQUENCE_ARROW_RIGHT) == 0) {
        return create_user_input_from_event(KEY_ARROW_RIGHT);
    }
    if (strcmp(sequence, SEQUENCE_ARROW_LEFT) == 0) {
        return create_user_input_from_event(KEY_ARROW_LEFT);
    }

    if (strcmp(sequence, SEQUENCE_HOME_0) == 0) {
        return create_user_input_from_event(KEY_HOME);
    }
    if (strcmp(sequence, SEQUENCE_HOME_1) == 0) {
        return create_user_input_from_event(KEY_HOME);
    }
    if (strcmp(sequence, SEQUENCE_HOME_2) == 0) {
        return create_user_input_from_event(KEY_HOME);
    }
    if (strcmp(sequence, SEQUENCE_HOME_3) == 0) {
        return create_user_input_from_event(KEY_HOME);
    }

    if (strcmp(sequence, SEQUENCE_END_0) == 0) {
        return create_user_input_from_event(KEY_END);
    }
    if (strcmp(sequence, SEQUENCE_END_1) == 0) {
        return create_user_input_from_event(KEY_END);
    }
    if (strcmp(sequence, SEQUENCE_END_2) == 0) {
        return create_user_input_from_event(KEY_END);
    }
    if (strcmp(sequence, SEQUENCE_END_3) == 0) {
        return create_user_input_from_event(KEY_END);
    }
    return create_user_input_from_char(ESCAPE_SEQUENCE_PREFIX);
}