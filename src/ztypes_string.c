#include "ztypes_string.h"


#include <stdlib.h>
#include <string.h>


// Malloc And Free 2d Char, Orginally were Part of Ztorg (https://github.com/zakarouf/ztorg)
// Now Moved to Common String
static z__char **zse_calloc_2D_array_char (unsigned int x, unsigned int y) {

    z__char **arr = calloc(sizeof(z__char*), y);
    for (int i = 0; i < y; ++i)
    {
        arr[i] = calloc(sizeof(z__char), x);
    }

    return arr;

}
static void zse_free2dchar(z__char **mem, int size)
{
    for (int i = 0; i < size; ++i)
    {
        free(mem[i]);
    }
    free(mem);

}


static void *safe_realloc(void * data, size_t size)
{
    void *tmpdata = realloc(data, size);
    if (tmpdata != NULL)
    {
        if (tmpdata != data)
        {
            return tmpdata;
        }
    }
    return data;
}

// Strings

z__String z__String_create(int size)
{
    return (z__String){

        .data = calloc(sizeof(z__char) , size),
        .size = size,
        .used = 0
    };
}

inline void z__String_delete(z__String * s)
{
    free(s->data);
    s->size = 0;
    s->used = 0;
}

inline void z__String_resize(z__String *str, int newsize)
{
    str->size = newsize;
    str->data = safe_realloc(str->data, newsize);
}

void z__String_Copy(z__String *dest, const z__String val)
{
    if (dest->size < val.size )
    {
        z__String_resize(dest, val.size);
    }
    memcpy(dest->data, val.data, val.size);
}

z__String z__String_MakeCopy(const z__String str)
{

    z__String str2 = {
        .data = calloc(sizeof(z__char) , str.size),
        .size = str.size,
        .used = str.used
    };

    memcpy(str2.data, str.data, str.size);

    return str2;
}

z__String z__String_Link(const z__String str)
{
    return (z__String) {
        .data = str.data,
        .size = str.size,
        .used = str.used
    };
}

inline void z__Strint_append(z__String *str, const z__char *src, int length)
{
    if (length > 0)
    {
        if ((str->size-str->used) > length){
            memcpy(&str[str->used], src, length);

        } else {
            z__String_resize(str, length+str->size);
        }
        str->used += length;
    }
}

inline void z__String_write(z__String *s, const z__char *st)
{
    memcpy(s->data, st, s->size);
}

inline void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace)
{
    dest->size = dest->size + src->used + extraSpace;
    dest->data = reallocf(dest->data, dest->size);

    memcpy(&dest[dest->used], src->data, src->used);
}

/* See if `Char` exist in a string */
int z_findCharInStr(z__String str, z__char c, int fromIndex)
{
    for (int i = fromIndex; i < str.size; ++i)
    {
        if(str.data[i] == c)
            return i;
    }
    return -1;
}

z__StringLines z__StringLines_createEmpty(int x, int y)
{
    return (z__StringLines){
        .data = zse_calloc_2D_array_char(x, y),
        .sizeofString = x,
        .lines = y,
        .linesUsed = 0
    };
}
void z__StringLines_delete(z__StringLines *strLines)
{
    zse_free2dchar(strLines->data, strLines->lines);
    strLines->sizeofString = 0;
    strLines->lines = 0;
}

z__StringLines z__StringLines_MakeCopy(z__StringLines strLines)
{
    z__StringLines tmp = z__StringLines_createEmpty(strLines.sizeofString, strLines.lines);
    for (int i = 0; i < tmp.lines; ++i)
    {
        memcpy(tmp.data[i], strLines.data[i], tmp.sizeofString);
    }
    return tmp;
}

void z__StringLines_Resize_Y (z__StringLines *ln , unsigned int newsize)
{
    if (ln->lines > newsize)
    {
        for (int i = newsize; i < ln->lines; ++i)
        {
            free(ln->data[i]);
        }
        ln->data = safe_realloc(ln->data, sizeof(z__char*)*newsize);
        
    }
    else if (ln->lines < newsize)
    {
        ln->data = safe_realloc(ln->data, newsize);
        for (int i = ln->lines; i < newsize; ++i)
        {
            ln->data[i] = calloc(sizeof(z__char), ln->sizeofString);
        }
    }

    ln->lines = newsize;
}
void z__StringLines_Resize_X (z__StringLines *ln, unsigned int newsize)
{
    for (int i = 0; i < ln->lines; ++i)
    {
        ln->data[i] = reallocf(ln->data[i], sizeof(z__char) * newsize);
    }

    ln->sizeofString = newsize;   
}

z__StringLines z__String_spiltChar (z__String buffer, const char *restrict breaker)
{
    z__String tmp = z__String_MakeCopy(buffer);
    char *lastbuff = tmp.data;
    char *token = strtok_r(lastbuff, breaker, &lastbuff);

    int ycount = 0;
    while(token != NULL)
    {
        ycount += 1;
        token = strtok_r(lastbuff, breaker, &lastbuff);
    }

    lastbuff = tmp.data;

    z__StringLines returnVal = z__StringLines_createEmpty(128, ycount);

    for (int i = 0; i < returnVal.lines && token != NULL; ++i)
    {
        strcpy(returnVal.data[i], token);
        token = strtok_r(lastbuff, breaker, &lastbuff);
    }

    z__String_delete(&tmp);

    return returnVal;

}

void z__StringLines_pushString(z__StringLines *strLines, int len, const z__char *string)
{
    if (strLines->lines <= strLines->linesUsed )
    {
        z__StringLines_Resize_Y(strLines, strLines->linesUsed+8);
    }
    int linesUsed = strLines->linesUsed;

    if (len >= strLines->sizeofString)
    {
        z__StringLines_Resize_X(strLines, len+8);
    }    
    memcpy(strLines->data[linesUsed], string, len);
    strLines->linesUsed++;
}

z__StringLinesArr z__StringLinesArr_createEmpty(int size, int x, int y)
{
    z__StringLinesArr lns = {
        .Sldata = calloc(sizeof(z__StringLines), size),
        .size = size,
        .used = 0
    };

    for (int i = 0; i < lns.size; ++i)
    {
        lns.Sldata[i] = z__StringLines_createEmpty(x, y);
    }

    return lns;
}

void z__StringLinesArr_delete(z__StringLinesArr *lns)
{
    for (int i = 0; i < lns->size; ++i)
    {
        z__StringLines_delete(&lns->Sldata[i]);
    }
    lns->size = 0;
}

void z__StringLinesArr_resize(z__StringLinesArr *lns, int newsize)
{
    if (newsize < lns->size)
    {
        for (int i = newsize; i < lns->size; ++i)
        {
            z__StringLines_delete(&lns->Sldata[i]);
        }
        lns->Sldata = safe_realloc(lns->Sldata, sizeof(z__StringLines) * newsize);
        lns->size = newsize;
    }
    else if (newsize > lns->size)
    {
        lns->Sldata = safe_realloc(lns->Sldata, sizeof(z__StringLines) * newsize);
        lns->size = newsize;
        for (int i = lns->size; i < newsize; ++i)
        {
            lns->Sldata[i] = z__StringLines_createEmpty(lns->Sldata[0].sizeofString, lns->Sldata[0].lines);
        }
    }
}

// String END
