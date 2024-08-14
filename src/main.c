#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_state.h"
#include "event_handler.h"
#include "rendering_controller.h"
#include "terminal.h"
#include "user_input_processor.h"
#include "user_input_reader.h"
#include "utils.h"

void load_file_rows(char *filename, editor_state *state, int rows);

int main(int argc, char *argv[]) {
    editor_state *state = editor_state_create();
    user_input user_input;
    user_event event;

    setup_terminal_io();
    terminal_size term_size = get_terminal_size();

    if (argc >= 2) {
        load_file_rows(argv[1], state, term_size.rows);
    }

    while (1) {
        refresh_screen(term_size, state);
        user_input = read_input();
        event = process_input(user_input);
        handle_event(event, state, term_size);
    }
    return 0;
}

void load_file_rows(char *filename, editor_state *state, int rows) {
    FILE *fp = fopen(filename, "r");
    if (!fp) panic("fopen");
    for (int i = 0; i < rows; i++) {
        char *line = NULL;
        size_t linecap = 0;
        ssize_t linelen;
        linelen = getline(&line, &linecap, fp);
        if (linelen != -1) {
            while (linelen > 0 &&
                   (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
                linelen--;
            editor_state_append_row(state, line, linelen);
        }
        free(line);
    }

    fclose(fp);
}