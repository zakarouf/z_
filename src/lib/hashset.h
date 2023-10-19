#ifndef ZAKAROUF__ZTYPES_TYPES__HASH_SET_H
#define ZAKAROUF__ZTYPES_TYPES__HASH_SET_H

#include "std/primitives.h"
#include "std/mem.h"
#include "bitf.h"
#include "fnptr.h"
#include "string.h"

/**
 * Basic template for a hash table
 */
#define z__HashSet(K, V)\
    struct {            \
        K *keys;        \
        V *values;      \
        z__u8 *is_set;  \
        z__u32 len;     \
        z__u32 lenUsed; \
    }

/* Template for non-object k,v hash table types */
#define z__HashAtom(K, V) z__HashSet(K, V)

/* Template for string key hash table types */
#define z__HashStr(T) z__HashSet(z__Str, T)

/* Template for interger key */
#define z__HashInt(V) z__HashSet(z__i32, V)

/*** Interfaces ***/
/** z__HashSet Interface **/

#define z__PRIV__HashSet_new(ht, n)\
    {                                                               \
        (ht)->len = n;                                              \
        (ht)->lenUsed = 0;                                          \
        (ht)->keys = z__CALLOC(sizeof(*(ht)->keys), (ht)->len);     \
        (ht)->values = z__CALLOC(sizeof(*(ht)->values), (ht)->len); \
        (ht)->is_set = z__BITCALLOC((ht)->len, 1);                  \
    }


#define z__HashSet_new(ht) z__PRIV__HashSet_new(ht, 16) //< This thing should be a 16 or any other power of 2

#define z__HashSet_delete(ht)\
    {                               \
        z__FREE((ht)->keys);        \
        z__FREE((ht)->values);      \
        z__FREE((ht)->is_set);      \
    }

#define z__HashSet_reset_all(ht, key_decon, val_decon)\
    {\
        for (size_t i = 0; i < (ht)->len; i++) {                \
            if(z__bitf_has((ht)->is_set, i)) {                  \
                z__bitf_clear((ht)->is_set, i);                 \
                key_decon((ht)->keys + i);                      \
                val_decon((ht)->values + i);                    \
            }                                                   \
        }                                                       \
        (ht)->lenUsed = 0;                                      \
    }

#define z__HashSet_delete_with_decon(ht, key_decon, val_decon)\
    {                                                       \
        z__HashSet_reset_all(ht, key_decon, val_decon);     \
        z__HashSet_delete(ht);                              \
    }

#define z__HashSet_delete_with_key_decon(ht, key_decon)\
    z__HashSet_delete_with_decon(ht, key_decon, zpp__IGNORE)
    
#define z__HashSet_delete_with_val_decon(ht, val_decon)\
    z__HashSet_delete_with_decon(ht, zpp__IGNORE, val_decon)

#define z__HashSet_reset_all_memset(ht)\
    {                                                           \
        memset((ht)->len                                        \
            , 0, z__BIT_SIZE_DETERMINE_FOR_BYTES((ht)->len));   \
        (ht)->lenUsed = 0;                                      \
    }

#define z__PRIV__HashSet_set_entry(ht, key, val, key_copy, hashfn, key_cmpfn, ...)\
    {                                                               \
        z__u64 hash_k;                                              \
        hashfn(&hash_k, key);                                       \
        z__size _idx = (z__size)(hash_k & ((z__u64)(ht)->len - 1)); \
        while(z__bitf_has((ht)->is_set, _idx)) {                    \
            if (key_cmpfn((ht)->keys[_idx], key)) {                 \
                goto zpp__CAT(_hash_L_, __COUNTER__);               \
            }                                                       \
            _idx += 1;                                              \
            if (_idx >= (ht)->len) {                                \
                _idx = 0;                                           \
            }                                                       \
        }                                                           \
                                                                    \
        (ht)->keys[_idx] = key_copy(key);                           \
        (ht)->lenUsed += 1;                                         \
        z__bitf_set((ht)->is_set, _idx);                            \
        zpp__CAT(_hash_L_, zpp__DEC(__COUNTER__)):;                 \
        (ht)->values[_idx] = val;                                   \
        __VA_ARGS__;                                                \
    }

#define z__PRIV__HashSet_expand(ht, hashfn)\
    {                                                   \
        z__typeof(*(ht)) ht_new;                        \
        z__PRIV__HashSet_new(&ht_new, (ht)->len << 1);  \
        for (z__size i = 0; i < (ht)->len; i++) {       \
            if (z__bitf_has((ht)->is_set, i)) {         \
                z__u64 hash_k = 0;                      \
                hashfn(&hash_k, (ht)->keys[i]);         \
                z__size _idx = (z__size)(hash_k & ((z__u64)(ht_new).len - 1)); \
                while(z__bitf_has((ht_new).is_set, _idx)) {\
                    _idx += 1;                          \
                }                                       \
                (ht_new).keys[_idx] = (ht)->keys[i];    \
                (ht_new).values[_idx] = (ht)->values[i];\
                z__bitf_set((ht_new).is_set, _idx);     \
                (ht_new).lenUsed += 1;                  \
            }                                           \
        }                                               \
        z__HashSet_delete(ht);                          \
        *(ht) = ht_new;                                 \
    }

