#include "../lib/test.h"
#include "../lib/forrange.h"

#include "../lib/prep/args.h"
#include "../lib/prep/loop.h"
#include "../lib/prep/num.h"

#include "../lib/types/primitives.h"

#include "../lib/types/record.h"
#include "../lib/types/vector.h"
#include "../lib/types/arr.h"
#include "../lib/types/llist.h"
#include "../lib/types/string.h"
#include "../lib/types/hashset.h"

#include "../lib/types/bitf.h"

#include "../lib/types/obj.h"
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

