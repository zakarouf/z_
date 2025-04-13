#ifndef ZAKAROUF_Z_IMP__FIO_H
#define ZAKAROUF_Z_IMP__FIO_H

#include "string.h"
#include "dynt.h"

#include <stdio.h>

/* File */

/**
 * Load an entire file (of file name provided as in), 
 * @param unitsize being the individual chuck/unit size of the values
 * @param len is the nonnull; returned length of individual unit count
 * @return pointer to a newly allocated & loaded file data in memory.
 */
void *z__fio_newFromFile(char const filename[], z__size unitsize, z__size *len);

/**
 * Get a String List of File & Folder names in a directory
 */
z__StringList z__fio_getfnames(char const path[]);

/**
 * Load in a formated array data from an already opened file.
 */
void* z__fio_ptr_newLoad(z__size *unitsize, z__size *len, FILE *fp);

/**
 * Dump a formated array data into an already opened file.
 */
void z__fio_ptr_dump(void const *ptr, z__size const unitsize, z__size const len, FILE *fp);

/**
 * Write data to a new file, returns true on success
 */
int z__fio_write_file(void const *ptr, z__size const unitsize, z__size const len
		, z__Str fname);

/**
 * Append data to a file, returns true on success
 */
int z__fio_append_file(void const *ptr, z__size const unitsize, z__size const len
		, z__Str fname);

/**
 * Load Up a file as a dynt object.
 */
z__Dynt z__fio_Dynt_newFromFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen);

/**
 * Load a Dynt Object form a file.
 */
void z__fio_Dynt_newLoad(z__Dynt *obj, FILE *fp);

/**
 * Dump a Dynt Object into a file.
 */
void z__fio_Dynt_dump(z__Dynt *obj, FILE *fp);

/**
 * Create a new directory.
 */
int z__fio_mkdir(const char *p, z__size mode);

/**
 * Check if file exists, returns 1 if true;
 */
int z__fio_fileExist(const char *p);

/**
 * Check if directory exists, returns 1 if true;
 */
int z__fio_directoryExist(const char *p);

/**
 * Load Up an array form a file
 */
#define z__fio_Arr_newFromFile(arr, filepath)\
	{														\
		z__size len;										\
		(arr)->data =										\
			z__fio_newFromFile(								\
					filepath, sizeof((arr)->data), &len);	\
															\
		(arr)->len = len;									\
		(arr)->lenUsed = (arr)->len;						\
	}

/**
 * Load Up Array from an open file.
 */
#define z__fio_Arr_newLoad(arr, fp)\
	({														\
		z__size unitsize;									\
		(arr)->data =										\
				z__fio_ptr_newLoad(							\
						&unitsize, &(arr)->len, fp);		\
		(arr)->lenUsed = (arr)->len;						\
		unitsize;											\
	})

/**
 * Dump an array into an opened file
 */
#define z__fio_Arr_dump(arr, fp)\
	z__fio_ptr_dump((arr)->data, sizeof(*(arr)->data), (arr)->lenUsed, fp)


#ifdef Z__IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

#include "string.h"
#include "dynt.h"

void *z__fio_newFromFile(char const filename[], z__size unitsize, z__size *len)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
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

void z__fio_ptr_dump(void const *ptr, z__size const unitsize, z__size const len, FILE *fp)
{
    if(unitsize <= 0 || len <= 0 ) return;

    fwrite(&unitsize, sizeof(unitsize), 1, fp);
    fwrite(&len, sizeof(len), 1, fp);
    fwrite(ptr, unitsize * len, 1, fp);
}

int z__fio_write_file(void const *ptr, z__size const unitsize, z__size const len
		, z__Str fname)
{
    if(z__fio_fileExist(fname.data)
    || unitsize <= 0 || len <= 0) return 0;

    FILE *fp = fopen(fname.data, "w");
    if(fp == NULL) return 0;
    
    fwrite(ptr, unitsize, len, fp);
    fclose(fp);
    return 1;
}

int z__fio_append_file(void const *ptr, z__size const unitsize, z__size const len
		, z__Str fname)
{
    if(unitsize <= 0 || len <= 0) return 0;

    FILE *fp = fopen(fname.data, "a");
    if(fp == NULL) return 0;
    
    fwrite(ptr, unitsize, len, fp);
    fclose(fp);
    return 1;
}

void* z__fio_ptr_newLoad(z__size *unitsize, z__size *len, FILE *fp)
{
    z__size _l, _unit;
    void *ptr;

    fread(&_unit, sizeof(_unit), 1, fp);
    fread(&_l, sizeof(_l), 1, fp);

    ptr = z__MALLOC(_unit * _l);
    fread(ptr, _unit * _l, 1, fp);

    if(unitsize) *unitsize = _unit;
    if(len) *len = _l;

    return ptr;
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
        obj->data = z__MALLOC(obj->lenUsed * obj->unitsize);
        fread(obj->data, 1, obj->unitsize * obj->lenUsed, fp);
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
        fwrite(obj->data, 1, obj->unitsize * obj->lenUsed, fp);
    }
}

z__Dynt z__fio_Dynt_newFromFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        return (z__Dynt){0};
    }

    /* Take in File size */
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fsize += 1;

    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */
    /* Make an empty Dynr Object */
    z__Dynt Object = z__Dynt_new(subDiv, fsize/subDiv, 0, comment, commentLen);
    memset(Object.data, 0, fsize);

    fread(Object.data, 1, (fsize-1), fp);

    fclose(fp);

    return Object;

}

z__String z__sys_getcwd(void)
{
    char *dir = getcwd(NULL, 0);
    z__u32 len = 0;
    if(dir) len = strnlen(dir, PATH_MAX);
    return (z__String){
        .data = dir,
        .len = len,
        .lenUsed = len
    };
}

z__String z__sys_getcwf(void)
{
    z__String cwd = z__sys_getcwd();
    if(!cwd.data) return cwd;

    z__i64 at = z__String_findchar_last(&cwd, '/') + 1;
    if(at < 0) return cwd;

    cwd.lenUsed -= at;
    memmove(cwd.data, cwd.data + at, cwd.lenUsed);
    cwd.data[cwd.lenUsed] = '\0';

    return cwd;
}

z__StringList z__fio_getfnames(char const path[])
{
    DIR * drip = opendir(path);
    if(drip == NULL) return (z__StringList){0};
    struct dirent* dp = NULL;
    int items = 0;
    
    dp = readdir(drip);
    while(dp != NULL) {
        items++;
        dp = readdir(drip);
    }
    closedir(drip);

    drip = opendir(path);
    z__StringList fnames = z__StringList_new(items);

    dp = readdir(drip);
    while(dp != NULL) {
        z__StringList_push(&fnames, dp->d_name, 255);
        dp = readdir(drip);
    }
    closedir(drip);

    return fnames;
}

int z__fio_fileExist(const char *p)
{
    FILE *fp = fopen(p, "rb");
    if(fp == NULL) return 0;
    fclose(fp);
    return 1;
}

int z__fio_directoryExist(const char *p)
{
    struct stat sb;
    return stat(p, &sb) == 0 && S_ISDIR(sb.st_mode);
}

int z__fio_mkdir(const char *p, z__size mode)
{
    return mkdir(p, mode);
}

#endif // Z__IMPLEMENTATION

#endif

