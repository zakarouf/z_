#include "../../src/types/string.h"
#include "../../src/imp/test.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST(name) z__test_def(string, name)

TEST(new_and_replace) {
    const char *name = "Jason";

    z__String s = z__String("Hello this is", name, "from Street No.", 31);
    z__test_assert(strncmp(s.data, "Hello this is Jason from Street No. 31", s.lenUsed) == 0, "Got: %s", s.data);

    z__String_replace(&s, "%s left, at %i in the evening", name, 6);
    z__test_assert(strncmp(s.data, "Jason left, at 6 in the evening", s.lenUsed) == 0, "Got %s", s.data);

    z__String_delete(&s);
    z__test_done();
}

z__test_defsu(string, new_and_replace);
