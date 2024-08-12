#include "rendering_controller.h"

#include <stdio.h>
#include <unistd.h>

#include "buffer.h"
#include "escape_sequences.h"

void draw_rows(buffer* buffer, terminal_size term_size);
void draw_version_row(buffer* buffer, terminal_size term_size);
int create_move_cursor_sequence(char* buff, int buff_len, int cursor_x,
                                int cursor_y);

void refresh_screen(terminal_size term_size, editor_state state) {
    buffer buffer = BUF_INIT;
    buffer_append(&buffer, HIDE_CURSOR_SEQUENCE, HIDE_CURSOR_SEQUENCE_BYTES);
    buffer_append(&buffer, CURSOR_TO_BEGINNING_SEQUENCE,
                  CURSOR_TO_BEGINNING_SEQUENCE_BYTES);
    draw_rows(&buffer, term_size);
    buffer_append(&buffer, CURSOR_TO_BEGINNING_SEQUENCE,
                  CURSOR_TO_BEGINNING_SEQUENCE_BYTES);

    const int SEQUENCE_LEN = 32;
    char move_cursor_sequence[SEQUENCE_LEN];
    int move_cursor_sequence_bytes = create_move_cursor_sequence(
        move_cursor_sequence, SEQUENCE_LEN, state.cursor_x, state.cursor_y);

    buffer_append(&buffer, move_cursor_sequence, move_cursor_sequence_bytes);

    buffer_append(&buffer, SHOW_CURSOR_SEQUENCE, SHOW_CURSOR_SEQUENCE_BYTES);
    write(STDOUT_FILENO, buffer.string, buffer.len);
    buffer_free(&buffer);
}

int create_move_cursor_sequence(char* buff, int buff_len, int cursor_x,
                                int cursor_y) {
    return snprintf(buff, buff_len, "\x1b[%d;%dH", cursor_y + 1, cursor_x + 1);
}

void draw_rows(buffer* buffer, terminal_size term_size) {
    for (int i = 0; i < term_size.rows; i++) {
        if (i == term_size.cols / 4) {
            draw_version_row(buffer, term_size);
        } else {
            buffer_append(buffer, "~", 1);
        }
        buffer_append(buffer, CLEAR_CURSOR_TO_RIGHT_SEQUENCE,
                      CLEAR_CURSOR_TO_RIGHT_SEQUENCE_BYTES);
        if (i < term_size.rows - 1) {
            buffer_append(buffer, "\r\n", 2);
        }
    }
}
void draw_version_row(buffer* buffer, terminal_size term_size) {
    char msg[80];
    int msglen = snprintf(msg, sizeof(msg), "CTEditor -- version %s", "X.Y.Z");
    if (msglen > term_size.cols) msglen = term_size.cols;

    // Center text
    int padding = (term_size.cols - msglen) / 2;
    if (padding) {
        buffer_append(buffer, "~", 1);
        padding--;
    }
    while (padding--) buffer_append(buffer, " ", 1);
    buffer_append(buffer, msg, msglen);
}