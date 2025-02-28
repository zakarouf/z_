#include "../lib/test.h"
#include "../lib/arena.h"

#include <string.h>

#define TEST_SUITE arena
#define TEST(name) z__test_def(TEST_SUITE, name)

#define z__size_MB(x) (z__size_KB(x) * 1024)
#define z__size_KB(x) (x * 1024)
#define z__size_B(x) (x)

TEST(arena) {
    int sizes[10] = { 1023, 525, 10000, 23, 25
                    , 1100, 431, 23410, 89, 2521525 };
    z__size total_size = sizeof(z__Arena);

    z__Arena *arena = z__Arena_new(z__size_MB(13));
    
    for (size_t i = 0; i < 10; i++) {
        z__Arena_alloc(arena, sizes[i]);
        total_size += sizes[i];
    }
    
    z__size arena_used = z__Arena_total_used(arena);
    z__test_assert(arena_used == total_size, "%"PRIu64 " != %"PRIu64
            , arena_used, total_size);

    z__Arena_delete(arena);

    z__test_assert(1, "");
    z__test_done();
}

z__test_impl(TEST_SUITE, arena);
