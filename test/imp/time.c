#include "../../src/imp/time.h"
#include "../../src/imp/test.h"
#include <stdio.h>

#define TEST_SUITE time
#define TEST(name) z__test_def(TEST_SUITE, name)

TEST(main)
{

    printf("time => %lld\n", z__time());
    printf("tps => %lld\n", z__time_tps());
    printf("process time => %lld\n", z__time_process());
    
    z__test_assert(1, ""); // Supress Warning
    z__test_done();
}

z__test_impl(TEST_SUITE, main);

