#ifndef ZAKAROUF_Z_IMP__TPRINT_H
#define ZAKAROUF_Z_IMP__TPRINT_H

#include <stdio.h>

#include "prep/args.h"
#include "prep/map.h"

#include "std/primitives.h"

#include "typeid.h"

int _z__tgfprint_raw(FILE *fp, z__u32 count, z__u16 tids[], z__size sizes[], ...);
#define z__tgfprint(fp, ...)\
      _z__tgfprint_raw(fp, zpp__Args_Count(__VA_ARGS__),\
          (z__u16[]){zpp__Args_maplist(z__typeid_raw, __VA_ARGS__)},\
          (z__size[]){zpp__Args_maplist(z__sizeof, __VA_ARGS__)},\
          __VA_ARGS__\
      );\

#define z__tgprint(...) z__tgfprint(stdout, __VA_ARGS__)


#endif

