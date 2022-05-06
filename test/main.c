#include "../src/imp/test.h"
#include <assert.h>

z__test_import(arr);
z__test_import(string);
z__test_import(hashhoyt);
z__test_import(imp_print);
z__test_import(playground);

int main (void)
{
    int total = 0, passed;
    passed = z__test_callsu(arr, &total);
    assert(passed == total);

    passed = z__test_callsu(string, &total);
    assert(passed == total);

    passed = z__test_callsu(hashhoyt, &total);
    assert(passed == total);

    passed = z__test_callsu(imp_print, &total);
    assert(passed == total);

    passed = z__test_callsu(playground, &total);
    assert(passed == total);

    return 0;
}
