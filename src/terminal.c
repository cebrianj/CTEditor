#include "terminal.h"

#include <sys/ioctl.h>

#include "escape_sequences.h"

int move_cursor(char* sequence, int sequence_len);

int get_cursor_position(int* row, int* col);

void setup_terminal() { setup_terminal_io(); }

terminal_size get_terminal_size() {
    struct winsize ws;
    terminal_size ts;
    int can_use_ioctl =
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1 && ws.ws_col != 0;

    if (can_use_ioctl) {
        ts.cols = ws.ws_col;
        ts.rows = ws.ws_row;
    } else {
        move_cursor(CURSOR_TO_RIGHT, CURSOR_TO_RIGHT_BYTES);
        move_cursor(CURSOR_TO_BOTTOM, CURSOR_TO_BOTTOM_BYTES);
        get_cursor_position(&ts.rows, &ts.cols);
    }

    return ts;
}

int get_cursor_position(int* row, int* col) {
    char response[32];
    ssize_t len;

    // Ask for cursor position
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) {
        return -1;
    }

    // Read response
    len = read(STDIN_FILENO, response, sizeof(response) - 1);
    if (len <= 0) {
        return -1;
    }
    response[len] = '\0';

    // Verify response format
    if (response[0] != '\x1b' || response[1] != '[') {
        return -1;
    }

    // Parse result
    if (sscanf(&response[2], "%d;%d", row, col) != 2) {
        return -1;
    }
    return 0;
}

int move_cursor(char* sequence, int sequence_len) {
    return write(STDOUT_FILENO, sequence, sequence_len) == sequence_len;
}
