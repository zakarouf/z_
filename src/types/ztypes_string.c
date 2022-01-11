#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "mem.h"
#include "string.h"


#ifdef Z___TYPE_CONFIG__USE_STRING

    z__String z__String_new(int size)
    {
        return (z__String){

           .data= calloc(sizeof(z__char) , size),
            .len = size,
            .lenUsed = 0
        };
    }

    z__String z__String_newFromStr(const char *st, int size)
    {
        if (size == -1) {
            size = strlen(st);
        }

        z__String str = z__String_new(size + 8);
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

    int z__String_cmp(z__String const *s1, z__String const *s2)
    {
        if(s1->lenUsed != s2->lenUsed) return false;
        return !memcpy(s1->data, s2->data, s1->len * sizeof(*s1->data));
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

    inline void z__String_delete(z__String * s)
    {
        free(s->data);
        s->len = 0;
        s->lenUsed = 0;
    }

    inline void z__String_resize(z__String *str, int newsize)
    {
        str->len = newsize;
        str->data = z__mem_safe_realloc(str->data, newsize);
    }

    void z__String_Copy(z__String *dest, const z__String val)
    {
        if (dest->len < val.len )
        {
            z__String_resize(dest, val.len);
        }
        memcpy(dest->data, val.data, val.len);
    }

    z__String z__String_MakeCopy(const z__String str)
    {

        z__String str2 = {
           .data= calloc(sizeof(z__char) , str.len),
            .len = str.len,
            .lenUsed = str.lenUsed
        };

        memcpy(str2.data, str.data, str.len);

        return str2;
    }

    inline void z__Strint_append(z__String *str, const z__char *src, int length)
    {
        if (length > 0)
        {
            if ((str->len-str->lenUsed) > length){
                memcpy(&str->data[str->lenUsed], src, length);

            } else {
                z__String_resize(str, length+str->len);
            }
            str->lenUsed += length;
        }
    }

    inline void z__String_write(z__String *s, const z__char *st, int len)
    {
        if (len == -1) {
            len = strlen(st);
        }
        if (len > s->len) {
            z__String_resize(s, len+1);
        }

        memcpy(s->data, st, s->len);
        s->lenUsed = len;
    }

    inline void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace)
    {
        dest->len = dest->len + src->lenUsed + extraSpace;
        dest->data = reallocf(dest->data, dest->len);

        memcpy(&dest[dest->lenUsed], src->data, src->lenUsed);
    }

    void z__String_pushChar(z__String *dest, z__char ch)
    {
        if(dest->len <= dest->lenUsed) {
            z__String_resize(dest, dest->len + 8);
        }

        dest->data[dest->lenUsed] = ch;
        dest->lenUsed += 1;
    }

    void z__String_insertChar(z__String *dest, z__char ch, z__i32 pos)
    {
        if(pos >= dest->lenUsed && pos < 0) {
            return;
        }
        
        if (dest->len <= dest->lenUsed) {
            z__String_resize(dest, dest->len +8);
        }

        memmove(&dest->data[pos+1], &dest->data[pos], (dest->lenUsed - pos) * sizeof(*dest->data));
        dest->data[pos] = ch;
        dest->lenUsed += 1;
    }

    void z__String_delChar(z__String *dest, z__i32 pos)
    {
        if(pos >= dest->lenUsed && pos < 0) {
            return;
        }

        memmove(&dest->data[pos], &dest->data[pos+1], (dest->lenUsed - pos) * sizeof(*dest->data));
        dest->lenUsed -= 1;
        dest->data[dest->lenUsed] = '\0';
    }

    void z__String_replaceChar(z__String *dest, z__char ch, z__i32 pos)
    {
        if(pos >= dest->lenUsed && pos < 0) {
            return;
        }
        dest->data[pos] = ch;
    }
    
    z__String z__String_newFromFile(char const filename[])
    {
        FILE *f;

        if ((f = fopen(filename, "rb")) == NULL)
        {
            return (z__String) {
                NULL, 0, 0
            };
        }

        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

        z__char *string = malloc(fsize + 1);
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
            .str_list = calloc(base_lines_count, sizeof(*ln.str_lens)),
            .list_len = base_lines_count,
            .list_lenUsed = 0
        };
        ln.str_lens = calloc(base_lines_count, sizeof(*ln.str_lens));

        return ln;
    }

    void z__StringList_delete(z__StringList *ln)
    {
        for (z__u32 i = 0; i < ln->list_lenUsed; ++i)
        {
            free(ln->str_list[i]);
        }
        free(ln->str_list);
        free(ln->str_lens);

        ln->list_len = 0;
        ln->list_lenUsed = 0;
    }

    void z__StringList_pushString(z__StringList *ln ,z__String str)
    {
        if(ln->list_lenUsed >= ln->list_len) {
            ln->list_len += Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->str_list = z__mem_safe_realloc(ln->str_list, sizeof(*ln->str_list) *ln->list_len);
        }

        ln->str_list[ln->list_lenUsed] = calloc(str.lenUsed+1, sizeof(**ln->str_list));
        memcpy(ln->str_list[ln->list_lenUsed], str.data, str.lenUsed * sizeof(*str.data));
        ln->str_lens[ln->list_lenUsed] = str.lenUsed;
        ln->list_lenUsed += 1;
    }
    
    int z__StringList_replace(z__StringList *ln, z__u32 idx, char const * st, int len)
    {
        if(idx >= ln->list_lenUsed) {
            return -1;
        }
        if(len == -1) len = strlen(st);
        if(len > ln->str_lens[idx]) {
            ln->str_lens[idx] = len;
            z__FREE(ln->str_list[idx]);
            ln->str_list[idx] = z__CALLOC(sizeof(**ln->str_list), len);
        }
        memcpy(ln->str_list[idx], st, len);
        return 1;
    }

    void z__StringList_push(z__StringList *ln , char const * st, int len)
    {
        if(ln->list_lenUsed >= ln->list_len) {
            ln->list_len += Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->str_list = z__mem_safe_realloc(ln->str_list, sizeof(*ln->str_list) *ln->list_len);
            ln->str_lens = z__mem_safe_realloc(ln->str_lens, sizeof(*ln->str_lens) *ln->list_len);
        }

        if (len == -1) {
            len = strlen(st);
        }

        ln->str_list[ln->list_lenUsed] = calloc(len, sizeof(**ln->str_list));
        memcpy(ln->str_list[ln->list_lenUsed], st, len * sizeof(*st));
        ln->str_lens[ln->list_lenUsed] = len;
        ln->list_lenUsed += 1;
    }

    void z__StringList_pop(z__StringList *ln)
    {
        free(ln->str_list[ln->list_lenUsed-1]);
        ln->list_lenUsed -= 1;
        /*
        if (ln->list_len - ln->list_lenUsed >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
        {
            ln->list_len -= Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->str_list = z__mem_safe_realloc(ln->str_list, sizeof(*ln->str_list) *ln->list_len);
            ln->str_lens = z__mem_safe_realloc(ln->str_lens, sizeof(*ln->str_lens) *ln->list_len);
        }
        */
    }

    z__StringList z__StringList_clone(z__StringList const *ln)
    {
        z__StringList newln = {
            .list_len = ln->list_len,
            .list_lenUsed = ln->list_lenUsed
        };

        newln.str_lens = malloc(sizeof(*newln.str_lens) * newln.list_len);
        memcpy(newln.str_lens, ln->str_lens, sizeof(*newln.str_lens)*newln.list_len);

        newln.str_list = malloc(sizeof(*newln.str_list) * newln.list_len);

        for (z__u32 i = 0; i < newln.list_lenUsed; ++i) {
            newln.str_list[i] = malloc(sizeof(**newln.str_list) * newln.str_lens[i]);
            memcpy(newln.str_list[i], ln->str_list[i], newln.str_lens[i]);
        }

        return newln;
    }

    z__StringList z__String_splitTok(z__String str, char const *restrict seperator)
    {
        z__String tmp = z__String_MakeCopy(str);
        char *lastbuff = tmp.data;
        char *token = strtok_r(lastbuff, seperator, &lastbuff);

        /*Count*/
        int linesCount = 0;
        while(token) {

            linesCount += 1;
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        z__String_delete(&tmp);
        tmp = z__String_MakeCopy(str);

        lastbuff = tmp.data;
        token = strtok_r(lastbuff, seperator, &lastbuff);

        z__StringList ln = z__StringList_new(linesCount);

        while(token) {
            z__StringList_push(&ln, token, -1);
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        return ln;
    }

    z__StringList z__String_splitTok_raw(char const *restrict stri, int len, char const *restrict seperator)
    {
        if (len == -1)
        {
            len = strlen(stri);
        }
        
        char *tmp_stri = z__New0(*tmp_stri, len);
        memcpy(tmp_stri, stri, len);

        char *lastbuff = tmp_stri;
        char *token = strtok_r(lastbuff, seperator, &lastbuff);

        /*Count*/
        z__u32 linesCount = 0;
        while(token) {

            linesCount += 1;
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        free(tmp_stri);
        tmp_stri = malloc(len * sizeof(*tmp_stri));
        memcpy(tmp_stri, stri, len);

        lastbuff = tmp_stri;

        token = strtok_r(lastbuff, seperator, &lastbuff);

        z__StringList ln = z__StringList_new(linesCount);

        while(token) {
            z__StringList_push(&ln, token, -1);
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        return ln;
    }

    z__StringList z__String_split_raw(char const *mainStr, int mainStrLen, char const *str, int str_len)
    {
        if (str_len == -1)
        {
            str_len = strlen(str);
        }
        if (mainStrLen == -1)
        {
            mainStrLen = strlen(mainStr);
        }

        char *tmp_mainStr = malloc(sizeof(*tmp_mainStr) * mainStrLen);
        memcpy(tmp_mainStr, mainStr, mainStrLen);

        char *strst = strnstr(tmp_mainStr, str, mainStrLen);

        while(strst) {
            memset(strst, 0, str_len);
            strst += str_len;
            strst = strstr(strst, str);
        }

        strst = tmp_mainStr;
        z__StringList ln = z__StringList_new(8);

        z__i32 i = 0, len = 0;
        if (*strst)
        {
            i = strlen(strst);
            z__StringList_push(&ln, strst, i);
            strst += i + str_len;
        }

        while(i <= mainStrLen) {

            len = strnlen(strst, mainStrLen-i);
            z__StringList_push(&ln, strst, len);

            i += len+str_len;
            strst += len + str_len;
        }

        return ln;
    }

    z__String z__StringList_toString(z__StringList const ln)
    {
        z__size strSize = 0;
        for (z__u32 i = 0; i < ln.list_lenUsed; i++) {
            strSize += ln.str_lens[i];
        }

        z__String string = z__String_new(strSize + 8);

        for (z__u32 i = 0; i < ln.list_lenUsed; i++) {
            memcpy(&string.data[string.lenUsed], ln.str_list[i], ln.str_lens[i]);
            string.lenUsed += ln.str_lens[i];
        }

        return string;
    }

    z__StringListArr z__StringListArr_new(z__u32 size, z__u32 x)
    {
        z__StringListArr lns = {
            .data = calloc(sizeof(z__StringList), size),
            .len = size,
            .lenUsed = 0
        };

        for (int i = 0; i < lns.len; ++i)
        {
            lns.data[i] = z__StringList_new(x);
        }

        return lns;
    }

    void z__StringListArr_delete(z__StringListArr *lns)
    {
        for (int i = 0; i < lns->len; ++i)
        {
            z__StringList_delete(&lns->data[i]);
        }
        free(lns->data);
       lns->data = NULL;
        lns->len = 0;
    }

    void z__StringListArr_resize(z__StringListArr *lns, int newsize)
    {
        if (newsize < lns->len)
        {
            for (int i = newsize; i < lns->len; ++i)
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
            for (int i = lns->len; i < newsize; ++i)
            {
               lns->data[i] = z__StringList_new(lns->data[0].list_len);
            }
        }
    }

    // String END

#endif //Z___TYPE_CONFIG__USE_STRING
