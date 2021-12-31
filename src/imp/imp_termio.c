#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

#include "termio.h"

z__u8 z__termio_getkey(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    tcgetattr(0, &old);

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &old);
    read(0, &buf, 1);

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(0, TCSADRAIN, &old);

    return buf;
}


void z__termio_nonblock(void)
{
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;

    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
void z__termio_block(void)
{
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int z__termio_kbhit(void)
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void z__termio_add_history(z__String const * const str)
{
    add_history(str->data);
}

z__String z__termio_readline(const char *msg)
{
    z__String str = {
      .data = readline(msg)
    };

    str.len = strlen(str.data);
    str.lenUsed = str.len;

    return str;
}


