#ifndef ZAKAROUF__ZTYPES_IMP_TERMIO_H
#define ZAKAROUF__ZTYPES_IMP_TERMIO_H

#include "../types/string.h"

z__u8 z__termio_getkey(void);               // Get Key Pressed
z__u8 z__termio_getkey_nowait(void);        // Get Key Pressed (non-interuptable)

int z__termio_kbhit(void);
void z__termio_nonblock(void);
void z__termio_block(void);


void z__termio_putchar(z__char c);
void z__termio_putString(const z__String * _Nonnull str);

z__String z__termio_readline(const char * _Nonnull msg);
void z__termio_add_history(z__String const * _Nonnull const str);

#endif

