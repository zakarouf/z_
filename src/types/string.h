/**
 * @file string.h
 * @brief String Types
 */

#ifndef ZAKAROUF__Z_TYPE_STRING_H
#define ZAKAROUF__Z_TYPE_STRING_H

#include "../config_types.h"
#include "../prep/nm/assert.h"
#include "base.h"

typedef char z__char;

typedef struct z__String
{
    z__char * data;
    z__u32 len;
    z__u32 lenUsed;

}z__String;

typedef struct z__StringList
{
    z__char **data;
    z__u32 *slens;
    z__u32 len;
    z__u32 lenUsed;
}z__StringList;

typedef struct z__StringListArr
{
    z__StringList *data;
    z__u32 len;
    z__u32 lenUsed;
}z__StringListArr;


#define z__fillString_MF(String, val)\
    {memset(String.str, (val), String.len)}

#define z__String_getData(String)   (String).str
#define z__String_getLen(String)    (String).len
#define z__String_getUsed(String)   (String).used

#define z__StringList_getUsed(ln)          (ln).line_used
#define z__StringList_getLen(ln)           (ln).line_len
#define z__StringList_getStringLen(ln, l)  (ln).str_lens[l]
#define z__StringList_getLineData(ln, l)   (ln).line[l]
#define z__StringList_getData(ln)          (ln).line

#define z__StringListArr_getLen(lns)           (lns).size
#define z__StringListArr_getUsed(lns)          (lns).used
#define z__StringListArr_getData(lns)          (lns).Sldata
#define z__StringListArr_getDataLine(lns, l)  (lns).Sldata[l]


/* String */

/**
 * @def z__String_new(int size);
 * @brief Create a new String Type 
 * 
 * @param size Length of the string
 */
z__String z__String_new(int size);

/**
 * @def z__String_delete(z__String *s);
 * @brief Delete the allocated string type
 * 
 * @param str String type
 */
void z__String_delete(z__String *str);


/**
 * @def z__String_resize(z__String *str, int newsize)
 * @brief Resizes the string
 * 
 * @param str String
 * @param newsize Length of the string
 */
void z__String_resize(z__String *str, int newsize);


/**
 * @def z__String_copy(z__String *str, const z__String val);
 * @brief Copy the Data to / str from / val
 * 
 * @param str String
 * @param val String to be copied
 */
void z__String_copy(z__String *str, const z__String val);


/**
 * @def z__String_newCopy(const z__String val);
 * @brief Creates a new copy of string passed.
 * 
 * @param str String
 * @param val String to be copied
 */
z__String z__String_newCopy(const z__String str);

/**
 * @def z__String_cmp(z__String const *s1, z__String const *s2);
 */
int z__String_cmp(z__String const *s1, z__String const *s2);


int z__str_isalnum(char const *str, z__size len);
int z__str_isalpha(char const *str, z__size len);
int z__str_isradix(char const *str, z__size len);
int z__str_isdecimal(char const *str, z__size len);
const char *z__str_findchar(const char ch, char const *str, z__size len);


/**
 *
 */
void z__Strint_appendStr(z__String *str, const z__char* src, z__u32 length);
void z__String_append(z__String *str, unsigned pad, char padchar, char const* __restrict format, ...) __printflike(4, 5);
void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace);
z__String z__String_bind(char *str, z__int sz);

void z__String_replaceStr(z__String *str, const char * s, int len);
void z__String_replace(z__String *str, char const * __restrict format, ...) __printflike(2, 3);

char const *z__str_skipget_ws(char const *str, z__u32 size);
char const *z__str_skipget_nonws(char const *str, z__u32 size);
char const *z__str_find_chars(char const *str, z__u32 size, char const * tab, const z__size tabsize);
const char *z__str_get_next_word(const char *ori, z__u32 len, char const *cursor);
const char *z__String_get_next_word(const z__String *ori, char const *cursor);


z__String z__String_newFromFile(char const filename[]);
void z__String_insertChar(z__String *dest, z__char ch, z__u32 pos);
void z__String_delChar(z__String *dest, z__u32 pos);
void z__String_pushChar(z__String *dest, z__char ch);

z__String z__String_newFromStr(const char *st, int size);
z__String z__String_newFrom(char const * __restrict format, ...) __printflike(1, 2);



/* String List */
z__StringList z__StringList_new(unsigned int base_lines_count);
void z__StringList_delete(z__StringList *strList);

z__StringList z__StringList_clone(z__StringList const *ln);
void z__StringList_pushString(z__StringList *ln ,z__String str);
void z__StringList_push(z__StringList *ln , char const * st, int len);
const char *z__StringList_pushFmt(z__StringList *ln, char const * __restrict format, ...) __printflike(2, 3);
void z__StringList_pop(z__StringList *ln);
z__String z__StringList_toString(z__StringList const ln);

z__StringList z__String_splitTok(z__String str, char const * seperator);
z__StringList z__String_splitTok_raw(char const * stri, int len, char const * seperator);
z__StringList z__String_split_raw(char const *mainStr, int mainStrLen, char const *str, int str_len);
int z__StringList_replace(z__StringList *ln, z__u32 idx, char const * st, int len);

/* String List Array */
z__StringListArr z__StringListArr_new(z__u32 len, z__u32 linecount);
void z__StringListArr_delete(z__StringListArr *lns);
void z__StringListArr_resize(z__StringListArr *lns, z__u32 newsize);


// Macros

#define z__String(...) ({\
        zpp__Args_map_fn_Pattern(z__PRIV__String_checkformat,,,__VA_ARGS__);                            \
        z__String _tmp = z__String_newFrom(zpp__Args_map(z__PRIV__String_sformat, __VA_ARGS__),         \
                            zpp__Args_maplist_fn_Pattern(z__PRIV__typegen_primlist, ,, __VA_ARGS__));   \
        z__String str_out = z__String_newFrom(_tmp.data, __VA_ARGS__);                                  \
        z__String_delete(&_tmp);                                                                        \
        str_out;                                                                                        \
    })

#define z__StringList_init(...)\
    ({\
        z__StringList tmp = z__StringList_new(zpp__Args_Count(__VA_ARGS__)+1);\
        z__PRIV__StringList_pushstr(__VA_ARGS__);\
        tmp;\
    })



// Private stuff

#define z__PRIV__typegen_primlist(v) z__typegen_def((v), "",\
                , (char, "%c")   \
                , (z__i16, "%hi")    \
                , (z__u16, "%hu")    \
                , (z__i32, "%i")     \
                , (z__u32, "%u")     \
                , (z__i64, "%lli")   \
                , (z__u64, "%llu")   \
                \
                , (z__f32, "%f")    \
                , (z__f64, "%lF")   \
                \
                , (z__size, "%zu")  \
                \
                , (char *, "%s")            \
                , (const char *, "%s")      \
                , (void *, "%p")            \
              ) 
#define z__PRIV__String_sformat(...) "%s "

#define z__PRIV__String_checkformat(v) _Static_assert(sizeof(z__PRIV__typegen_primlist(v)) > 1, "Generic Format for this type is applied yet");

#define z__PRIV__StringList_tmp_pushstr(v) z__StringList_push(&tmp, v, -1);
#define z__PRIV__StringList_pushstr(...) zpp__Args_map(z__PRIV__StringList_tmp_pushstr, __VA_ARGS__)


#endif
