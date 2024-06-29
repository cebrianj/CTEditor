#include "user_input_processor.h"

void process_key(char c) {
    switch (c) {
        case CTRL_WITH('q'):
            exit(0);
            break;
    }
}