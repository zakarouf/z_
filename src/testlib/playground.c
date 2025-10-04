#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Z__IMPLEMENTATION
#include "../lib/std/primitives.h"
#include "../lib/test.h"
#include "../lib/forrange.h"
#include "../lib/prep/args.h"
#include "../lib/prep/loop.h"
#include "../lib/prep/num.h"
#include "../lib/string.h"
#include "../lib/time.h"
#include "../lib/record.h"
#include "../lib/vector.h"
#include "../lib/arr.h"
#include "../lib/llist.h"
#include "../lib/string.h"
#include "../lib/hashset.h"
#include "../lib/bitf.h"
#include "../lib/obj.h"
#include "../lib/assert.h"
#include "../lib/scene.h"
#include "../lib/arena.h"

#define def(name) z__test_def(playground, name)

#define log(fmt, ...)\
    printf("%s:%u @ %s(): " fmt "\n", __FILE__, __LINE__, __func__ zpp__Args_Expandif((,), (), __VA_ARGS__));

#define z__PRIV__String_fmt(...) 

def(repeat) {
    int i = zpp__Repeat(2, +, 1);
    z__test_assert_int(i, 2);
    z__test_done();
}

/*
#include "../lib/bnf.h"
def(bnf)
{
    int i = zpp__Repeat(2, +, 1);
    z__test_assert_int(i, 2);

    z__Bnf grammer;
    z__Bnf_new(&grammer);

    #define n(as, ...) zpp__CAT(z__BnfNode_, as)(grammer.node_pool, __VA_ARGS__)
    #define val(x) ((z__Str){.data = x, .len = sizeof(x)-1})

    z__BnfNode *digit = 
        n(as_or, n(as_value, val("0"))
               , n(as_or, n(as_value, val("1"))
                   , n(as_or, n(as_value, val("2"))
                       , n(as_or, n(as_value, val("3"))
                           , n(as_or, n(as_value, val("4"))
                               , n(as_or, n(as_value, val("5"))
                                   , n(as_or, n(as_value, val("6"))
                                       , n(as_or, n(as_value, val("7"))
                                           , n(as_or, n(as_value, val("8"))
                                               , n(as_value, val("9"))
        )))))))));

    z__Bnf_add_rule(&grammer, "digit", 5, digit);

    z__BnfNode *numbers = 
        n(as_or, n(as_and
                    , n(as_rule, &grammer, val("digit"))
                    , n(as_rule, &grammer, val("digit")))
               , n(as_rule, &grammer, val("digit"))
        ); 

    z__Bnf_add_rule(&grammer, "numbers", 7, numbers);


    z__print_bnf(&grammer);

    z__test_assert(1, "");
    z__test_done();
}
#include "../lib/prep/base.h"
*/

typedef struct z__HashSetMeta z__HashSetMeta;
struct z__HashSetMeta {
    z__u32      *keys;
    z__u32      *values;

    z__u32Arr   unused_buff;

    z__u32      used;
    z__u32      capacity;
};


// refer to "../lib/tree.h" for ensuring all Assignment6
#include "../lib/soarr.h"
typedef struct Entities Entities;
z__SoArr(Entities, (z__u32, pos), (z__u32, id))

#include <stdio.h>

void print_utf8_chars(const char *utf8_str) {
    while (*utf8_str) {
        unsigned char c = *utf8_str;

        // Detect first byte of a UTF-8 sequence
        int num_bytes;
        if ((c & 0x80) == 0) num_bytes = 1;             // 1-byte ASCII
        else if ((c & 0xE0) == 0xC0) num_bytes = 2;     // 2-byte UTF-8
        else if ((c & 0xF0) == 0xE0) num_bytes = 3;     // 3-byte UTF-8
        else if ((c & 0xF8) == 0xF0) num_bytes = 4;     // 4-byte UTF-8
        else { utf8_str++; continue; }                  // Skip invalid byte

        printf("Char: ");
        for (int i = 0; i < num_bytes; i++) {
            printf("%02X ", (unsigned char)utf8_str[i]);
        }
        printf("\n");

        utf8_str += num_bytes;
    }
}

void z__print_bytes_as_bits(z__byte const *data, z__size size)
{
    for (size_t i = 0; i < size; i++) {
        z__byte byte = data[i];
        z__byte bits[8];
        for (int j = 7; j >= 0; j--) {
            bits[j] = (byte&1) + '0';
            byte = byte >> 1;
        }
        z__print("0b%.*s(0x%02hhx) ", 8, bits, data[i]);
    }
}


def(utf8) {

}

def(main) {
    Entities entt;
    Entities_new(&entt, 8);
    
    z__print_bytes_as_bits((z__byte[8]){ 0x80
                                , 0xE0
                                , 0xC0

                                , 0xF0
                                , 0xE0

                                , 0xF8
                                , 0xF0}, 7); 
    z__test_assert_int(1, 1);
    z__test_done();
}

z__test_impl(playground, main);

