#ifndef ZAKAROUF_Z_IMP__TEST_H
#define ZAKAROUF_Z_IMP__TEST_H

#include "../prep/base.h"
#include "../prep/args.h"
#include "../prep/nm/assert.h"
#include "../prep/nm/string.h"

#include "sys.h"
#include "ansi.h"

#define z__PRIV__test_exception(fmt, ...)\
    ({ z__log_cl256(1\
        , " =>> " __FILE__ ":" zpp__to_string(__LINE__)  ": for test \"%s\", Assertion Failed!\n"\
          z__ansi_fmt((plain))                                              \
          fmt "\n" , _name_, ##__VA_ARGS__); return 0; })

#define z__test_assert(exp, fmt, ...)\
    zpp__assert_construct(exp, z__PRIV__test_exception, "For Expression: " #exp "\n" fmt ,##__VA_ARGS__)

#define z__test_assert_int(exp, expected) {\
        int e1 = exp; int e2 = expected;\
        zpp__assert_construct( e1 == e2, z__PRIV__test_exception, "Expected: %i\nGot: %i", e1, e2);\
    }

#define z__test_done() return 1;

#define z__test_def(suite, name)\
    static int zpp__CAT3(suite, , name)(char const * const _name_)

#define z__test_run(suite, ...)\
    ({                                                                                  \
        const char *fn_names[] = {zpp__Args_maplist(zpp__to_string, __VA_ARGS__)};      \
        int (*fn[])(const char *) = { zpp__Args_maplist_Pattern(suite,, __VA_ARGS__) }; \
        size_t passed = 0;                                                              \
        z__logfile_cl256(stdout, 5, "Running Suite \"" #suite "\"\n");\
        for (size_t i = 0; i < zpp__Args_Count(__VA_ARGS__); i++) {                   \
            if((fn[i])(fn_names[i])) {                                                \
                z__logfile_cl256(stdout, 6                                            \
                    , " -> Test [%zu/"\
                                  zpp__to_string(zpp__Args_Count(__VA_ARGS__))\
                                "] Passed O : %s\n"                                   \
                    , i+1, fn_names[i]);                                              \
                passed += 1;                                                          \
            } else {                                                                  \
                z__logfile_cl256(stdout, 1                                            \
                    , " -> Test [%zu/"\
                                  zpp__to_string(zpp__Args_Count(__VA_ARGS__))\
                                "] Failed X : %s\n", i+1, fn_names[i]);                 \
            }                                                                           \
        }                                                                               \
        z__logfile_cl256(stdout, 3                                                      \
            , "For Suite \"" #suite "\" %zu out of "                                        \
               zpp__to_string(zpp__Args_Count(__VA_ARGS__))                                 \
              " test passed & %zu failed\n", passed, zpp__Args_Count(__VA_ARGS__) - passed);\
        passed;                                                                             \
    })


#define z__test_expsu(suite)\
    int zpp__CAT(_test__, suite)(int *_total_)

#define z__test_defsu(suite, ...)\
    z__test_expsu(suite) {\
        *_total_ = zpp__Args_Count(__VA_ARGS__);\
        return z__test_run(suite, __VA_ARGS__);\
    }

#define z__test_callsu(suite, total) zpp__CAT(_test__, suite)(total); puts("");

#endif

