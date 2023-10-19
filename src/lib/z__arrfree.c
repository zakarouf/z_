#include <stdlib.h>
#include "std/mem.h"
#include "arr.h"

void z__mem_Arr_clean(void * arr)
{
    z__voidArr *temp = arr;
    //printf("%d, %p\n", temp->len, temp->data); // for Debug
    z__Arr_delete(temp);
}

