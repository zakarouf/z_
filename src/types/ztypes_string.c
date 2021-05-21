#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mem.h"
#include "string.h"


#ifdef Z___TYPE_CONFIG__USE_STRING

    z__String z__String_new(int size)
    {
        return (z__String){

            .str = calloc(sizeof(z__char) , size),
            .len = size,
            .used = 0
        };
    }

    inline void z__String_delete(z__String * s)
    {
        free(s->str);
        s->len = 0;
        s->used = 0;
    }

    inline void z__String_resize(z__String *str, int newsize)
    {
        str->len = newsize;
        str->str = z__mem_safe_realloc(str->str, newsize);
    }

    void z__String_Copy(z__String *dest, const z__String val)
    {
        if (dest->len < val.len )
        {
            z__String_resize(dest, val.len);
        }
        memcpy(dest->str, val.str, val.len);
    }

    z__String z__String_MakeCopy(const z__String str)
    {

        z__String str2 = {
            .str = calloc(sizeof(z__char) , str.len),
            .len = str.len,
            .used = str.used
        };

        memcpy(str2.str, str.str, str.len);

        return str2;
    }

    inline void z__Strint_append(z__String *str, const z__char *src, int length)
    {
        if (length > 0)
        {
            if ((str->len-str->used) > length){
                memcpy(&str[str->used], src, length);

            } else {
                z__String_resize(str, length+str->len);
            }
            str->used += length;
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

        memcpy(s->str, st, s->len);
        s->used = len;
    }

    inline void z__String_join(z__String *dest, z__String *src, unsigned int extraSpace)
    {
        dest->len = dest->len + src->used + extraSpace;
        dest->str = reallocf(dest->str, dest->len);

        memcpy(&dest[dest->used], src->str, src->used);
    }

    void z__String_pushChar(z__String *dest, z__char ch)
    {
        if(dest->len <= dest->used) {
            z__String_resize(dest, dest->len + 8);
        }

        dest->str[dest->used] = ch;
        dest->used += 1;
    }

    void z__String_insertChar(z__String *dest, z__char ch, z__i32 pos)
    {
        if(pos >= dest->used && pos < 0) {
            return;
        }
        
        if (dest->len <= dest->used) {
            z__String_resize(dest, dest->len +8);
        }

        z__char
            tmpchar = dest->str[pos],
            *buff = &dest->str[dest->used];
        dest->str[pos] = ch;
        dest->str[dest->used + 1] = 0;

        int splen = dest->used - pos;

        for (int i = 0; i < splen; i++) {
            *buff = *(buff-1);
            buff--;
        }
        dest->str[pos +1] = tmpchar;

        dest->used += 1;
    }

    void z__String_delChar(z__String *dest, z__i32 pos)
    {
        if(pos >= dest->used && pos < 0) {
            return;
        }

        int splen = dest->used - pos;
        z__char *buff = &dest->str[pos];

        for (int i = 0; i < splen; ++i)
        {
            *buff = *(buff+1);
            buff++;
        }
        dest->used -= 1;
    }

    void z__String_replaceChar(z__String *dest, z__char ch, z__i32 pos)
    {
        if(pos >= dest->used && pos < 0) {
            return;
        }
        dest->str[pos] = ch;
    }

    
    z__String z__String_newFromFile(char filename[])
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
             .str = string
            ,.len = fsize +1
            ,.used = fsize +1
        };
    }
       

    z__StringList z__StringList_new(unsigned int base_lines_count)
    {
        z__StringList ln = {
            .str_list = calloc(base_lines_count, sizeof(*ln.str_lens)),
            .list_len = base_lines_count,
            .ll_used = 0
        };
        ln.str_lens = calloc(base_lines_count, sizeof(*ln.str_lens));

        return ln;
    }

    void z__StringList_delete(z__StringList *ln)
    {
        for (int i = 0; i < ln->ll_used; ++i)
        {
            free(ln->str_list[i]);
        }
        free(ln->str_list);
        free(ln->str_lens);

        ln->list_len = 0;
        ln->ll_used = 0;
    }

    void z__StringList_pushString(z__StringList *ln ,z__String str)
    {
        if(ln->ll_used >= ln->list_len) {
            ln->list_len += Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->str_list = z__mem_safe_realloc(ln->str_list, sizeof(*ln->str_list) *ln->list_len);
        }

        ln->str_list[ln->ll_used] = calloc(str.used+1, sizeof(**ln->str_list));
        memcpy(ln->str_list[ln->ll_used], str.str, str.used * sizeof(*str.str));
        ln->str_lens[ln->ll_used] = str.used;
        ln->ll_used += 1;
    }

    void z__StringList_push(z__StringList *ln , char const * st, int len)
    {
        if(ln->ll_used >= ln->list_len) {
            ln->list_len += Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->str_list = z__mem_safe_realloc(ln->str_list, sizeof(*ln->str_list) *ln->list_len);
            ln->str_lens = z__mem_safe_realloc(ln->str_lens, sizeof(*ln->str_lens) *ln->list_len);
        }

        if (len == -1) {
            len = strlen(st);
        }

        ln->str_list[ln->ll_used] = calloc(len, sizeof(**ln->str_list));
        memcpy(ln->str_list[ln->ll_used], st, len * sizeof(*st));
        ln->str_lens[ln->ll_used] = len;
        ln->ll_used += 1;
    }

    void z__StringList_pop(z__StringList *ln)
    {
        free(ln->str_list[ln->ll_used-1]);
        ln->ll_used -= 1;
        /*
        if (ln->list_len - ln->ll_used >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
        {
            ln->list_len -= Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT;
            ln->str_list = z__mem_safe_realloc(ln->str_list, sizeof(*ln->str_list) *ln->list_len);
            ln->str_lens = z__mem_safe_realloc(ln->str_lens, sizeof(*ln->str_lens) *ln->list_len);
        }
        */
    }

    z__StringList z__StringList_newFrom(z__StringList const *ln)
    {
        z__StringList newln = {
            .list_len = ln->list_len,
            .ll_used = ln->ll_used
        };

        newln.str_lens = malloc(sizeof(*newln.str_lens) * newln.list_len);
        memcpy(newln.str_lens, ln->str_lens, sizeof(*newln.str_lens)*newln.list_len);

        newln.str_list = malloc(sizeof(*newln.str_list) * newln.list_len);

        for (int i = 0; i < newln.ll_used; ++i) {
            newln.str_list[i] = malloc(sizeof(**newln.str_list) * newln.str_lens[i]);
            memcpy(newln.str_list[i], ln->str_list[i], newln.str_lens[i]);
        }

        return newln;
    }

    z__StringList z__String_splitTok(z__String str, char const *restrict seperator)
    {
        z__String tmp = z__String_MakeCopy(str);
        char *lastbuff = tmp.str;
        char *token = strtok_r(lastbuff, seperator, &lastbuff);

        /*Count*/
        int linesCount = 0;
        while(token) {

            linesCount += 1;
            token = strtok_r(lastbuff, seperator, &lastbuff);
        }

        z__String_delete(&tmp);
        tmp = z__String_MakeCopy(str);

        lastbuff = tmp.str;
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
        
        char *tmp_stri = malloc(len * sizeof(*tmp_stri));
        memcpy(tmp_stri, stri, len);

        char *lastbuff = tmp_stri;
        char *token = strtok_r(lastbuff, seperator, &lastbuff);

        /*Count*/
        int linesCount = 0;
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

        int i = 0, len = 0;
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

    z__StringListArr z__StringListArr_new(int size, int x, int y)
    {
        z__StringListArr lns = {
            .Sldata = calloc(sizeof(z__StringList), size),
            .len = size,
            .used = 0
        };

        for (int i = 0; i < lns.len; ++i)
        {
            lns.Sldata[i] = z__StringList_new(x);
        }

        return lns;
    }

    void z__StringListArr_delete(z__StringListArr *lns)
    {
        for (int i = 0; i < lns->len; ++i)
        {
            z__StringList_delete(&lns->Sldata[i]);
        }
        free(lns->Sldata);
        lns->Sldata = NULL;
        lns->len = 0;
    }

    void z__StringListArr_resize(z__StringListArr *lns, int newsize)
    {
        if (newsize < lns->len)
        {
            for (int i = newsize; i < lns->len; ++i)
            {
                z__StringList_delete(&lns->Sldata[i]);
            }
            lns->Sldata = z__mem_safe_realloc(lns->Sldata, sizeof(z__StringList) * newsize);
            lns->len = newsize;
        }
        else if (newsize > lns->len)
        {
            lns->Sldata = z__mem_safe_realloc(lns->Sldata, sizeof(z__StringList) * newsize);
            lns->len = newsize;
            for (int i = lns->len; i < newsize; ++i)
            {
                lns->Sldata[i] = z__StringList_new(lns->Sldata[0].list_len);
            }
        }
    }

    // String END

#endif //Z___TYPE_CONFIG__USE_STRING
