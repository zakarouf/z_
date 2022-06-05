#include "../../src/imp/argparse.h"
#include "../../src/imp/test.h"
#include "../../src/types/base.h"

#include <string.h>

#define TEST_SUITE imp_argparse
#define TEST(name) z__test_def(TEST_SUITE, name)

static
const char *argv[] = {
    "--run",
    "file"
};

static
const int argc = 2;

TEST(argparse) {
    
    int a;
    z__argp_start(argv, 0, argc) {
        z__argp_ifarg_custom(("a", 1), ("a", 2)) {
        
        }
        z__argp_ifarg(&a, ("a", 1))
    }
    

    z__test_done();
}

z__test_impl(TEST_SUITE, argparse);

