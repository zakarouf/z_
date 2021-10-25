#ifndef ZAKAROUF_Z_IMP__FIO_H
#define ZAKAROUF_Z_IMP__FIO_H

#include "../types/string.h"
#include "../types/dynt.h"
#include "../types/arr.h"


/* File */
z__i8Arr z__fio_readFile(char const filename[]);
z__Dynt z__fio_Dynt_readFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen);
z__StringList z__fio_getfnames(char const path[]);


#endif
