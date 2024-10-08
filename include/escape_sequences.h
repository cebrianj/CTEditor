#ifndef ESCAPE_SEQUENCES_H
#define ESCAPE_SEQUENCES_H

#define ESCAPE_SEQUENCE_PREFIX '\x1b'
#define ESCAPE_SEQUENCE_PREFIX_BYTES 1

#define HIDE_CURSOR_SEQUENCE "\x1b[?25l"
#define HIDE_CURSOR_SEQUENCE_BYTES 6
#define SHOW_CURSOR_SEQUENCE "\x1b[?25h"
#define SHOW_CURSOR_SEQUENCE_BYTES 6

#define CLEAR_CURSOR_TO_RIGHT_SEQUENCE "\x1b[0K"
#define CLEAR_CURSOR_TO_RIGHT_SEQUENCE_BYTES 4

#define CLEAR_SCREEN_SEQUENCE "\x1b[2J"
#define CLEAR_SCREEN_SEQUENCE_BYTES 4

#define CURSOR_TO_BEGINNING_SEQUENCE "\x1b[H"  // "\x1b[0:0H"
#define CURSOR_TO_BEGINNING_SEQUENCE_BYTES 3

#define CURSOR_TO_RIGHT "\x1b[999C"
#define CURSOR_TO_RIGHT_BYTES 6
#define CURSOR_TO_BOTTOM "\x1b[999B"
#define CURSOR_TO_BOTTOM_BYTES 6

#endif