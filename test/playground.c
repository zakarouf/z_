#include "../src/imp/test.h"
#include "../src/prep/args.h"
#include "../src/prep/loop.h"
#include "../src/prep/num.h"

#include "../src/types/base.h"

#include "../src/types/record.h"
#include "../src/types/vector.h"

#include "../src/types/obj.h"
#include <stdio.h>

#define def(name) z__test_def(playground, name)

#if defined (__clang__)
#define z__obj_dump(obj, f) __builtin_dump_struct(obj, f)
#endif

#define log(fmt, ...)\
    printf("%s:%u @ %s(): " fmt "\n", __FILE__, __LINE__, __func__ zpp__Args_Expandif((,), (), __VA_ARGS__));

#define z__AList(L, ...)

def(main)
{

    z__test_assert(1, ""); // Supress Warning
    z__test_done();
}

z__test_impl(playground, main);

