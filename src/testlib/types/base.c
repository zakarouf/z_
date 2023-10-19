#include "../../lib/types/primitives.h"
#include "../../lib/test.h"

#define TEST_SUITE types_primitives
#define TEST(name) z__test_def(TEST_SUITE, name)


TEST(size_evaluation)
{
    z__test_assert(sizeof(z__i8) == 1, "");
    z__test_assert(sizeof(z__i16) == 2, "");
    z__test_assert(sizeof(z__i32) == 4, "");
    z__test_assert(sizeof(z__i64) == 8, "");

    z__test_assert(sizeof(z__u8) == 1, "");
    z__test_assert(sizeof(z__u16) == 2, "");
    z__test_assert(sizeof(z__u32) == 4, "");
    z__test_assert(sizeof(z__u64) == 8, "");

    z__test_assert(sizeof(z__f32) == 4, "");
    z__test_assert(sizeof(z__f64) == 8, "");

    z__test_assert(sizeof(z__size) == 8, "");
    z__test_assert(sizeof(z__byte) == 1, "");
    z__test_assert(sizeof(z__byte) == sizeof(z__u8), "");
    z__test_assert(sizeof(z__ptr) == sizeof(z__size), "");

    z__test_done();
}

z__test_impl(TEST_SUITE, size_evaluation);

