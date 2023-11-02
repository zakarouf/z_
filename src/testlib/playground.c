#include "../lib/test.h"
#include "../lib/forrange.h"

#include "../lib/prep/args.h"
#include "../lib/prep/loop.h"
#include "../lib/prep/num.h"

#include "../lib/std/primitives.h"

#include "../lib/record.h"
#include "../lib/vector.h"
#include "../lib/arr.h"
#include "../lib/llist.h"
#include "../lib/string.h"
#include "../lib/hashset.h"

#include "../lib/bitf.h"

#include "../lib/obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define def(name) z__test_def(playground, name)

#define log(fmt, ...)\
    printf("%s:%u @ %s(): " fmt "\n", __FILE__, __LINE__, __func__ zpp__Args_Expandif((,), (), __VA_ARGS__));

def(main)
{
    z__test_assert(1, "");
    z__test_done();
}

z__test_impl(playground, main);

