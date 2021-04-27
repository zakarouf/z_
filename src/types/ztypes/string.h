#ifndef ZAKAROUF__Z_TYPE_STRING_H
#define ZAKAROUF__Z_TYPE_STRING_H

#include "../config.h"

typedef char z__char;

typedef struct ZINT_STRING
{
    z__char * data;
    int size;
    int used;

}z__String;

typedef struct
{
    z__char **data;
    unsigned int *sizeofString;
    unsigned int lines;
    unsigned linesUsed;
}z__StringLines;

typedef struct
{
    z__StringLines *Sldata;
    int size;
    int used;
}z__StringLinesArr;


#define z__fillString_MF(String, val)\
    {memset(String.str, (val), String.size)}

#define z__String_getData(String)   (String).data
#define z__String_getLen(String)    (String).size
#define z__String_getUsed(String)   (String).used

#define z__StringLines_getUsed(ln)          (ln).linesUsed
#define z__StringLines_getLen(ln)           (ln).lines
#define z__StringLines_getStringLen(ln, l)  (ln).sizeofString[l]
#define z__StringLines_getLineData(ln, l)   (ln).data[l]
#define z__StringLines_getData(ln)          (ln).data

#define z__StringLinesArr_getLen(lns)           (lns).size
#define z__StringLinesArr_getUsed(lns)          (lns).used
#define z__StringLinesArr_getData(lns)          (lns).data
#define z__StringLinesArr_getDataLines(lns, l)  (lns).data[l]



z__String z__String_new(int size);
void z__String_delete(z__String * s);

void z__String_resize(z__String *str, int newsize);

void z__String_write(z__String *s, const z__char *st, int len);
void z__String_Copy(z__String *str, const z__String val);
z__String z__String_MakeCopy(const z__String str);

void z__Strint_append(z__String *str, const z__char* src, int length);
void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace);
z__String z__String_newFromFile(char filename[]);


z__StringLines z__StringLines_new(unsigned int base_lines_count);
void z__StringLines_delete(z__StringLines *strLines);

z__StringLines z__StringLines_newFrom(z__StringLines const *ln);
void z__StringLines_pushString(z__StringLines *ln ,z__String str);
void z__StringLines_push(z__StringLines *ln , char const * st, int len);
void z__StringLines_pop(z__StringLines *ln);

z__StringLines z__String_splitTok(z__String str, char const *restrict seperator);
z__StringLines z__String_splitTok_raw(char const *restrict stri, int len, char const *restrict seperator);
z__StringLines z__String_split_raw(char const *mainStr, int mainStrLen, char const *str, int str_len);


z__StringLinesArr z__StringLinesArr_new(int size, int x, int y);
void z__StringLinesArr_delete(z__StringLinesArr *lns);
void z__StringLinesArr_resize(z__StringLinesArr *lns, int newsize);



#endif

