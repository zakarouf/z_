#ifndef ZAKAROUF__Z_TYPE_STRING_H
#define ZAKAROUF__Z_TYPE_STRING_H

#include "../config_types.h"

typedef char z__char;

typedef struct ZINT_STRING
{
    z__char * data;
    int len;
    int lenUsed;

}z__String;

typedef struct
{
    z__char **str_list;
    unsigned int *str_lens;
    unsigned int list_len;
    unsigned int list_lenUsed;
}z__StringList;

typedef struct
{
    z__StringList *data;
    int len;
    int lenUsed;
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
z__String z__String_new(int size);
void z__String_delete(z__String * s);

void z__String_resize(z__String *str, int newsize);

void z__String_write(z__String *s, const z__char *st, int len);
void z__String_Copy(z__String *str, const z__String val);
z__String z__String_MakeCopy(const z__String str);
z__String z__String_newfrom(const char *st, int size);

void z__Strint_append(z__String *str, const z__char* src, int length);
void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace);
z__String z__String_newFromFile(char filename[]);
void z__String_insertChar(z__String *dest, z__char ch, int pos);
void z__String_delChar(z__String *dest, int pos);


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

/* String List Array */
z__StringListArr z__StringListArr_new(int size, int x, int y);
void z__StringListArr_delete(z__StringListArr *lns);
void z__StringListArr_resize(z__StringListArr *lns, int newsize);


// Macros



#define z__StringList__PRIV_tmp_pushstr(v) z__StringList_push(&tmp, v, -1);
#define z__StringList_pushstr(...) zpp__Args_map(z__StringList__PRIV_tmp_pushstr, __VA_ARGS__)

#define z__StringList_init(...)\
({\
    z__StringList tmp = z__StringList_new(zpp__Args_Count(__VA_ARGS__)+1);\
    z__StringList_pushstr(__VA_ARGS__);\
    tmp;\
})


#endif

