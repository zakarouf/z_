#include "../../src/types/string.h"
#include "../../src/imp/test.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST(name) z__test_def(string, name)

TEST(new_and_replace_and_append) {
    /* Basic C (Null Terminated String) */
    const char *name = "Jason";

    /* Creating a Basic z__String using primitive types and strings */
    z__String s = z__String("Hello this is", name, "from Street No.", 31);
    z__test_assert(strncmp(s.data, "Hello this is Jason from Street No. 31", s.lenUsed) == 0, "Got: %s", s.data);

    /* Checking Replace */
    z__String_replace(&s, "%s left, at %i in the evening", name, 6);
    z__test_assert(strncmp(s.data, "Jason left, at 6 in the evening", s.lenUsed) == 0, "Got %s", s.data);

    /* Deleting String Object */
    z__String_delete(&s);

    
    /* Testing Append */
    s = z__String_new(31);
    z__String_append(&s, 0, ' ', "Eggs");
    z__String_append(&s, 0, ' ', ", Onions,");
    z__String_append(&s, 1, ' ', "Potatoes");
    z__String_append(&s, 1, ',', " Chilli Powder");
    z__String_append(&s, 3, '.', "");

    z__test_assert(strncmp(s.data, "Eggs, Onions, Potatoes, Chilli Powder...", s.lenUsed) == 0, "Got :%s", s.data);
    z__String_delete(&s);
    
    z__test_done();
}

TEST(split) {
    z__String s = z__String(
        "1. Oranges\n"
        "2. Bananas\n"
        "3. Apples\n"
        "4. Berries\n"
        "5. Melons\n"
        "6. Tomatoes\n"
        "7. Mytoes\n"
    );

    z__StringList list = z__String_splitTok(s, z__Str("\n", 1));
    z__test_assert_int(list.lenUsed, 7);
    z__test_assert(strcmp(list.data[2], "3. Apples") == 0, "Got: %s", list.data[2]);

    z__String_delete(&s);
    z__StringList_delete(&list);

    z__test_done();
}

TEST(tokens) {
    z__String s = z__String(
        "Step 1: Run,"
        "Step 2: Hide,"
        "Step 3: Cower,"
        "Step 4: Accept Fate"
    );

    z__u32 prev = 0;
    z__u32 i = z__String_tok(s, prev, z__Str(",", 1)); // i now points to [Run, <---- Here]
    z__test_assert(strncmp(s.data + prev, "Step 1: Run,", i-prev) == 0, "");

    prev = i;
    i = z__String_tok(s, prev, z__Str(",", 1));
    z__test_assert(strncmp(s.data + prev, "Step 2: Hide,", i-prev) == 0, "");

    prev = i;
    i = z__String_tok(s, prev, z__Str("4", 1)); // Something Different...
    z__test_assert(strncmp(s.data + prev, "Step 3: Cower,Step 4", i-prev) == 0, "");

    prev = i;
    i = z__String_tok(s, prev, z__Str(",", 1));
    z__test_assert(strncmp(s.data + prev, ": Accept Fate", i-prev) == 0, "");

    prev = i;
    i = z__String_tok(s, prev, z__Str(",", 1));
    z__test_assert(strncmp(s.data + prev, "", i-prev) == 0, "");

    z__test_done();

}

TEST(join) {
    z__String s = z__String_newFrom("Hello");
    z__String s2 = z__String_newFrom(", World!");
    z__String s3 = z__String_newFrom("42");

    z__test_assert(s.lenUsed == 5, "Got: %i", s.lenUsed);
    z__test_assert(s2.lenUsed == 8, "Got: %i", s2.lenUsed);
    z__test_assert(s3.lenUsed == 2, "Got: %i", s3.lenUsed);

    z__String_join(&s, &s2);
    z__test_assert(strncmp(s.data, "Hello, World!", s.lenUsed) == 0, "Got: %s|%u", s.data, s.lenUsed);
    
    z__String_join(&s, &s3);
    z__test_assert(strncmp(s.data, "Hello, World!42", s.lenUsed) == 0, "Got: %s|%u", s.data, s.lenUsed);

    z__test_done(
        z__String_delete(&s);
        z__String_delete(&s2);
        z__String_delete(&s3);
    );

}

z__test_export(string, new_and_replace_and_append, split, tokens, join);

