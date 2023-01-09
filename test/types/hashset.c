#include "../../src/types/hashset.h"
#include "../../src/imp/test.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_SUITE hashset
#define TEST(name) z__test_def(TEST_SUITE, name)

static int memctr = 0; // Counting memory allocation since we are dealing w/ macros
#define heapcall(f, ...) f(__VA_ARGS__); memctr+=1;
#define heapfree(f, ...) f(__VA_ARGS__); memctr-=1;

#define malloc(x) heapcall(malloc, x)
#define calloc(x, y) heapcall(calloc, x, y)
#define strdup(x) heapcall(strdup, x)
#define z__Str_newCopy(x) heapcall(z__Str_newCopy, x)

#define free(x) heapfree(free, x)

TEST(hashstr) {
    
    #define cstr(cstr) z__Str(cstr, sizeof(cstr)-1)

    #define tassheap(expected) \
        z__test_assert(memctr == expected, "Heap Alloc Counter at %i, expected %i", memctr, expected);

    #define tassval(k, v) \
        z__HashStr_getreff(&ht, cstr(k), &val);\
        z__test_assert(val != NULL, "%s Not Found", k);\
        z__test_assert(*val == v, "Value found incorrect, expected: `%d` but found `%d`", v, *val);

    #define set(k, v) z__HashStr_set(&ht, cstr(k), v)

    #define memctr_print() z__print("Memctr at %i\n", memctr);

    z__HashStr(int) ht;
    z__HashStr_new(&ht);
    tassheap(3);

    set("Mango", 1);        tassheap(4);
    set("Orange", 2);       tassheap(5);
    set("Banana", 3);       tassheap(6);
    set("Apple", 4);        tassheap(7);
    set("Velvet", 90);      tassheap(8);
    set("Vio", 12);         tassheap(9);
    set("R", 65);           tassheap(10);
    set("Mex", 22);         tassheap(11);
    set("TRESSSS", 124);    tassheap(12);

    z__HashSet_foreach(i, &ht) {
        printf("K(\"%s\") => %d\n", i.key->data, *i.value);
    }

    int *val = NULL;

    tassval("Mango", 1);
    tassval("Orange", 2);
    tassval("Banana", 3);
    tassval("Apple", 4);

    z__HashStr_delete(&ht);

    tassheap(0);
    memctr_print();
    

    z__test_done();
}

struct {
    z__i32 key; z__u64 value;
} const pairs[] = {
    #define s(k, v) { .key = k, .value = v},
    s(0, 1000)
    s(1, 1001) s(2, 1002) s(3, 1003)
    s(4, 1004) s(5, 1005) s(6, 1006)
    s(7, 1007) s(8, 1008) s(9, 1009)
    s(10, 1010)s(11, 1011)s(12, 1012)
    s(13, 1013)s(14, 1011)s(15, 1012)
    s(16, 1016)s(17, 1017)s(18, 1018)
    s(19, 1019)s(20, 1020)s(21, 1021)
    #undef s
};

TEST(hashint) {

    const z__u32 length = 22;

    z__HashInt(z__u64) ht;
    z__HashInt_new(&ht);

    for (size_t i = 0; i < length; i++) {
        z__HashInt_set(&ht, pairs[i].key, pairs[i].value);
    }

    for (size_t i = 0; i < length; i++) {
        z__u64 *value = NULL;
        z__HashInt_getreff(&ht, pairs[i].key, &value);
        z__test_assert(value, "value is null, for key `%i`", pairs[i].key);
        z__test_assert(*value == pairs[i].value, "{k(%i), v(%llu)} -> %llu", pairs[i].key, pairs[i].value, *value);
    }

    z__test_assert(1, "");
    z__test_done();
}

z__test_impl(TEST_SUITE, hashstr, hashint);

