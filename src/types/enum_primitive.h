#ifndef ZAKAROUF__ZTYPES_TYPES__ENUM_PRIMITIVE_H
#define ZAKAROUF__ZTYPES_TYPES__ENUM_PRIMITIVE_H


// Enum_tag_prefix: z__Enum__PRIV__tag__
// Enum_tag_of_prefix: z__Enum__datatag__ENUM__

#define z__Enum__PRIV__member

#define z__Enum_Tag(Tag, ...)\
    struct z__Enum__PRIV__tag__##Tag{ \
        union {                 \
            __VA_ARGS__;        \
        } data;                 \
        unsigned short _in_use; \
    }

#define z__Enum(Tag) struct z__Enum__PRIV__tag__##Tag

#define z__Enum_assign(en, of, val)\
    {                               \
        (en)->data.of = val;        \
        (en)->_in_use = of;         \
    }

#define z__Enum_assign_MC_nocheck(en, of, val) {                \
        memcpy((en)->data.of, val, sizeof((en)->data.of));      \
        (en)->_in_use = of;\
    }


#define z__Enum_match(en)\
    for(int keep = 1; keep; keep = 0)\
        for(z__typeof(en) *z__tmp__enum = &en; keep; keep ^= 1)\
            switch((z__tmp__enum)->_in_use)\

#define z__Enum_slot(dat, val) break; case dat: z__typeof((en).data.dat) *val = &(en).data.data;

#endif
