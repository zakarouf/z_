#ifndef ZAKAROUF__ZTYPES_IMP_TERMIO_H
#define ZAKAROUF__ZTYPES_IMP_TERMIO_H

#include "../types/string.h"

/**
 * Get Size of the Current Terminal
 */
void z__termio_get_term_size(z__u32 * _Nonnull x, z__u32 * _Nonnull y);

/**
 * Get a key input as char (blocking)
 */
z__u8 z__termio_getkey(void);

/**
 * Get a key input as char (non blocking)
 */
z__u8 z__termio_getkey_nowait(void);

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

#endif

