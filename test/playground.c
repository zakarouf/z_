#include "../src/imp/test.h"

#define def(name) z__test_def(playground, name)

#if defined (__clang__)
#define z__obj_dump(obj, f) __builtin_dump_struct(obj, f)
#endif

def(main)
{
    z__obj_dump(stdout, &printf);
    z__test_done();
}

z__test_export(playground, main);

