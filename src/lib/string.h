#ifndef ZAKAROUF__Z_IMP_STRING_H
#define ZAKAROUF__Z_IMP_STRING_H

#include "prep/map.h"
#include "prep/args.h"
#include "typegen.h"

#include "std/primitives.h"

typedef char z__char;

/**
 * String Object Type
 */
typedef struct z__String
{
    /* String data */
    z__char * data;

    /* Total Length Allocated */
    z__u32 len;

    /* Total Length in use */
    z__u32 lenUsed;

} z__String;

/**
 * Mutable String type, for slices
 */
typedef struct z__Str {

    /* String Data */
    z__char * data;

    /* String Length */
    z__u32 len;

}z__Str;

/**
 * Constant string type, for slices and c strings
 */
typedef struct z__CStr {

    /* String Data */
    z__char const * data;

    /* String Length */
    z__u32 len;

}z__CStr;


/**
 * List of Strings
 */
typedef struct z__StringList
{
    /* List Data */
    z__char **data;

    /* Length of Each String */
    z__u32 *slens;

    /* Length Allocated */
    z__u32 len;

    /* Length Used */
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



/* Str */
z__Str z__Str_newCopy(z__Str str);
int z__Str_isequal(z__Str str1, z__Str str2);
//***************************<>***************************//

/* CSTR */
/**
 * Skip all the non white spaces character, and returns the first occurrence when reached one.
 */
char const *z__str_skipget_ws(char const *str, z__u32 size);

/**
 * Skip all the white spaces characters; and
 * returns the first occurrence of a non white space character.
 */
char const *z__str_skipget_nonws(char const *str, z__u32 size);

/**
 * Find the First occurrence of any of the provided char list.
 */
char const *z__str_find_chars(char const *str, z__u32 size, char const * tab, const z__size tabsize);

/**
 * Returns the first occurrence of the next word
 * i.e First letter after finding (a/series of) white space
 */
char const *z__str_get_next_word(const char *ori, z__u32 len, char const *cursor);

/**
 * Compares string (s1 and s2), non case sensitive
 * Returns -> 0 : if equal
 *        |-> -n: if s1 < s2
 *        |-> +n: if s1 > s2
 */
z__i32 z__str_cmp_nocase(char const *s1, char const *s2, z__u32 len);

/**
 * Check if an entire string provided is alpha-numerical
 */
int z__str_isalnum(char const *str, z__size len);

/**
 * Check if an entire string provided is alphabatical
 */
int z__str_isalpha(char const *str, z__size len);

/**
 * Check if an entire string provided is non-decimal number
 */
int z__str_isradix(char const *str, z__size len);

/**
 * Check if an entire string provided is decimal number.
 */
int z__str_isdecimal(char const *str, z__size len);

/**
 * Finds and returns a pointer to the first occurrence of char `ch`
 * Returns NULL, if no such occurrences occurred.
 */
const char *z__str_findchar(const char ch, char const *str, z__size len);

/**
 */
const char *z__str_findchar_last(const char ch, char const *str, z__size len);

/**
 * Create a wrapper around a str. Use with caution if the `str` is no heap allocated.
 */
z__String z__String_bind(char *str, z__int sz);
//***************************<>***************************//


/* String */
/**
 * @def z__String_new(int size);
 * @brief Create a new String Type 
 * 
 * @param size Length of the string
 */
z__String z__String_new(int size);

z__String z__String_newFromStr(const char *st, int size);
z__String z__String_newFrom(char const * __restrict format, ...) __printflike(1, 2);
z__String z__String_newFromFile(char const filename[]);
z__String z__String_newCopy(const z__String str);

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
 * Expand the the total length allocated by a given length.
 */
void z__String_expand(z__String *str, z__size by);

/**
 * @def z__String_copy(z__String *str, const z__String val);
 * @brief Copy the Data to / str from / val
 * 
 * @param str String
 * @param val String to be copied
 */
void z__String_copy(z__String *str, const z__String val);

/**
 * @def z__String_cmp(z__String const *s1, z__String const *s2);
 */
int z__String_cmp(z__String const *s1, z__String const *s2);

/**
 * Append a string of length provided, into the str. Auto re-allocates if required
 */
z__String* z__String_append_str(z__String *str, const z__char *src, z__u32 length);

/**
 * Append a formated string provided similar to sprintf
 * Auto re-allocates if required
 */
z__String *z__String_append(z__String *str, unsigned pad, char padchar, char const* __restrict format, ...) __printflike(4, 5);
z__String *z__String_append_nopad(z__String *str, char const* __restrict format, ...) __printflike(2, 3);

/**
 * Append a string into onto another string
 */
void z__String_join(z__String *dest, z__String const *src);

/**
 * Replace an already initialized string with another c string.
 */
void z__String_replaceStr(z__String *str, const char * s, int len);

/**
 * Replace an already initialized string with a formated string
 * Re-allocates if necessary
 */
void z__String_replace(z__String *str, char const * __restrict format, ...) __printflike(2, 3);

/**
 * Replaces a segment of a string, from a given index and of a given length, with a formated string.
 * Re-allocates if necessary
 * If seg_len < 0, then overflow; 
 */
int z__String_replace_seg(z__String *str, z__size from, z__i64 seg_len, char const * __restrict format, ...) __printflike(4, 5);


z__i64 z__String_findchar(z__String const *str, z__char ch);
z__i64 z__String_findchar_last(z__String const *str, z__char ch);

/**
 * Same as z__str_get_next_word but applied on z__String
 */
char const *z__String_get_next_word(const z__String *ori, char const *cursor);

/**
 * Similar to strtok_r() but better and using indexing rather than pointers
 */
z__u64 z__String_tok(z__String const str, z__u64 prevtok, z__Str seperator);

/**
 * Skip the given token, opposite of z__String_tok.
 */
z__u64 z__String_tokskip(z__String const str, z__u64 prevtok, z__Str nest);

/**
 * Insert in between a string, moves string accordingly to fit in the char.
 */
void z__String_insertChar(z__String *dest, z__char ch, z__u32 pos);

/**
 * Deletes a char in-between a string
 * Moves string accordingly to close in the gap left behind
 */
void z__String_delChar(z__String *dest, z__u32 pos);

/**
 * Pushes a char at the end
 */
void z__String_pushChar(z__String *dest, z__char ch);
//***************************<>***************************//



/* String List */
/**
 * Create a new String List
 */
z__StringList z__StringList_new(unsigned int base_lines_count);

/**
 * Delete the String List
 */
void z__StringList_delete(z__StringList *strList);

/**
 * Creates a new String List copy from a given.
 */
z__StringList z__StringList_clone(z__StringList const *ln);

/**
 * Push a z__String into a String List
 */
void z__StringList_pushString(z__StringList *ln ,z__String str);

/**
 * Push A c string into the String List
 */
void z__StringList_push(z__StringList *ln , char const * st, int len);

/**
 * Push A Formated String List
 */
const char *z__StringList_pushFmt(z__StringList *ln, char const * __restrict format, ...) __printflike(2, 3);

/**
 * Pop the last String Value
 */
void z__StringList_pop(z__StringList *ln);

/**
 * Compile the Entire String List into a newly z__String
 */
z__String z__StringList_toString(z__StringList const ln);

/**
 * Create a new string list by spliting a string by a any tokenn.
 */
z__StringList z__String_splitTok(z__String str, z__Str seperator);

/**
 * Create a new string list by spliting a const c string/slice
 */
z__StringList z__String_splitTok_raw(z__Str const str, z__Str const seperator);

/**
 * Create a new string from spliting a string by the given word.
 */
z__StringList z__String_split(z__String str, z__Str word);

/**
 * Replace a string by the index value of the string list.
 */
int z__StringList_replace(z__StringList *ln, z__u32 idx, char const * st, int len);

/* String List Array */
z__StringListArr z__StringListArr_new(z__u32 len, z__u32 linecount);
void z__StringListArr_delete(z__StringListArr *lns);
void z__StringListArr_resize(z__StringListArr *lns, z__u32 newsize);


/* Macros */
/**
 * String Constructor
 */
#define z__String(...) ({\
        zpp__Args_map_fn_Pattern(z__PRIV__String_checkformat,,,__VA_ARGS__);                            \
        z__String _tmp = z__String_newFrom(zpp__Args_map(z__PRIV__String_sformat, __VA_ARGS__),         \
                            zpp__Args_maplist_fn_Pattern(z__PRIV__typegen_primlist, ,, __VA_ARGS__));   \
        z__String str_out = z__String_newFrom(_tmp.data, __VA_ARGS__);                                  \
        z__String_delete(&_tmp);                                                                        \
        str_out.lenUsed -= 1;                                                                           \
        str_out;                                                                                        \
    })

/**/
#define z__Str(str, l)\
        ((z__Str){.data = str, .len = l})

#define z__CStr(str, l)\
        ((z__CStr){.data = str, .len = l})

#define z__cstr(str) ((z__CStr){.data = str, .len = sizeof(str)-1})

#define z__StringList_init(...)\
    ({                                                                          \
        z__StringList tmp = z__StringList_new(zpp__Args_Count(__VA_ARGS__)+1);  \
        z__PRIV__StringList_pushstr(__VA_ARGS__);                               \
        tmp;                                                                    \
    })



// Private stuff

#define z__PRIV__typegen_primlist(v) z__typegen_def((v), "",\
                , (char, "%c")   \
                , (z__i16, "%" PRIi16)    \
                , (z__u16, "%" PRIu16)    \
                , (z__i32, "%" PRIi32)     \
                , (z__u32, "%" PRIu32)     \
                , (z__i64, "%" PRIi64)   \
                , (z__u64, "%" PRIu64)   \
                \
                , (z__f32, "%f")    \
                , (z__f64, "%lF")   \
                \
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
