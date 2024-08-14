#include <errno.h>
#include <stdlib.h>

#include "editor_state.h"
#include "event_handler.h"
#include "rendering_controller.h"
#include "terminal.h"
#include "user_input_processor.h"
#include "user_input_reader.h"

editor_state state = {0};

int main() {
    user_input user_input;
    user_event event;

    setup_terminal_io();
    terminal_size term_size = get_terminal_size();
    while (1) {
        refresh_screen(term_size, &state);
        user_input = read_input();
        event = process_input(user_input);
        handle_event(event, &state, term_size);
    }
    return 0;
}
