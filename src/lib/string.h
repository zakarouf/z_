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

#ifdef Z__IMPLEMENTATION
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#include "std/mem.h"

/**
 * Checks formats len required.
 */
static inline int _get_string_fmt_required_size(char const *__restrict format, va_list args)
{
    va_list args2;
    va_copy(args2, args);
    int size = vsnprintf(NULL, 0, format, args2);
    va_end(args2);
    return size;
}
/********************/

// Behaves same as strnstr
char *
z__str_findstr(const char *s, const char *find, size_t slen)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != '\0') {
		len = strlen(find);
		do {
			do {
				if (slen-- < 1 || (sc = *s++) == '\0')
					return (NULL);
			} while (sc != c);
			if (len > slen)
				return (NULL);
		} while (strncmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}

int z__str_isalnum(char const *str, z__size len)
{
    while(len > 0) {
        if(!isalnum(*str)) return 0;
        str++;
        len--;
    }
    return 1;
}

int z__str_isalpha(char const *str, z__size len)
{
    while(len > 0) {
        if(!isalpha(*str)) return 0;
        str++;
        len--;
    }
    return 1;
}

int z__str_isradix(char const *str, z__size len)
{
    while(len > 0) {
        if(!isdigit(*str)) return 0;
        str++;
        len--;
    }
    return 1;
}

int z__str_isdecimal(char const *str, z__size len)
{
    char dob = 0;

    while(len > 0) {
        if(!isdigit(*str)) {
            if(*str == '.') {
                dob += 1;
                goto _L_skip_return;
            }
            return 0;
        }

        _L_skip_return:
        str++;
        len--;
    }

    return (dob == 1);
}

const char *z__str_findchar(const char ch, char const *str, z__size len)
{
    while(len > 0) {
        if(*str == ch) return str;
        str++;
        len--;
    }
    return NULL;
}

const char *z__str_findchar_last(const char ch, char const *str, z__size len)
{
    str += len;
    while(len > 0) {
        if(*str == ch) return str;
        str--;
        len--;
    }
    return NULL;
}

char const *z__str_skipget_ws(char const *str, z__u32 size)
{
    while(size > 0
        &&(*str != ' '
          &&*str != '\n'
          &&*str != '\t')) {
        str++;
        size--;

    }
    return str;
}

char const *z__str_skipget_nonws(char const *str, z__u32 size)
{
    while(size > 0
        &&(*str == ' '
          ||*str == '\n'
          ||*str == '\t')) {
        str++;
        size--;
    }
    return str;
}

char const *z__str_find_chars(char const *str, z__u32 size, char const * tab, const z__size tabsize)
{
    while(size > 0){
        for(z__size i = 0; i < tabsize; i++) {
            if(*str == tab[i]) goto _L_return;
        }
        str++;
        size--;
    }
    
    return NULL;

    _L_return: {
        return str;
    }
}


const char *z__str_get_next_word(const char *ori, z__u32 len, char const *cursor)
{
    if(cursor < ori && cursor >= (ori + len)) {
        return NULL;
    }
    #define cursize(cursor) (len - (cursor - ori))
    char const *ws = z__str_skipget_ws(cursor, cursize(cursor));
    return z__str_skipget_nonws(ws, cursize(ws));

    #undef cursize
}

int z__str_check_ifchar(char x, z__Str list)
{
    for (size_t i = 0; i < list.len; i++) {
        if(x == list.data[i]) return 1;
    }
    return 0;
}

int z__str_cmp_nocase(const char *s1, const char *s2, z__u32 len)
{
    while (len != 0) {
        if(tolower(s1[len]) != tolower(s2[len])) {
            return tolower(s1[len]) - tolower(s2[len]);
        }
        len -= 1;
    }
    return 0;
}

/*******/
z__Str z__Str_newCopy(z__Str str)
{
    return (z__Str){
        .data = strndup(str.data, str.len),
        .len = str.len
    };
}

int z__Str_isequal(z__Str str1, z__Str str2)
{
    if(str1.len == str2.len) {
        return !strncmp(str1.data, str2.data, str1.len);
    }
    return 0;
}

z__String z__String_new(int size)
{
    return (z__String){
       .data= z__CALLOC(sizeof(z__char) , size+ 1),
        .len = size,
        .lenUsed = 0
    };
}

z__String z__String_newFromStr(const char *st, int size)
{
    if (size == -1) {
        size = strlen(st);
    }

    z__String str = z__String_new(size);
    memcpy(str.data, st, sizeof(*st) * size);
    str.lenUsed = size;

    return str;
}

z__String z__String_newFrom(char const * __restrict format, ...)
{
    va_list args, args_final;
    va_start(args, format);
    va_copy(args_final, args);

    z__size len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    z__String str = z__String_new(len + 1);
    str.lenUsed = vsnprintf(str.data, str.len, format, args_final);
    
    va_end(args_final);
     
    return str;
}

z__String z__String_newCopy(const z__String str)
{
    z__String str2 = {
       .data= z__CALLOC(sizeof(z__char) , str.len),
        .len = str.len,
        .lenUsed = str.lenUsed
    };

    memcpy(str2.data, str.data, str.len);

    return str2;
}

inline void z__String_delete(z__String * s)
{
    z__FREE(s->data);
    s->len = 0;
    s->lenUsed = 0;
}

void z__String_expand(z__String *str, z__size by)
{
    str->len += by;
    str->data = z__REALLOC(str->data, str->len);
}

void z__String_copy(z__String *dest, const z__String val)
{
    if (dest->lenUsed < val.lenUsed)
    {
        z__String_resize(dest, val.lenUsed + 1);
    }
    memcpy(dest->data, val.data, val.len);
    dest->lenUsed = val.lenUsed;
    dest->data[dest->lenUsed] = '\0';
}

z__i32 z__String_cmp(z__String const *s1, z__String const *s2)
{
    return s1->lenUsed == s2->lenUsed?
        memcmp(s1->data, s2->data, s1->len * sizeof(*s1->data)):
        (z__i32)((z__i32)(s1->lenUsed) - (z__i32)(s2->lenUsed));
}

z__i32 z__String_cmp_nocase(z__String const *s1, z__String const *s2)
{
    return s1->lenUsed == s2->lenUsed?
        z__str_cmp_nocase(s1->data, s2->data, s1->lenUsed):
        (z__i32)((z__i32)(s1->lenUsed) - (z__i32)(s2->lenUsed));
}

z__String z__String_bind(char *str, z__int sz)
{
    if(sz == -1) {
        sz = strlen(str);
    }
    return (z__String) {
        .data = str,
        .len = sz,
        .lenUsed = sz
    };
}

inline void z__String_resize(z__String *str, int newsize)
{
    str->len = newsize+1;
    str->data = z__mem_safe_realloc(str->data, newsize);
    str->data[newsize] = 0;
    if(str->lenUsed > str->len) str->lenUsed = str->len;
}


void z__String_replace(z__String *str, char const * __restrict format, ...)
{
    va_list args, args_final;
    va_start(args, format);
    va_copy(args_final, args);
    
    z__size len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if(len > str->len) {
        z__String_expand(str, len + 1);
    }

    str->lenUsed = vsnprintf(str->data, str->len, format, args_final);
    va_end(args_final);
}

int z__String_replace_seg(z__String *str, z__size from, z__i64 seg_len, char const * __restrict format, ...)
{
    if(from > str->lenUsed) return 0;

    va_list args, args_final;
    va_start(args, format);
    va_copy(args_final, args);
    z__size len = vsnprintf(NULL, 0, format, args);
    va_end(args);
  
    if(seg_len > 0) len = seg_len;
    if((len + from) > str->lenUsed) {
        if((len + from) > str->len) z__String_expand(str, len + 1);
        str->lenUsed = len + from;
        vsnprintf(str->data + from, len + 1, format, args_final);
    } else {
        z__char tmp = str->data[from + len]; // Circumvent null terminator added by vsnprintf
        vsnprintf(str->data + from, len, format, args_final);
        str->data[from + len] = tmp;
    }
    return len;
}

void z__String_replaceStr(z__String *str, const char * s, int len)
{
    if(len < 0) len = strlen(s);
    if((z__u32)len > str->len) { 
        z__String_expand(str, len + 1);
    }
    memcpy(str->data, s, sizeof(*s) * len);
    str->lenUsed = len;
    str->data[str->lenUsed] = 0;
}

z__String* z__String_append_str(z__String *str, const z__char *src, z__u32 length)
{
    if((str->len - str->lenUsed) > length){
        z__String_expand(str, length + 2);
    }
    memcpy(str->data + str->lenUsed, src, length);
    str->lenUsed += length;
    return str;
}

z__String *z__String_append(z__String *str, unsigned pad, char padchar, char const* __restrict format, ...)
{
    va_list args;
    va_start(args, format);
    z__size len = _get_string_fmt_required_size(format, args);

    if((len + pad) > (str->len - str->lenUsed)) {
        z__String_expand(str, (len + pad + 1));
    }

    memset(str->data + str->lenUsed, padchar, pad * sizeof(padchar));
    str->lenUsed += pad;
    vsnprintf(str->data + str->lenUsed, len + 1, format, args);
    str->lenUsed += len;

    va_end(args);
    return str;
}

z__String *z__String_append_nopad(z__String *str, char const* __restrict format, ...)
{
    va_list args;
    va_start(args, format);
    z__size const len = _get_string_fmt_required_size(format, args);

    if((len) > (str->len - str->lenUsed)) {
        z__String_expand(str, (len + 1));
    }

    vsnprintf(str->data + str->lenUsed, len + 1, format, args);
    str->lenUsed += len;

    va_end(args);
    return str;
}

inline void z__String_join(z__String *dest, z__String const *src)
{
    z__size const newsize = dest->lenUsed + src->lenUsed;
    if(newsize > dest->len) {
        z__String_expand(dest, src->lenUsed);
    }

    memcpy(dest->data + dest->lenUsed, src->data, src->lenUsed * sizeof(*src->data));
    dest->lenUsed = newsize;
    dest->data[newsize] = '\0';
}

void z__String_pushChar(z__String *dest, z__char ch)
{
    if(dest->len <= dest->lenUsed) {
        z__String_expand(dest, dest->len);
    }

    dest->data[dest->lenUsed] = ch;
    dest->lenUsed += 1;
}

void z__String_insertChar(z__String *dest, z__char ch, z__u32 pos)
{
    if(pos >= dest->lenUsed) {
        return;
    }
    
    if (dest->len <= dest->lenUsed) {
        z__String_resize(dest, dest->len +8);
    }

    memmove(&dest->data[pos+1], &dest->data[pos], (dest->lenUsed - pos) * sizeof(*dest->data));
    dest->data[pos] = ch;
    dest->lenUsed += 1;
}

void z__String_delChar(z__String *dest, z__u32 pos)
{
    if(pos >= dest->lenUsed) {
        return;
    }

    memmove(&dest->data[pos], &dest->data[pos+1], (dest->lenUsed - pos) * sizeof(*dest->data));
    dest->lenUsed -= 1;
    dest->data[dest->lenUsed] = '\0';
}

void z__String_replaceChar(z__String *dest, z__char ch, z__u32 pos)
{
    if(pos >= dest->lenUsed) {
        return;
    }
    dest->data[pos] = ch;
}

z__i64 z__String_findchar(z__String const *str, z__char ch)
{
    char const *ch_ptr = z__str_findchar(ch, str->data, str->lenUsed);
    if(ch_ptr == NULL) return -1;
    z__uptr at = str->lenUsed - (ch_ptr - str->data);
    return at;
}

z__i64 z__String_findchar_last(z__String const *str, z__char ch)
{
    char const *ch_ptr = z__str_findchar_last(ch, str->data, str->lenUsed);
    if(ch_ptr == NULL) return -1;
    z__uptr at = str->lenUsed - (ch_ptr - str->data);
    return at;
}

const char *z__String_get_next_word(const z__String *ori, char const *cursor)
{
    if(cursor < ori->data && cursor >= (ori->data + ori->lenUsed)) {
        return NULL;
    }
    #define cursize(cursor) (ori->lenUsed - (cursor - ori->data))
    char const *ws = z__str_skipget_ws(cursor, cursize(cursor));
    return z__str_skipget_nonws(ws, cursize(ws));

    #undef cursize
}

z__u64 z__String_tok(z__String const str, z__u64 prevtok, z__Str seperator)
{
    register size_t i = prevtok;
    register size_t j;
    for (; i < str.lenUsed; i++) {
        for (j = 0; j < seperator.len; j++) {
            if(seperator.data[j] == str.data[i]) {
                i += 1; if(i >= str.lenUsed) return i;
                while(z__str_check_ifchar(str.data[i], seperator)) {
                    i += 1; if(i >= str.lenUsed) return i;
                }
                return i;
            }
        }
    }

    return i;
}

z__u64 z__String_tokskip(z__String const str, z__u64 prevtok, z__Str nest)
{
    size_t i = prevtok;
    for (; i < str.lenUsed; i++) {
        for (register size_t j = 0; j < nest.len; j++) {
            if(nest.data[j] != str.data[i]) goto _L_return;
        }
    }
    _L_return:
    return i;
}

z__String z__String_newFromFile(char const filename[])
{
    FILE *f;

    if ((f = fopen(filename, "rb")) == NULL) {
        return (z__String) {
            NULL, 0, 0
        };
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    z__char *string = z__MALLOC(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = 0;
    return (z__String){
        .data= string
        ,.len = fsize +1
        ,.lenUsed = fsize +1
    };
}


z__StringList z__StringList_new(unsigned int base_lines_count)
{
    z__StringList ln = {
        .len = base_lines_count,
        .lenUsed = 0
    };
    ln.slens = z__CALLOC(base_lines_count, sizeof(*ln.slens));
    ln.data = z__CALLOC(base_lines_count, sizeof(*ln.data));

    return ln;
}

void z__StringList_delete(z__StringList *ln)
{
    for (z__u32 i = 0; i < ln->lenUsed; ++i) {
        z__FREE(ln->data[i]);
    }
    z__FREE(ln->data);
    z__FREE(ln->slens);

    ln->len = 0;
    ln->lenUsed = 0;
}

#define _z__StringList_expandif(l) \
    {\
        if((l)->lenUsed >= (l)->len) {\
            (l)->len += (l)->len;\
            (l)->data = z__REALLOC(                 \
                    (l)->data                       \
                  , sizeof(*(l)->data) * (l)->len); \
            (l)->slens = z__REALLOC(\
                    (l)->slens\
                  , sizeof(*(l)->slens) * (l)->len);\
        }\
    }

void z__StringList_pushString(z__StringList *ln ,z__String str)
{
    _z__StringList_expandif(ln);

    ln->data[ln->lenUsed] = z__CALLOC(str.lenUsed+1, sizeof(**ln->data));
    memcpy(ln->data[ln->lenUsed], str.data, str.lenUsed * sizeof(*str.data));
    ln->slens[ln->lenUsed] = str.lenUsed;
    ln->lenUsed += 1;
}

void z__StringList_push(z__StringList *ln , char const * st, int st_len)
{
    _z__StringList_expandif(ln);

    z__size len;
    if (st_len <= -1) {
        len = strlen(st);
    } else {
        len = st_len;
    }

    ln->data[ln->lenUsed] = z__MALLOC((len+1) * sizeof(*st));
    memcpy(ln->data[ln->lenUsed], st, len * sizeof(*st));

    ln->slens[ln->lenUsed] = len;
    ln->data[ln->lenUsed][len] = 0;
    ln->lenUsed += 1;
}

const char *z__StringList_pushFmt(z__StringList *ln, char const * __restrict format, ...)
{
    _z__StringList_expandif(ln);

    va_list args, args_final;
    va_start(args, format);
    va_copy(args_final, args);

    z__size len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    ln->data[ln->lenUsed] = z__MALLOC((len+1) * sizeof(**ln->data));
    ln->slens[ln->lenUsed] = vsnprintf(ln->data[ln->lenUsed], len, format, args_final);
    ln->lenUsed += 1;

    va_end(args_final);
     
    return ln->data[ln->lenUsed-1];
}

void z__StringList_pop(z__StringList *ln)
{
    if (ln->lenUsed <= 0) return;
    z__FREE(ln->data[ln->lenUsed-1]);
    ln->lenUsed -= 1;
    /*
    if (ln->len - ln->lenUsed >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
    {
        ln->len -= Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
        ln->data = z__mem_safe_realloc(ln->data, sizeof(*ln->data) *ln->len);
        ln->slens = z__mem_safe_realloc(ln->slens, sizeof(*ln->slens) *ln->len);
    }
    */
}

int z__StringList_replace(z__StringList *ln, z__u32 idx, char const * st, int st_len)
{
    if(idx >= ln->lenUsed) {
        return -1;
    }

    z__size len;
    if(st_len == -1) len = strlen(st);
    else len = st_len;

    if(len > ln->slens[idx]) {
        ln->slens[idx] = len;
        z__FREE(ln->data[idx]);
        ln->data[idx] = z__CALLOC(sizeof(**ln->data), len);
    }
    memcpy(ln->data[idx], st, len);
    return 1;
}

z__StringList z__StringList_clone(z__StringList const *ln)
{
    z__StringList newln = {
        .len = ln->len,
        .lenUsed = ln->lenUsed
    };

    newln.slens = z__MALLOC(sizeof(*newln.slens) * newln.len);
    memcpy(newln.slens
         , ln->slens
         , sizeof(*newln.slens)*newln.len);

    newln.data = z__MALLOC(sizeof(*newln.data) * newln.len);

    for (z__u32 i = 0; i < newln.lenUsed; ++i) {
        newln.data[i] = z__MALLOC(sizeof(**newln.data) * newln.slens[i]);
        memcpy(newln.data[i], ln->data[i], newln.slens[i]);
    }

    return newln;
}


z__StringList z__String_splitTok(z__String str, z__Str seperator)
{
    z__StringList ln = z__StringList_new(8);
    
    z__u32 start = 0;
    for (register size_t i = 0; i < str.lenUsed; i++) {
        for (register size_t j = 0; j < seperator.len; j++) {
            if(str.data[i] == seperator.data[j]) {
                z__StringList_push(&ln, &str.data[start], i - start);
                i += 1; if(i >= str.lenUsed) goto _L_return;
                while(z__str_check_ifchar(str.data[i], seperator)) {
                    i += 1; if(i >= str.lenUsed) goto _L_return;
                }
                start = i;
            }
        }
    }

    if(start < str.lenUsed) {
        z__StringList_push(&ln, &str.data[start], str.lenUsed - start);
    }

    _L_return:
    return ln;
}

z__StringList z__String_splitTok_raw(z__Str const str, z__Str const seperator)
{
    return z__String_splitTok(
            (z__String){
                .data = str.data,
                .len = str.len,
                .lenUsed = str.len
            }
            , seperator);
}

z__StringList z__String_split(z__String str, z__Str word)
{
    z__StringList ln = z__StringList_new(8);

    char *i = str.data;
    char *prev = i;
    char *endi = str.data + str.lenUsed;

    i = z__str_findstr(i, word.data, endi - i);
    if(i == NULL) {
        z__StringList_push(&ln, str.data, str.len);
        return ln;
    }

    do {
        z__StringList_push(&ln, prev, i - prev);
        prev = i + word.len;
        i = z__str_findstr(prev, word.data, endi - i);
    } while(i);
    
    if(prev < endi) {
        z__StringList_push(&ln, prev, endi - prev);
    }

    return ln;
}

z__String z__StringList_toString(z__StringList const ln)
{
    z__size strSize = 0;
    for (z__u32 i = 0; i < ln.lenUsed; i++) {
        strSize += ln.slens[i];
    }

    z__String string = z__String_new(strSize + 8);

    for (z__u32 i = 0; i < ln.lenUsed; i++) {
        memcpy(&string.data[string.lenUsed], ln.data[i], ln.slens[i]);
        string.lenUsed += ln.slens[i];
    }

    return string;
}

z__StringListArr z__StringListArr_new(z__u32 size, z__u32 x)
{
    z__StringListArr lns = {
        .data = z__CALLOC(sizeof(z__StringList), size),
        .len = size,
        .lenUsed = 0
    };

    for (z__u32 i = 0; i < lns.len; ++i)
    {
        lns.data[i] = z__StringList_new(x);
    }

    return lns;
}

void z__StringListArr_delete(z__StringListArr *lns)
{
    for (z__u32 i = 0; i < lns->len; ++i)
    {
        z__StringList_delete(&lns->data[i]);
    }
    z__FREE(lns->data);
   lns->data = NULL;
    lns->len = 0;
}

void z__StringListArr_resize(z__StringListArr *lns, z__u32 newsize)
{
    if (newsize < lns->len)
    {
        for (z__u32 i = newsize; i < lns->len; ++i)
        {
            z__StringList_delete(&lns->data[i]);
        }
       lns->data = z__mem_safe_realloc(lns->data, sizeof(z__StringList) * newsize);
        lns->len = newsize;
    }
    else if (newsize > lns->len)
    {
       lns->data = z__mem_safe_realloc(lns->data, sizeof(z__StringList) * newsize);
        lns->len = newsize;
        for (z__u32 i = lns->len; i < newsize; ++i)
        {
           lns->data[i] = z__StringList_new(lns->data[0].len);
        }
    }
}

// String END

#endif //Z__IMPLEMENTATION
#endif
