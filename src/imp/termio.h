#ifndef ZAKAROUF__ZTYPES_IMP_TERMIO_H
#define ZAKAROUF__ZTYPES_IMP_TERMIO_H

#include "../types/string.h"

void z__termio_get_term_size(z__u32 * _Nonnull x, z__u32 * _Nonnull y);

z__u8 z__termio_getkey(void);               // Get Key Pressed
z__u8 z__termio_getkey_nowait(void);        // Get Key Pressed (non-interuptable)

int z__termio_kbhit(void);
void z__termio_nonblock(void);
void z__termio_block(void);

void z__termio_echo(int tog);

void z__termio_putchar(z__char c);
void z__termio_putString(const z__String * _Nonnull str);

#endif

