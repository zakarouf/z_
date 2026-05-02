#include <math.h>
#define Z__IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <z_/arr.h>
#include <z_/string.h>

struct bm_State {
    z__u32Arr elements;
    z__u32 page_size;
    z__u64 total_pages;
    z__String msg;
};

typedef struct bm_State bm_State;

z__u64 powu(z__u64 x, z__u64 y)
{
    z__u64 total = 1;
    for (size_t i = 0; i < y; i++) {
        total *= x;
    }
    return total;
}

static void _generate_permutation_by_index(const z__u32 *elements, char *result, z__u32 M, z__u32 N, int index) {
    printf("\n");
    for (z__u32 i = 0; i < N; i++) {
        result[N - i - 1] = elements[index % M];
        index /= M;
        printf("perm>> %.*s\n", N, result);
    }
    result[N] = '\0';  // Null-terminate the string
}


static void _gen_perm(bm_State *bm, z__i64 page_n)
{
    if((bm->page_size) >= bm->msg.len) { z__String_expand(&bm->msg, bm->page_size + 1); }
    /**
    for (size_t i = 0; i < bm->page_size; i++) {
        bm->msg.data[bm->page_size - 1 - i] = bm->elements.data[page_n % bm->elements.lenUsed];
        page_n /= bm->elements.lenUsed;
    }
    */
    printf("msg size:%d", bm->msg.lenUsed);
    _generate_permutation_by_index(bm->elements.data,bm->msg.data, bm->elements.lenUsed, bm->page_size, page_n);
    bm->msg.lenUsed = bm->page_size;
}



void bm_State_new(bm_State *bm, z__u64 page_size, char const *elems, z__u32 const elem_count)
{
    bm->page_size = page_size;
    z__Arr_new(&bm->elements, elem_count);
    for (size_t i = 0; i < elem_count; i++) {
        bm->elements.data[i] = elems[i];
    }
    bm->total_pages = powu(elem_count, page_size);
    bm->msg = z__String_new(page_size);
}

void print_pages(bm_State *bm)
{
    printf("Total Pages: %"PRIu64"\n"
                "Page Size: %"PRIu32"\n", bm->total_pages
                           , bm->page_size);
    for (size_t i = 0; i < bm->total_pages; i++) {
        _gen_perm(bm, i);
        printf("Page:%zu\n%.*s\n", i, bm->msg.lenUsed, bm->msg.data);
    }
}

int main(int argc, char **argv) {
    // Create an array of A-Z and space (total 27 characters)
    char elements[28];  // 26 letters + space + null terminator
    for (int i = 0; i < 2; i++) {
        elements[i] = 'A' + i;
    }
    elements[3] = ' ';  // Add space at the end
    
    bm_State bm;
    bm_State_new(&bm, 2, elements,3);
    print_pages(&bm);

    return 0;
}
