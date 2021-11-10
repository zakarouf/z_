#ifndef ZAKAROUF_Z_IMP__FIO_H
#define ZAKAROUF_Z_IMP__FIO_H

#include "../types/string.h"
#include "../types/dynt.h"
#include "../types/arr.h"

#include <stdio.h>

/* File */
void *z__fio_newFromFile(char const filename[], z__size unitsize, z__size *len);

z__StringList z__fio_getfnames(char const path[]);

void* z__fio_ptr_newLoad(z__size *unitsize, z__size *len, FILE *fp);
void z__fio_ptr_dump(void const *ptr, z__size const unitsize, z__size const len, FILE *fp);


z__Dynt z__fio_Dynt_newFromFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen);
void z__fio_Dynt_dump(z__Dynt *obj, FILE *fp);
void z__fio_Dynt_newLoad(z__Dynt *obj, FILE *fp);


#define z__fio_Arr_newFromFile(arr, filepath)\
	{																		\
		(arr)->data =														\
			z__fio_newFromFile(filepath, sizeof((arr)->data), &(arr)->len); \
																			\
		(arr)->lenUsed = (arr)->len;										\
	}

#define z__fio_Arr_newLoad(arr, fp)\
	({																			\
		z__size unitsize;														\
		(arr)->data = z__fio_ptr_newLoad(&unitsize, &(arr)->len, fp);			\
		(arr)->lenUsed = (arr)->len;											\
		unitsize;																\
	})

#define z__fio_Arr_dump(arr, fp)\
	z__fio_ptr_dump((arr)->data, sizeof(*(arr)->data), (arr)->lenUsed)

#endif

