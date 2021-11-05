#ifndef ZAKAROUF_Z_IMP__FIO_H
#define ZAKAROUF_Z_IMP__FIO_H

#include "../types/string.h"
#include "../types/dynt.h"
#include "../types/arr.h"

#include <stdio.h>

/* File */
void *z__fio_newFromFile(char const filename[], z__size unitsize, z__size *len);
#define z__fio_Arr_newFromFile(arr, filepath)\
	{																		\
		(arr)->data =														\
			z__fio_newFromFile(filepath, sizeof((arr)->data), &(arr)->len); \
																			\
		(arr)->lenUsed = (arr)->len;										\
	}

z__StringList z__fio_getfnames(char const path[]);

z__Dynt z__fio_Dynt_newFromFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen);
void z__fio_Dynt_dump(z__Dynt *obj, FILE *fp);
void z__fio_Dynt_newLoad(z__Dynt *obj, FILE *fp);


#endif

