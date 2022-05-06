#ifndef ZAKAROUF_Z_IMP__TEST_H
#define ZAKAROUF_Z_IMP__TEST_H

#include "../prep/base.h"
#include "../prep/args.h"
#include "../prep/nm/assert.h"
#include "../prep/nm/string.h"

#include "print.h"
#include "ansi.h"

#define z__PRIV__test_exception(fmt, ...)\
    ({ z__fprint_cl256f(stdout, 1,\
    " =>> " __FILE__ ":" zpp__to_string(__LINE__)  ": for test %i:\"%s\", Assertion Failed!\n"\
          z__ansi_fmt((plain))                                              \
          fmt "\n" , _id_, _name_, ##__VA_ARGS__); _name_ = 0; goto _L_test_return; })

#define z__test_assert(exp, fmt, ...)\
    zpp__assert_construct(exp, z__PRIV__test_exception, "For Expression: " #exp "\n" fmt ,##__VA_ARGS__)

#define z__test_assert_int(exp, expected) {         \
        z__typeof(exp) e1 = exp                     \
                     , e2 = expected;               \
        zpp__assert_construct(                      \
                e1 == e2                            \
                , z__PRIV__test_exception           \
                , "Expected: %i\nGot: %i", e1, e2); \
    }

#define z__test_done(...) {\
    _L_test_return:         \
    __VA_ARGS__;            \
    return (size_t)_name_;     \
}

#define z__test_def(suite, name)\
    static int zpp__CAT3(suite, , name)(char const * _name_, const unsigned int _id_)

#define z__test_run(suite, ...)\
    ({                                                                                  \
        const char *fn_names[] = {zpp__Args_maplist(zpp__to_string, __VA_ARGS__)};      \
        int (*fn[])(const char *, const unsigned int) = {                               \
                    zpp__Args_maplist_Pattern(suite,, __VA_ARGS__)                      \
        };                                                                              \
        size_t passed = 0;                                                              \
        z__fprint_cl256f(stdout, 5,                                                     \
                z__ansi_fmt((bold))                                                     \
                "Running Suite \"" #suite "\"\n");                                      \
        for (size_t i = 0; i < zpp__Args_Count(__VA_ARGS__); i++) {                     \
            if((fn[i])(fn_names[i], i)) {                                               \
                z__fprint_cl256f(stdout, 6                                              \
                    , " -> Test [%zu/"\
                                  zpp__to_string(zpp__Args_Count(__VA_ARGS__))\
                                "] Passed O : %s\n"                                   \
                    , i+1, fn_names[i]);                                              \
                passed += 1;                                                          \
            } else {                                                                  \
                z__fprint_cl256f(stdout, 1                                            \
                    , " -> Test [%zu/"\
                                  zpp__to_string(zpp__Args_Count(__VA_ARGS__))\
                                "] Failed X : %s\n", i+1, fn_names[i]);                 \
            }                                                                           \
        }                                                                               \
        z__fprint_cl256f(stdout, 3                                                      \
            , "For Suite \"" #suite "\" %zu out of "                                        \
               zpp__to_string(zpp__Args_Count(__VA_ARGS__))                                 \
              " test passed & %zu failed\n\n", passed, zpp__Args_Count(__VA_ARGS__) - passed);\
        passed;                                                                             \
    })

#define z__PRIV__test_defsu(suite)\
    int zpp__CAT(_test__, suite)(int *_total_)

#define z__test_import(suite)\
    extern z__PRIV__test_defsu(suite)

#define z__test_export(suite, ...)\
    z__PRIV__test_defsu(suite) {\
        *_total_ = zpp__Args_Count(__VA_ARGS__);\
        return z__test_run(suite, __VA_ARGS__);\
    }

#define z__test_callsu(suite, total) zpp__CAT(_test__, suite)(total);

#endif

