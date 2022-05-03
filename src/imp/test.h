#ifndef ZAKAROUF_Z_IMP__TEST_H
#define ZAKAROUF_Z_IMP__TEST_H

#include "../prep/base.h"
#include "../prep/args.h"
#include "../prep/nm/assert.h"
#include "../prep/nm/string.h"

#include "sys.h"
#include "ansi.h"

#define z__PRIV__test_exception(exp, fmt, ...)\
    ({ z__log_cl256(1\
        , "Assertion Failed @ line "\
          #exp ": " zpp__to_string(__LINE__) "\n" z__ansi_fmt((plain)) fmt "\n" ,##__VA_ARGS__); return 0; })

#define z__test_assert(exp, fmt, ...) zpp__assert_construct(exp, z__PRIV__test_exception, exp, fmt ,##__VA_ARGS__)
#define z__test_done() return 1;

#define z__test_def(suite, name)\
    int zpp__CAT3(suite, , name)(void)

#define z__test_run(suite, ...)\
    {                                                                                 \
        const char *fn_names[] = {zpp__Args_maplist(zpp__to_string, __VA_ARGS__)};    \
        int (*fn[])(void) = { zpp__Args_maplist_Pattern(suite,, __VA_ARGS__) };       \
        size_t passed = 0;                                                            \
        z__logfile_cl256(stdout, 5, "Running Suite " #suite "\n");\
        for (size_t i = 0; i < zpp__Args_Count(__VA_ARGS__); i++) {                   \
            if((fn[i])()) {                                                           \
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
            , "For test " #suite " %zu out of "                                         \
               zpp__to_string(zpp__Args_Count(__VA_ARGS__))                             \
              " Passed & %zu Failed\n", passed, zpp__Args_Count(__VA_ARGS__) - passed); \
    }



#endif

