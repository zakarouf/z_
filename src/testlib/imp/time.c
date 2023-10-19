#include "../../lib/time.h"
#include "../../lib/test.h"
#include <stdio.h>
#include <inttypes.h>

#define TEST_SUITE time
#define TEST(name) z__test_def(TEST_SUITE, name)

TEST(main)
{

    printf("time => %" PRIu64 "\n", z__time());
    printf("tps => %"PRIu64"\n", z__time_tps());
    printf("process time => %"PRIu64"\n", z__time_process());
    printf("Execution Time => %f\n", z__time_delta(0, z__time_process()));
    
    z__test_assert(1, ""); // Supress Warning
    z__test_done();
}

z__test_impl(TEST_SUITE, main);

