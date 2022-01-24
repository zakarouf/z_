/**
 * @file string.h
 * @brief String Types
 */

#ifndef ZAKAROUF__Z_TYPE_STRING_H
#define ZAKAROUF__Z_TYPE_STRING_H

#include "../config_types.h"
#include "base.h"

typedef char z__char;

typedef struct z__String
{
    z__char * data;
    z__int len;
    z__int lenUsed;

}z__String;

typedef struct z__StringList
{
    z__char **str_list;
    z__u32 *str_lens;
    z__u32 list_len;
    z__u32 list_lenUsed;
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
void z__Strint_appendStr(z__String *str, const z__char* src, int length);
void z__String_append(z__String *str, unsigned pad, char padchar, char const* __restrict format, ...) __printflike(4, 5);
void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace);
z__String z__String_bind(char *str, z__int sz);

void z__String_replaceStr(z__String *str, const char * s, int len);
void z__String_replace(z__String *str, char const * __restrict format, ...) __printflike(2, 3);

char const *z__str_skipget_ws(char const *str, int size);
char const *z__str_skipget_nonws(char const *str, int size);
char const *z__str_find_chars(char const *str, int size, char const * tab, const z__size tabsize);
const char *z__str_get_next_word(const char *ori, z__size len, char const *cursor);
const char *z__String_get_next_word(const z__String *ori, char const *cursor);


z__String z__String_newFromFile(char const filename[]);
void z__String_insertChar(z__String *dest, z__char ch, int pos);
void z__String_delChar(z__String *dest, int pos);
void z__String_pushChar(z__String *dest, z__char ch);

z__String z__String_newFromStr(const char *st, int size);
z__String z__String_newFrom(char const * __restrict format, ...) __printflike(1, 2);



/* String List */
z__StringList z__StringList_new(unsigned int base_lines_count);
void z__StringList_delete(z__StringList *strList);

z__StringList z__StringList_clone(z__StringList const *ln);
void z__StringList_pushString(z__StringList *ln ,z__String str);
void z__StringList_push(z__StringList *ln , char const * st, int len);
void z__StringList_pop(z__StringList *ln);
z__String z__StringList_toString(z__StringList const ln);

z__StringList z__String_splitTok(z__String str, char const * seperator);
z__StringList z__String_splitTok_raw(char const * stri, int len, char const * seperator);
z__StringList z__String_split_raw(char const *mainStr, int mainStrLen, char const *str, int str_len);
int z__StringList_replace(z__StringList *ln, z__u32 idx, char const * st, int len);

/* String List Array */
z__StringListArr z__StringListArr_new(z__u32 len, z__u32 linecount);
void z__StringListArr_delete(z__StringListArr *lns);
void z__StringListArr_resize(z__StringListArr *lns, int newsize);


// Macros


#define z__StringList__PRIV_tmp_pushstr(v) z__StringList_push(&tmp, v, -1);
#define z__StringList__PRIV_pushstr(...) zpp__Args_map(z__StringList__PRIV_tmp_pushstr, __VA_ARGS__)

#define z__StringList_init(...)\
({\
    z__StringList tmp = z__StringList_new(zpp__Args_Count(__VA_ARGS__)+1);\
    z__StringList__PRIV_pushstr(__VA_ARGS__);\
    tmp;\
})


#endif

