#include "../../src/imp/print.h"
#include "../../src/imp/test.h"

#define TEST(name) z__test_def(imp_print, name)

TEST(print) {
    
    z__fprint_cl256f(stdout, 4, "cl256f\n");
    z__fprint_vb(stdout, "vb Number => %d\n", 24);
    z__fprint_vb_cl256f(stdout, 32, "Hello\n");

    z__fprint_clrgb(stdout, 10, 52, 9, 100, 3, 52, "cl\n");
    z__fprint_clrgbf(stdout, 100, 3, 52, "clf\n");

    z__fprint_vb_clrgb(stdout, 10, 52, 9, 100, 3, 52, "vb\n");
    z__fprint_vb_clrgbf(stdout, 100, 3, 52, "\n");

    z__test_assert(1 == 1, "");

    z__test_done();
}

z__test_export(imp_print, print);

