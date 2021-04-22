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
    unsigned int sizeofString;
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
    memset(String.str, (val), String.size)

#define z__StringGetLen_MF(String)\
    (z__String)String.size;    

#define z__StringGetUsed_MF(String)\
    (z__String)String.used;    

int z_findCharInStr(z__String str, z__char c, int fromIndex);

z__String z__String_create(int size);
void z__String_delete(z__String * s);
void z__String_resize(z__String *str, int newsize);
void z__String_Copy(z__String *str, const z__String val);
z__String z__String_MakeCopy(const z__String str);
z__String z__String_Link(const z__String str);
void z__Strint_append(z__String *str, const z__char* src, int length);
void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace);
z__String z__String_createFromFile(char filename[]);


z__StringLines z__StringLines_createEmpty(int x, int y);
void z__StringLines_delete(z__StringLines *strLines);
void z__StringLines_Resize_Y (z__StringLines *ln , unsigned int newsize);
void z__StringLines_Resize_X (z__StringLines *ln, unsigned int newsize);
z__StringLines z__StringLines_MakeCopy(z__StringLines strLines);
z__StringLines z__String_spiltChar(z__String buffer, const char * breaker);
void z__StringLines_pushString(z__StringLines *strLines, int len, const char *string);


z__StringLinesArr z__StringLinesArr_createEmpty(int size, int x, int y);
void z__StringLinesArr_delete(z__StringLinesArr *lns);
void z__StringLinesArr_resize(z__StringLinesArr *lns, int newsize);



#endif

