#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#include "fio.h"

void *z__fio_newFromFile(char const filename[], z__size unitsize, z__size *len)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    z__size fsize = ftell(fp);
    *len = fsize;
    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */

    z__size extra = fsize/unitsize;

    void *data = z__MALLOC(fsize * extra);
    fread(data, 1, fsize, fp);
    fclose(fp);

    return data;
}

void z__fio_Dynt_newLoad(z__Dynt *obj, FILE *fp)
{
    fread(&obj->typeID, sizeof(obj->typeID), 1, fp);

    fread(&obj->unitsize, sizeof(obj->unitsize), 1, fp);
    fread(&obj->lenUsed, sizeof(obj->lenUsed), 1, fp);
    obj->len = obj->lenUsed;

    fread(&obj->commentLen, sizeof(obj->commentLen), 1, fp);

    if(obj->commentLen > 0) {
        obj->comment = z__MALLOC(sizeof(*obj->comment) * obj->commentLen);
        fread(obj->comment, sizeof(*obj->comment), obj->commentLen, fp);
    }

    if((obj->unitsize * obj->lenUsed) > 0){
        obj->data = z__MALLOC(sizeof(*obj->data) * obj->lenUsed * obj->unitsize);
        fread(obj->data, sizeof(*obj->data), obj->unitsize * obj->lenUsed, fp);
    }
}

void z__fio_Dynt_dump(z__Dynt *obj, FILE *fp)
{
    fwrite(&obj->typeID, sizeof(obj->typeID), 1, fp);

    fwrite(&obj->unitsize, sizeof(obj->unitsize), 1, fp);
    fwrite(&obj->lenUsed, sizeof(obj->lenUsed), 1, fp);

    fwrite(&obj->commentLen, sizeof(obj->commentLen), 1, fp);

    if(obj->commentLen > 0) {
        fwrite(obj->comment, sizeof(*obj->comment), obj->commentLen, fp);
    }

    if((obj->unitsize * obj->lenUsed) > 0){
        fwrite(obj->data, sizeof(*obj->data), obj->unitsize * obj->lenUsed, fp);
    }
}

z__Dynt z__fio_Dynt_newFromFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        return (z__Dynt){NULL};
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fsize += 1;

    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */

    z__Dynt Object = z__Dynt_new(subDiv, fsize/subDiv, comment, commentLen, 0);
    memset(Object.data, 0, fsize);

    fread(Object.data, 1, (fsize-1), fp);

    fclose(fp);

    return Object;

}

z__StringList z__fio_getfnames(char const path[])
{
    DIR * drip = opendir(path);
    if(drip == NULL) return (z__StringList){0};
    struct dirent* dp;
    int items = 0;

    while((dp = readdir(drip)) != NULL)
    {
        items++;
    }
    closedir(drip);
    drip = opendir(path);

    z__StringList fnames = z__StringList_new(32);

    while((dp = readdir(drip)) != NULL)
    {
        z__StringList_push(&fnames, dp->d_name, dp->d_namlen);
    }
    closedir(drip);

    return fnames;
}

