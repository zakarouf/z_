#include "../../lib/argparse.h"
#include "../../lib/test.h"
#include "../../lib/types/primitives.h"

#include <string.h>

#define TEST_SUITE imp_argparse
#define TEST(name) z__test_def(TEST_SUITE, name)

static
const char *argv[] = {
    "--run",
    "filename",
};

static
const int argc = sizeof(argv)/sizeof(*argv);

TEST(argparse) {
    
    int a;
    z__argp_start(argv, 0, argc) {
        z__argp_ifarg_custom(("-a", 1), ("--append", 1)) {
        
        }
        z__argp_ifarg(&a, ("a", 1)) {


        }
    }
    
    z__test_assert(1, "");
    z__test_done();
}

z__test_impl(TEST_SUITE, argparse);

