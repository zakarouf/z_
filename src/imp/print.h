#ifndef ZAKAROUF_Z_IMP__PRINT_H
#define ZAKAROUF_Z_IMP__PRINT_H

#include <stdio.h>

#include "../prep/args.h"
#include "../prep/map.h"
#include "../types/base.h"

#include "type.h"

int _z__tfprint_raw(FILE *fp, z__u32 count, z__u16 tids[], z__size sizes[], ...);
#define z__tfprint(fp, ...)\
      _z__tfprint_raw(fp, zpp__Args_Count(__VA_ARGS__),\
          (z__u16[]){zpp__Args_maplist(z__typeid_raw, __VA_ARGS__)},\
          (z__size[]){zpp__Args_maplist(z__sizeof, __VA_ARGS__)},\
          __VA_ARGS__\
      );\

#define z__tprint(...) z__tfprint(stdout, __VA_ARGS__)


#endif

