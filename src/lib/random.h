#ifndef ZAKAROUF_Z__RANDOM_H
#define ZAKAROUF_Z__RANDOM_H

#include "std/primitives.h"

z__u64 z__rnd_spm64(z__u64 counter, z__u64 seed); 
z__u64 z__rnd_hash64_splitmix(z__u64 x);
z__u64 z__rnd_hash64_wang(z__u64 x);
z__u64 z__rnd_hash64_murmur(z__u64 x);

#ifdef Z__IMPLEMENTATION

z__u64 z__rnd_hash64_splitmix(z__u64 x)
{
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9ULL;
    x ^= x >> 27;
    x *= 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return x;
}

z__u64 z__rnd_hash64_wang(z__u64 x)
{
    x = (~x) + (x << 21);
    x = x ^ (x >> 24);
    x = (x + (x << 3)) + (x << 8);
    x = x ^ (x >> 14);
    x = (x + (x << 2)) + (x << 4);
    x = x ^ (x >> 28);
    x = x + (x << 31);
    return x;
}

z__u64 z__rnd_hash64_murmur(z__u64 x)
{
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return x;
}

z__u64 z__rnd_spm64(z__u64 x, z__u64 seed) 
{
    x ^= seed;
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9ULL;
    x ^= x >> 27;
    x *= 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return x;
}

#endif

#endif

