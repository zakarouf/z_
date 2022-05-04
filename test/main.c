#include "../src/imp/test.h"

z__test_expsu(arr);
z__test_expsu(string);

int main (int argc, char *argv[])
{
    int total = 0, passed;
    passed = z__test_callsu(arr, &total);
    passed = z__test_callsu(string, &total);
    
    return 0;
}
