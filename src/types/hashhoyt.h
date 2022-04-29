#ifndef ZAKAROUF__ZTYPES_TYPES__HASH_HOYT_H
#define ZAKAROUF__ZTYPES_TYPES__HASH_HOYT_H


#include "base.h"
#include "mem.h"

// Must be multiple power of 2
#define Z___TYPE_CONFIG__HASH_INITIAL_SIZE 16

#define z__HashHoyt(T)\
    struct {                    \
        struct {                \
            char const *key;    \
            T value;            \
        } *entries;             \
        z__size len;            \
        z__size used;           \
    }


#define z__HashHoyt_new(ht)\
    {                                                       \
        (ht)->len = Z___TYPE_CONFIG__HASH_INITIAL_SIZE;     \
        (ht)->used = 0;                                     \
        (ht)->entries = z__New0(*(ht)->entries, (ht)->len); \
        if ((ht)->entries == NULL) {                        \
            (ht)->len = 0;                                  \
        }                                                   \
    }

#define z__HashHoyt_new_to_hold(ht, n)\
    {\
        z__size z__HashHoyt_new_to_hold__priv__n = n;\
        z__HashHoyt_new_to_hold__priv__n *= 2;\
        int z__HashHoyt_new_to_hold__priv__i = 0;\
        for(; z__HashHoyt_new_to_hold__priv__i<<1 < z__HashHoyt_new_to_hold__priv__n; z__HashHoyt_new_to_hold__priv__i++){}\
        (ht)->len = z__HashHoyt_new_to_hold__priv__i;       \
        (ht)->used = 0;                                     \
        (ht)->entries = z__New0(*(ht)->entries, (ht)->len); \
        if ((ht)->entries == NULL) {                        \
            (ht)->len = 0;                                  \
        }                                                   \
    }

#define z__HashHoyt_delete(ht)\
    {                                       \
        for(z__size i = 0; i < (ht)->len; i++) {\
            z__FREE((void *)(ht)->entries[i].key); \
        }                                   \
        z__FREE((ht)->entries);             \
        (ht)->len = 0;                      \
        (ht)->used = 0;                     \
    }


#define z__HashHoyt__PRIV__FNV_OFFSET 14695981039346656037UL
#define z__HashHoyt__PRIV__FNV_PRIME 1099511628211UL

static inline z__u64 z__HashHoyt_hashkey(const char *key)
{
    z__u64 hash = z__HashHoyt__PRIV__FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (z__u64)(unsigned char)(*p);
        hash *= z__HashHoyt__PRIV__FNV_PRIME;
    }
    return hash;
}

#define z__HashHoyt_getreff(ht, hkey, val)\
    {\
        (val) = NULL;\
        z__u64 hash_k = z__HashHoyt_hashkey(hkey);\
        z__size idx = (z__size)(hash_k & ((z__u64)(ht)->len - 1));\
        while((ht)->entries[idx].key != NULL) {\
            if (strcmp(hkey, (ht)->entries[idx].key) == 0) {\
                (val) = &(ht)->entries[idx].value;\
                break;\
            }\
            idx += 1;\
            if (idx > (ht)->len) { \
                idx = 0;\
            }\
        }\
    }

#define z__PRIV__HashHoyt_set_entry(ht, hkey, val)\
    {\
        z__u64 hash_k = z__HashHoyt_hashkey(hkey);\
        z__size idx = (z__size)(hash_k & ((z__u64)(ht)->len - 1));\
        while((ht)->entries[idx].key != NULL) {\
            if (strcmp(hkey, (ht)->entries[idx].key) == 0) {\
                (ht)->entries[idx].value = val;\
                break;\
            }\
            idx += 1;               \
            if (idx > (ht)->len) {  \
                idx = 0;            \
            }   \
        }       \
                \
        (ht)->entries[idx].key = strdup(hkey);\
        (ht)->entries[idx].value = val;      \
        (ht)->used += 1;                     \
    }

#define z__HashHoyt_set(ht, key, val)\
    {\
        if((ht)->len/2 <= (ht)->used) {\
            z__PRIV__HashHoyt__expand(ht);\
        }\
        z__PRIV__HashHoyt_set_entry(ht, key, val);\
    }

#define z__PRIV__HashHoyt__expand(ht)\
    {                                                       \
        z__size newsize = (ht)->len * 2;                    \
        z__typeof(*(ht)->entries)                           \
            *new_entries = z__New0(*new_entries, newsize);  \
                                                        \
        if (new_entries)                                \
        {                                               \
            z__typeof(*ht) htnew = {                        \
                .len = newsize,                             \
                .used = (ht)->used,                         \
                .entries = new_entries                      \
            };                                              \
            for (z__size i = 0; i < (ht)->len; i++) {   \
                if ((ht)->entries[i].key) {             \
                    z__PRIV__HashHoyt_set_entry(      \
                        &htnew,                 \
                        (ht)->entries[i].key,   \
                        (ht)->entries[i].value);\
                }                               \
            }                                   \
            z__FREE((ht)->entries);             \
            *(ht) = htnew;                      \
        }                                       \
    }

#define z__HashHoyt_foreach(e, ht)\
    for (z__typeof((ht)->entries) e = (ht)->entries; e < (ht)->len + (ht)->entries; e++)\
        if((e)->key != NULL)

#endif

