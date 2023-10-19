#ifndef ZAKAROUF__ZTYPES_TYPES__TYPEOF_H
#define ZAKAROUF__ZTYPES_TYPES__TYPEOF_H

#define z__typeof __typeof__
#define z__cont_typeof(T, mem) z__typeof(((T *)0)->mem)

#endif
