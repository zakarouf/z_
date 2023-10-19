#ifndef ZAKAROUF__ZTYPES_TYPES__ARRFREE_H
#define ZAKAROUF__ZTYPES_TYPES__ARRFREE_H

void z__mem_Arr_clean(void * arr);
#define z__Arrfree __attribute__((cleanup(z__mem_Arr_clean)))

#endif
