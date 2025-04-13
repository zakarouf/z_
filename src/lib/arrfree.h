#ifndef ZAKAROUF__ZTYPES_TYPES__ARRFREE_H
#define ZAKAROUF__ZTYPES_TYPES__ARRFREE_H

void z__mem_Arr_clean(void * arr);
#define z__Arrfree __attribute__((cleanup(z__mem_Arr_clean)))

#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include "std/mem.h"
#include "arr.h"

void z__mem_Arr_clean(void * arr)
{
    z__voidArr *temp = arr;
    //printf("%d, %p\n", temp->len, temp->data); // for Debug
    z__Arr_delete(temp);
}
#endif //Z__IMPLEMENTATION

#endif
