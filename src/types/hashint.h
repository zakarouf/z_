#ifndef ZAKAROUF__ZTYPES_TYPES__HASH_INT_H
#define ZAKAROUF__ZTYPES_TYPES__HASH_INT_H

#include "base.h"
#include "mem.h"
#include "../prep/nm/ident.h"
#include "../prep/num.h"

#define z__HashInt(T)\
    struct {                \
        struct {            \
            z__u32 key;     \
            T value;        \
            char is_set;    \
        } *entries;         \
        z__size len;        \
        z__size used;       \
    }

#define z__HashInt_new(ht)\
    {                                                                   \
        (ht)->len = 16;                                                 \
        (ht)->used = 0;                                                 \
        (ht)->entries = z__CALLOC(sizeof(*(ht)->entries), (ht)->len);   \
    }

#define z__HashInt_delete(ht)\
    {                           \
        z__FREE((ht)->entries); \
        (ht)->len = 0;          \
        (ht)->used = 0;         \
    }

#define z__PRIV__HashInt_sethash(_hash_key)\
    {\
        _hash_key = ((_hash_key >> 16) ^ _hash_key) * 0x45d9f3b;\
        _hash_key = ((_hash_key >> 16) ^ _hash_key) * 0x45d9f3b;\
        _hash_key = (_hash_key >> 16) ^ _hash_key;\
    }

#define z__PRIV__HashInt_set_entry(ht, hkey, val)\
    {\
        z__u32 _hash_key = hkey;                        \
        z__PRIV__HashInt_sethash(_hash_key);            \
        z__u32 _idx = _hash_key & ((ht)->len - 1);      \
        while((ht)->entries[_idx].is_set) {             \
            if((ht)->entries[_idx].key == _hash_key) {  \
                (ht)->entries[_idx].value = val;        \
                goto zpp__CAT(_hash_L_, __COUNTER__);   \
            }                                           \
            _idx += 1;                                  \
            if(_idx >= (ht)->len) {                     \
                _idx = 0;                               \
            }                                           \
        }                                               \
        (ht)->entries[_idx].key = hkey;                 \
        (ht)->entries[_idx].value = val;                \
        (ht)->entries[_idx].is_set = true;              \
        (ht)->used += 1;                                \
        zpp__CAT(_hash_L_, zpp__DEC(__COUNTER__)):;     \
    }

#define z__PRIV__HashInt_expand(ht)\
    {                                                                   \
        z__typeof(*ht) _tmphash = {                                     \
            .len = (ht)->len << 1,                                      \
            .used = 0,                                                  \
            .entries =                                                  \
                z__CALLOC(sizeof(*(ht)->entries), (ht)->len << 1)       \
        };                                                              \
                                                                        \
        if(_tmphash.entries) {                                          \
            for (size_t i = 0; i < (ht)->len; i++) {                    \
                if((ht)->entries[i].is_set) {                           \
                    z__PRIV__HashInt_set_entry(                         \
                        &_tmphash                                       \
                        , (ht)->entries[i].key                          \
                        , (ht)->entries[i].value                        \
                    );                                                  \
                }                                                       \
            }                                                           \
            z__FREE((ht)->entries);                                     \
            *(ht) = _tmphash;                                           \
        }                                                               \
    }                                                                   \

#define z__HashInt_set(ht, key, val)                \
    {                                               \
        if(((ht)->len >> 1) <= (ht)->used) {        \
            z__PRIV__HashInt_expand(ht);            \
        }                                           \
        z__PRIV__HashInt_set_entry(ht, key, val);   \
    }

#define z__HashInt_getreff(ht, key)\
    ({                                                  \
        z__typeof((ht)->entries->value) *reff = NULL;   \
        z__u32 _hashint = key;                          \
        z__PRIV__HashInt_sethash(_hashint);             \
        z__u32 _idx = _hashint & ((ht)->len - 1);       \
        if((ht)->entries[_idx].is_set) {                \
            reff =  &(ht)->entries[_idx].value;         \
        }                                               \
        reff;                                           \
    })

#define z__HashInt_foreach(e, ht)\
    for (z__typeof((ht)->entries) e = (ht)->entries; e < (ht)->entries + (ht)->len; e++)\
        if(e->is_set)

#endif

