#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#include "io.h"

z__i8Arr z__io_readFile(char const  filename[])
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        return (z__i8Arr){NULL, -1, -1};
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */

    void *data = z__MALLOC(fsize + 1);
    fread(data, 1, fsize, fp);
    fclose(fp);

    return (z__i8Arr) {
        .data = data,
        .len = fsize +1,
        .lenUsed = fsize +1
    };
}

z__Dynt z__io_Dynt_readFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen)
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

z__StringLines z__io_getfnames(char const path[])
{
    DIR * drip = opendir(path);
    if(drip == NULL) return (z__StringLines){0};
    struct dirent* dp;
    int items = 0;

    while((dp = readdir(drip)) != NULL)
    {
        items++;
    }
    closedir(drip);
    drip = opendir(path);

    z__StringLines fnames = z__StringLines_new(32);

    while((dp = readdir(drip)) != NULL)
    {
        z__StringLines_push(&fnames, dp->d_name, dp->d_namlen);
    }
    closedir(drip);

    return fnames;
}

