#ifndef ZAKAROUF__ZTYPES_IMP_TERMIO_H
#define ZAKAROUF__ZTYPES_IMP_TERMIO_H

#include "string.h"

/**
 * Get Size of the Current Terminal
 */
void z__termio_get_term_size(z__u32 * _Nonnull x, z__u32 * _Nonnull y);

/**
 * Get a key input as char (blocking)
 */
z__u8 z__termio_getchar(void);

/**
 * Get a key input as char (non blocking)
 */
z__u8 z__termio_getchar_nowait(void);

/**
 * Get Key Hit
 */
int z__termio_kbhit(void);

/**
 * Block Terminal io
 */
void z__termio_block(void);

/**
 * Un-Block Terminal io
 */
void z__termio_nonblock(void);

/**
 * Enable/Disable Key Echo
 */
void z__termio_echo(int tog);

/**
 * Put Char on terminal
 */
void z__termio_putchar(z__char c);

/**
 * Put a string on terminal
 */
void z__termio_putString(const z__String * _Nonnull str);


#ifdef Z__IMPLEMENTATION
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "std/primitives.h"
#include "string.h"

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

void z__termio_echo(int tog)
{
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if(tog) ttystate.c_lflag |= ECHO;
    else    ttystate.c_lflag &= ~ECHO;

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

z__u8 z__termio_getchar(void)
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

#define k(n) z__termio_key_##n
enum z__termio_key {
      k(null) = 0
    , k(soh)

    , k(space) = 32
    , k(tilde) = 126
    , k(delete) = 127

    , k(arrow_up) = 128
};

z__u32 z__termio_getkey(void)
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

z__u8 z__termio_getchar_nowait(void)
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

    z__u8 c = 0;
    if(z__termio_kbhit()) {
        c = fgetc(stdin);
    }

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    return c;
}

void z__termio_get_term_size(z__u32 *x, z__u32 *y)
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);
    *x = ws.ws_col;
    *y = ws.ws_row;
}

void z__termio_getln_b(z__String *str)
{
    while(true) {
        int key = z__termio_getkey();
        if (key == '\n') { return; }
        z__String_pushChar(str, key);
    }
}

z__String z__termio_getln(void)
{
    z__String str = z__String_new(64);
    z__termio_getln_b(&str);
    return str;
}

void z__termio_putString(z__String const * const str)
{
    fwrite(str->data, sizeof *str->data, str->len, stdout); 
}

#endif //Z__IMPLEMENTATION

#endif

