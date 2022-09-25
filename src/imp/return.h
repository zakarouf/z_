#ifndef ZAKAROUF_Z_IMP__RETURN_H
#define ZAKAROUF_Z_IMP__RETURN_H

#include <stdnoreturn.h>
#include "../prep/base.h"

#define z__return_def(name, retval, ...)\
    goto zpp__CAT(_L_returnsk_, name);  \
    zpp__CAT(_L_return_, name): {       \
        __VA_ARGS__;                    \
        return retval;                  \
    } zpp__CAT2(_L_returnsk_, name):;

#define z__return_with(name) { goto zpp__CAT(_L_return_, name); }

#endif

