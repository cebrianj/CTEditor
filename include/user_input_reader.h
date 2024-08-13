#ifndef USER_INPUT_READER_H
#define USER_INPUT_READER_H

#include <errno.h>
#include <unistd.h>

#include "escape_sequences.h"
#include "user_input.h"
#include "utils.h"

user_input read_input();

#endif
