#include "../../src/types/bitf.h"
#include "../../src/imp/test.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_SUITE bit
#define TEST(name) z__test_def(TEST_SUITE, name)

static void print_bytebit(z__u8 b, char endchar)
{
    #define PRINT_BIT(offset)\
        fputc("01"[z__bit_has(b, offset)], stdout);

    PRINT_BIT(0);
    PRINT_BIT(1);
    PRINT_BIT(2);
    PRINT_BIT(3);
    PRINT_BIT(4);
    PRINT_BIT(5);
    PRINT_BIT(6);
    PRINT_BIT(7);
    fputc(endchar, stdout);
}

static void print_bytesbit(z__u8 b[static 1], z__size size)
{
    for (size_t i = 0; i < size; i++) {
        print_bytebit(b[i], ' ');
    }
    printf("\n");
}


TEST(bit)
{
    #define tassbit(x, n) z__bitf_has(x, n)

    z__u8 x[10] = {0};
    print_bytesbit(x, 10); 

    z__bitf_set(x, 12);
    z__bitf_set(x, 56);
    z__bitf_set(x, 22);
    z__bitf_set(x, 3);

    int y = 0;
    z__bitf_set(&y, 0);
    z__bitf_set(&y, 19);
    z__bitf_set(&y, 31);
    z__bitf_set(&y, 2);

    #define bitass(x)\
        zpp__static_assert((((x >> 3) + 1) << 3) > x)

    #define printsize(x)\
        printf("(%u %u) ", x, ((x >> 3) + 1) << 3);

    bitass(1);
    bitass(8);
    bitass(729480);
    bitass(0);
    
    z__test_assert(1, "");
    z__test_done();
}

z__test_impl(TEST_SUITE, bit);
