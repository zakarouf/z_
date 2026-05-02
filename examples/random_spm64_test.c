#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Z__IMPLEMENTATION
#include <z_/std/mem.h>
#include <z_/utils.h>
#include <z_/random.h>
#include <z_/arr.h>

float u32_to_float(uint32_t x) {
    return z__u32norm(x);
//    return (x >> 8) * (1.0f / (1U << 24));
}


double to_unit_float(uint64_t x) {
    // Keep 53 bits and divide by 2^53
    return (x >> 11) * (1.0 / (1ULL << 53));
}

static void gen_rnd_new(z__u64 rand_pos, z__u64 rand_seed
    , z__u32 count, z__u32 range, z__u64Arr *array, z__u64(*rnd)(z__u64 v, z__u64 seed))
{
    z__Arr_new(array, count);
    for (size_t i = 0; i < count; i++) {
        array->data[i] = rnd(rand_pos, rand_seed) % range;
        rand_pos += 1;
    }
    array->lenUsed = count;
}

#include <z_/pairarr.h>
#include <ctype.h>


static void test_rndness(z__u64Arr *array)
{
    z__PairArr(z__u32, z__u32) dups;
    z__PairArr_new(&dups, array->lenUsed >> 2);
    for (size_t i = 0; i < array->lenUsed; i++) {
        z__u64 val = array->data[i];
        for (size_t j = 0; j < array->lenUsed; j++) {
            if(array->data[j] == val && j != i) {
                if(dups.lenUsed && dups.data_a[dups.lenUsed-1] == i) {
                    dups.data_b[dups.lenUsed-1] += 1;
                } else {
                    z__PairArr_push(&dups, i, 1);
                }
            }
        }
    }    

    printf("Total dups %"PRIu32 "\n\n", dups.lenUsed);
    for (size_t i = 0; i < dups.lenUsed; i++) {
        printf("at [%"PRIu32"] = %"PRIu64 " (%"PRIu32")\n"
                , dups.data_a[i], array->data[dups.data_a[i]], dups.data_b[i]);
    }

    z__PairArr_delete(&dups);
}

static void u64Arr_print(z__u64Arr *self)
{
    for (size_t i = 0; i < self->lenUsed; i++) {
        printf("[%zu] %"PRIu64 "\n", i, self->data[i]);
    }
}

z__u64 murmer(z__u64 x, z__u64 seed) {
    return z__rnd_hash64_murmur(x^seed);
}

z__u64 wang(z__u64 x, z__u64 seed) {
    return z__rnd_hash64_wang(x^seed);
}

int main(int argc, char *argv[])
{
    if(argc < 5) { printf("Usage: %s <pos> <seed> <count> <range> <rndtype>(w|m|s|all)", argv[0]); exit(-1); }
    z__bool all = 0;
    z__u64 (*rnd)(z__u64, z__u64);

    switch (argv[5][0]) {
        break; case 'a': all = 1;
        break; case 'm': rnd = murmer; printf("Using murmer\n");
        break; case 'w': rnd = wang; printf("Using wang\n");
        break; default: rnd = z__rnd_spm64; printf("Using spm\n");
    }

    if(!all) {
        z__u64Arr array;
        gen_rnd_new(      strtoull(argv[1], NULL, 10)
                           , strtoull(argv[2], NULL, 10)
                           , strtoull(argv[3], NULL, 10)
                           , strtoull(argv[4], NULL, 10)
                           , &array
                           , rnd);
        test_rndness(&array);
        z__Arr_delete(&array);
    } else {
        z__u64 (*rnds[3])(z__u64, z__u64) = { murmer, wang, z__rnd_spm64 };
        char *names[3] = {"murmer", "wang", "spm"};
        for (size_t i = 0; i < 3; i++) {
            z__u64Arr array;
            printf("Using %s\n", names[i]);
            gen_rnd_new(      strtoull(argv[1], NULL, 10)
                               , strtoull(argv[2], NULL, 10)
                               , strtoull(argv[3], NULL, 10)
                               , strtoull(argv[4], NULL, 10)
                               , &array
                               , rnds[i]);
            test_rndness(&array);
            z__Arr_delete(&array);
        }
    }

    return EXIT_SUCCESS;
}