#define z__HashSet_set(ht, key, val, key_copy, hashfn, key_cmpfn, ...)\
    {                                                                                           \
        if((ht)->len/2 <= (ht)->lenUsed) {                                                      \
            z__PRIV__HashSet_expand(ht, hashfn);                                                \
        }                                                                                       \
        z__PRIV__HashSet_set_entry(ht, key, val, key_copy, hashfn, key_cmpfn ,##__VA_ARGS__);   \
    }

#define z__HashSet_getreff_r(ht, hkey, hashfn, key_cmpfn)\
    ({                                                              \
        z__typeof((ht)->values) valptr;                             \
        z__HashSet_getreff(ht, hkey, &valptr, hashfn, key_cmpfn);   \
        valptr;                                                     \
    })

#define z__HashSet_getreff(ht, hkey, valptr, hashfn, key_cmpfn)\
    {                                                               \
        *(valptr) = NULL;                                           \
        z__u64 hash_k;                                              \
        hashfn(&hash_k, hkey);                                      \
        z__size _idx = (z__size)(hash_k & ((z__u64)(ht)->len - 1)); \
        while(z__bitf_has((ht)->is_set, _idx)) {                    \
            if (key_cmpfn((ht)->keys[_idx], hkey)) {                \
                *(valptr) = &(ht)->values[_idx];                    \
                break;                                              \
            }                                                       \
            _idx += 1;                                              \
            if (_idx >= (ht)->len) {                                \
                _idx = 0;                                           \
            }                                                       \
        }                                                           \
    }

#define z__HashSet_foreach(i, ht)\
    for (struct {\
            z__typeof((ht)->keys) key;\
            z__typeof((ht)->values) value;\
        } i = {(ht)->keys, (ht)->values}; i.key < (ht)->keys + (ht)->len; i.key++, i.value++) if(z__bitf_has((ht)->is_set, (i.key - (ht)->keys)))


/** z__HashAtom Interface **/

#define z__HashAtom_new(ht) z__HashSet_new(ht)
#define z__HashAtom_delete(ht) z__HashSet_delete(ht)

#define z__HashAtom_delete_with_val_decon(ht, val_decon, ...)\
    {                                                           \
        for (size_t i = 0; i < (ht)->len; i++) {                \
            if(z__bitf_has((ht)->is_set, i)) {                  \
                val_decon((ht)->values ,##__VA_ARGS__);         \
            }                                                   \
        }                                                       \
        z__HashAtom_delete(ht);                                 \
    }

#define z__PRIV__HashAtom_newCopy(v) (v);
#define z__HashAtom_set(ht, hkey, val, hashfn, key_cmpfn, ...)\
    z__HashSet_set(ht, hkey, val, z__PRIV__HashAtom_newCopy, hashfn, key_cmpfn ,##__VA_ARGS__)

#define z__HashAtom_getreff(ht, hkey, valptr, hashfn, key_cmpfn)\
    z__HashSet_getreff(ht, hkey, valptr, hashfn, key_cmpfn)



/** z__HashStr Interface **/
#define z__HashStr_new(ht) z__HashSet_new(ht)
#define z__PRIV__HashStr_key_decon(k) z__FREE((k)->data)

#define z__HashStr_reset_all_val_decon(ht, val_decon)\
    { z__HashSet_reset_all(ht, z__PRIV__HashStr_key_decon, val_decon); }

#define z__HashStr_delete(ht) z__HashSet_delete_with_key_decon(ht, z__PRIV__HashStr_key_decon)
#define z__HashStr_delete_with_val_decon(ht, val_decon) z__HashSet_delete_with_decon(ht, z__PRIV__HashStr_key_decon, val_decon)

#define z__HashStr__PRIV__FNV_OFFSET 14695981039346656037UL
#define z__HashStr__PRIV__FNV_PRIME 1099511628211UL

#define z__PRIV__HashStr_hashfn(hash, str)\
    {                                                                                               \
        _Static_assert(sizeof(*(hash)) == sizeof(z__u64), "Size of Hash Number Should Be 8bytes");  \
        *(hash) = z__HashStr__PRIV__FNV_OFFSET;                                                     \
        for (const char* p = str.data                                                               \
            ; p - str.data < str.len; p++) {                                                        \
            *(hash) ^= (z__u64)(unsigned char)(*p);                                                 \
            *(hash) *= z__HashStr__PRIV__FNV_PRIME;                                                 \
        }                                                                                           \
    }

#define z__HashStr_set(ht, key, val, ...)\
    z__HashSet_set(ht, key, val, z__Str_newCopy, z__PRIV__HashStr_hashfn, z__Str_isequal ,##__VA_ARGS__)

#define z__HashStr_getreff(ht, hkey, valptr) z__HashSet_getreff(ht, hkey, valptr, z__PRIV__HashStr_hashfn, z__Str_isequal)


/** z__HashInt Interface **/
#define z__HashInt_new(ht) z__HashSet_new(ht)
#define z__HashInt_delete(ht) z__HashSet_delete(ht)
#define z__HashInt_delete_with_val_decon(ht, val_decon) z__HashSet_delete_with_val_decon(ht, val_decon)

#define z__PRIV__HashInt_isequal(x, y) (x == y)
#define z__PRIV__HashInt_hashfn(hash, hkey)\
    {                                                           \
        z__u32 _hash_key = hkey;                                \
        _hash_key = ((_hash_key >> 16) ^ _hash_key) * 0x45d9f3b;\
        _hash_key = ((_hash_key >> 16) ^ _hash_key) * 0x45d9f3b;\
        _hash_key = (_hash_key >> 16) ^ _hash_key;              \
        *(hash) = _hash_key;                                    \
    }

#define z__HashInt_set(ht, hkey, val, ...)\
    z__HashSet_set(ht, hkey, val, z__PRIV__HashAtom_newCopy, z__PRIV__HashInt_hashfn, z__PRIV__HashInt_isequal ,##__VA_ARGS__)

#define z__HashInt_getreff(ht, hkey, valptr) z__HashSet_getreff(ht, hkey, valptr, z__PRIV__HashInt_hashfn, z__PRIV__HashInt_isequal)

#endif

