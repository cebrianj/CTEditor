#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios initial_tsettings;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &initial_tsettings);

    struct termios raw = initial_tsettings;
    // Modify terminal input flags
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    // Modify terminal output flags
    raw.c_oflag &= ~(OPOST);

    // Modify terminal control mode flags
    raw.c_cflag |= (CS8);

    // Modify terminal local flags
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void set_stdin_min_read_size(int size) {
    struct termios tsettings;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tsettings);
    tsettings.c_cc[VMIN] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tsettings);
}

void set_stdin_timeout(int deciseconds) {
    struct termios tsettings;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tsettings);
    tsettings.c_cc[VTIME] = deciseconds;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tsettings);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &initial_tsettings);
}

int main() {
    enableRawMode();
    set_stdin_min_read_size(0);
    float timeout_deciseconds = 1;  // 0.1 second = 100ms = 1 decisecond
    set_stdin_timeout(timeout_deciseconds);
    atexit(disableRawMode);

    char c;
    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q') break;
    }
    return 0;
}