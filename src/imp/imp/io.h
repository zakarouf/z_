#ifndef ZAKAROUF_Z_IMP__IO_H
#define ZAKAROUF_Z_IMP__IO_H

#include "../../types/ztypes/string.h"
#include "../../types/ztypes/dynt.h"
#include "../../types/ztypes/arr.h"


/* File */
z__i8Arr z__io_i8_readFile(char const filename[]);
z__Dynt z__io_Dynt_readFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen);
z__StringLines z__io_getfnames(char const path[]);


#endif