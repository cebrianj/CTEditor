#include "terminal_io.h"

#include <termios.h>
#include <unistd.h>

struct termios initial_tsettings;

void enableRawMode();

void set_stdin_min_read_size(int size);

void set_stdin_timeout(int deciseconds);

void disableRawMode();

struct termios get_terminal_settings();

void setup_terminal_io() {
    enableRawMode();
    set_stdin_min_read_size(0);
    int timeout_deciseconds = 1;  // 0.1 second = 100ms = 1 decisecond
    set_stdin_timeout(timeout_deciseconds);
    atexit(disableRawMode);
}

void enableRawMode() {
    initial_tsettings = get_terminal_settings();
    struct termios raw = initial_tsettings;
    // Modify terminal input flags
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    // Modify terminal output flags
    raw.c_oflag &= ~(OPOST);

    // Modify terminal control mode flags
    raw.c_cflag |= (CS8);

    // Modify terminal local flags
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        panic("Error trying to set terminal settings");
    }
}

void set_stdin_min_read_size(int size) {
    struct termios tsettings = get_terminal_settings();
    tsettings.c_cc[VMIN] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tsettings);
}

void set_stdin_timeout(int deciseconds) {
    struct termios tsettings = get_terminal_settings();
    tsettings.c_cc[VTIME] = deciseconds;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tsettings);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &initial_tsettings);
}

struct termios get_terminal_settings() {
    struct termios t_settings;
    if (tcgetattr(STDIN_FILENO, &t_settings) == -1) {
        panic("Error trying to retreive terminal settings");
    }
    return t_settings;
}
