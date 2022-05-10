#include "../../src/types/arr.h"
#include "../../src/imp/test.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST(name) z__test_def(arr, name)

TEST(init_and_delete) {
    
    z__Arr(int) f = z__Arr_init(f, 1, 2, 3, 5, 6);
    
    z__test_assert(
        z__Arr_cmpdata(f, ((int[]){1, 2, 3, 5, 6}), 5 * sizeof(int)) == 0,"");

    z__Arr_delete(&f);
    z__test_done();
}

TEST(copy) {
    z__u64Arr arr, copy_arr;
    z__Arr_new(&arr, 32);
    
    z__Arr_foreach(i, arr, normal, 0, arr.len) {
        *i = random();
    }

    z__Arr_newCopy(&copy_arr, arr);
    
    z__test_assert(z__Arr_cmp(arr, copy_arr) == 0, "");
    z__Arr_delete(&arr);
    z__Arr_delete(&copy_arr);
    z__test_done();
}

z__test_impl(arr, init_and_delete, copy);

