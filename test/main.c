#include "../src/imp/test.h"
#include <assert.h>

z__test_import(types_base);
z__test_import(arr);
z__test_import(string);
z__test_import(hashhoyt);
z__test_import(types_obj);

z__test_import(imp_print);
z__test_import(time);

z__test_import(playground);

int main (void)
{
    int total = 0;

    /* Types */
    z__test_callsu(types_base, &total);
    z__test_callsu(arr, &total);
    z__test_callsu(string, &total);
    z__test_callsu(hashhoyt, &total);
    z__test_callsu(types_obj, &total);

    /* Imp */
    z__test_callsu(imp_print, &total);
    z__test_callsu(time, &total);

    /**/
    z__test_callsu(playground, &total);

    return 0;
}
