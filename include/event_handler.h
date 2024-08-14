#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdlib.h>

#include "editor_state.h"
#include "terminal_size.h"
#include "user_event.h"

int handle_event(user_event event, editor_state* state,
                 terminal_size term_size);

#endif
