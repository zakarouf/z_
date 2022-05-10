#include "../../src/types/hashhoyt.h"
#include "../../src/imp/test.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST(name) z__test_def(hashhoyt, name)

static int memctr = 0; // Counting memory allocation since we are dealing w/ macros
#define heapcall(f, ...) f(__VA_ARGS__); memctr+=1;
#define heapfree(f, ...) f(__VA_ARGS__); memctr-=1;

#define malloc(x) heapcall(malloc, x)
#define calloc(x, y) heapcall(calloc, x, y)
#define strdup(x) heapcall(strdup, x)

#define free(x) heapfree(free, x)



TEST(hashhoyt)
{
    z__HashHoyt(int) h;
    int *val = 0;

    z__HashHoyt_new(&h);

    z__HashHoyt_set(&h, "hello", 32);
    z__test_assert(memctr == 2, "Heap Alloc Counter %i", memctr);

    z__HashHoyt_getreff(&h, "hello", val);
    z__test_assert(*val == 32, "");

    z__HashHoyt_set(&h, "world", 96);
    z__test_assert(memctr == 3, "Heap Alloc Counter %i", memctr);

    z__HashHoyt_set(&h, "hello", 0xdead);
    z__test_assert(memctr == 3, "Heap Alloc Counter %i", memctr);

    z__HashHoyt_getreff(&h, "hello", val);
    z__test_assert(*val == 0xdead, "");

    z__HashHoyt_getreff(&h, "world", val);
    z__test_assert(*val == 96, "");

    z__HashHoyt_delete(&h);
    z__test_assert(memctr == 0, "Heap Alloc Counter %i", memctr);

    z__test_done();
}

z__test_impl(hashhoyt, hashhoyt);

