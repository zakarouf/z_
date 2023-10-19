#ifndef ZAKAROUF_Z_IMP__FIO_H
#define ZAKAROUF_Z_IMP__FIO_H

#include "string.h"
#include "dynt.h"
#include "arr.h"

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
 * Load Up a file as a dynt object.
 */
z__Dynt z__fio_Dynt_newFromFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen);

/**
 * Dump a Dynt Object into a file.
 */
void z__fio_Dynt_dump(z__Dynt *obj, FILE *fp);

/**
 * Load a Dynt Object form a file.
 */
void z__fio_Dynt_newLoad(z__Dynt *obj, FILE *fp);

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
	{																											\
		z__size len;																				\
		(arr)->data =																				\
			z__fio_newFromFile(																\
					filepath, sizeof((arr)->data), &len);					\
																												\
		(arr)->len = len;																		\
		(arr)->lenUsed = (arr)->len;												\
	}

/**
 * Load Up Array from an open file.
 */
#define z__fio_Arr_newLoad(arr, fp)\
	({														\
		z__size unitsize;						\
		(arr)->data =								\
				z__fio_ptr_newLoad(			\
						&unitsize, &(arr)->len, fp);\
		(arr)->lenUsed = (arr)->len;				\
		unitsize;														\
	})

/**
 * Dump an array into an opened file
 */
#define z__fio_Arr_dump(arr, fp)\
	z__fio_ptr_dump((arr)->data, sizeof(*(arr)->data), (arr)->lenUsed, fp)

#endif

