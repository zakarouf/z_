#include "../lib/test.h"
#include "../lib/prep/args.h"
#include <assert.h>
#include <stdlib.h>

#define import_sin(x) z__test_implext(x);
#define import(...) zpp__Args_map(import_sin, __VA_ARGS__)

#define testrun_sin(suite)\
    {                                               \
        int total = 0;                              \
        int passed = z__test_callsu(suite, &total);  \
        if(total != passed) {                       \
            z__fprint(stdout, "Test in suite \"" #suite "\" Failed!\n");    \
            abort();                                \
        }                                           \
    }

#define testrun(...)\
    zpp__Args_map(testrun_sin, __VA_ARGS__);\

#define test_list_types \
      types_primitives\
    , arr\
    , string\
    , hashset\
    , types_obj

#define test_list_imp \
      imp_print\
    , time\
    , scene\
    , arena

import(test_list_types);
import(test_list_imp);
import(playground);

void die(const char *msg)
{
    z__print("%s", msg);
    abort();
}

int main (void)
{
    /* Types */
    testrun(test_list_types);

    /* Imp */
    testrun(test_list_imp);

    /**/
    testrun(playground);

    z__print(
        z__ansi_fmt((bold))
            "All Test Passed"
        z__ansi_fmt((plain))
            "\n"
    );

    return 0;
}
