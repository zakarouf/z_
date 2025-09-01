/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF_Z_IMP__TEST_H
#define ZAKAROUF_Z_IMP__TEST_H

#include "prep/base.h"
#include "prep/args.h"
#include "prep/nm/assert.h"
#include "prep/nm/string.h"

#include "print.h"
#include "ansifmt.h"
#include "typeof.h"

#ifndef z__PRIV__test_ON_ASSERT_FALIURE
#define z__PRIV__test_ON_ASSERT_FALIURE() goto _L_test_return;
#endif

#define z__PRIV__test_exception(fmt, ...)\
    ({ z__fprint_cl256f(stdout, 1,\
    " Assertion Failed!\n"                                                     \
    "   =>> " __FILE__ ":" zpp__to_string(__LINE__)  ": for test %i:\"%s\" \n"        \
          z__ansi_fmt((cl256_fg, 4), (bold))                                        \
          "Description: " z__ansi_fmt((plain)) "%s\n"                               \
          fmt "\n" , _id_, _name_, _description_, ##__VA_ARGS__); _name_ = 0; z__PRIV__test_ON_ASSERT_FALIURE(); })

#define z__test_assert(exp, fmt, ...)\
    zpp__assert_construct(exp, z__PRIV__test_exception,\
        z__ansi_fmt((bold)) "`" #exp "`\n" z__ansi_fmt((plain))\
            fmt ,##__VA_ARGS__)

#define z__test_assert_int(exp, expected) {         \
        z__typeof(exp) e1 = exp                     \
                     , e2 = expected;               \
        zpp__assert_construct(                      \
                e1 == e2                            \
                , z__PRIV__test_exception           \
                , "Expected: %i\nGot: %i", e2, e1); \
    }

#define z__test_done(...) {\
    _L_test_return:         \
    __VA_ARGS__;            \
    return (size_t)_name_;     \
}

#define z__test_def(suite, name)\
    static int zpp__CAT3(suite, , name)(char const * _name_, char const * _description_, const unsigned int _id_)

#define z__test_run(suite, ...)\
    ({                                                                                  \
        const char *fn_names[] = {zpp__Args_maplist(zpp__to_string, __VA_ARGS__)};      \
        int (*fn[])(const char *, const char *, const unsigned int) = {                 \
                zpp__Args_maplist_Pattern(suite,, __VA_ARGS__)                          \
        };                                                                              \
        size_t passed = 0;                                                              \
        z__fprint_cl256f(stdout, 5,                                                     \
                z__ansi_fmt((bold))                                                     \
                "Running Suite \"" #suite "\"\n");                                      \
        for (size_t i = 0; i < zpp__Args_Count(__VA_ARGS__); i++) {                     \
            z__fprint_cl256f(stdout, 4,                                                 \
                    " * Running Test [%zu/" zpp__to_string(zpp__Args_Count(__VA_ARGS__))"] \"%s\"\n"\
                    , i + 1, fn_names[i]);\
            if((fn[i])(fn_names[i], "", i)) {                                           \
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

#define z__test_impl(suite, ...)\
    z__PRIV__test_defsu(suite) {\
        *_total_ = zpp__Args_Count(__VA_ARGS__);\
        return z__test_run(suite, __VA_ARGS__);\
    }

#define z__test_implext(suite)\
    extern z__PRIV__test_defsu(suite)

#define z__test_callsu(suite, total) zpp__CAT(_test__, suite)(total);

#endif

