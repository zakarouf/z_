#ifndef ZAKAROUF__Z__TYPES_H
#define ZAKAROUF__Z__TYPES_H

#include "config_types.h"
#include "types/base.h"
#include "types/base_util.h"
#include "types/typeof.h"
#include "types/mem.h"

#include "types/bitf.h"

/* CGLM */
#ifdef Z___TYPE_INCLUED_CGLM
    #include "types/cglm.h"
#endif

/* Vectors And Matrices For Graphical Maths */
#ifdef Z___TYPE_CONFIG__USE_GMATHTYPE
    #include "types/gmath.h"
#endif 


/* Generic Array Type */
#ifdef Z___TYPE_CONFIG__USE_ARR_ARRAYTYPE
	#include "types/arr.h"
#endif

/* Irregular Type */
#ifdef Z___TYPE_CONFIG__USE_IRREGULAR_ARRAYTYPE
    #include "types/irrg.h"
#endif

/* Void Array Type */
#ifdef Z___TYPE_CONFIG__USE_DYNT_ARRAYTYPE
    #include "types/dynt.h"
#endif


/* Tuple Type */
#ifdef Z___TYPE_CONFIG__USE_TUPLE
    #include "types/tuple.h"
#endif

/* Enum Type (PRIMITIVE) */
#ifdef Z___TYPE_CONFIG__USE_ENUM_PRIMITIVE
    #include "enum_primitive.h"
#endif

/* Enum Type */
#ifdef Z___TYPE_CONFIG__USE_ENUM
    #include "types/enum.h"
#endif

/* Record Type */
#ifdef Z___TYPE_CONFIG__USE_RECORD
    #include "types/record.h"
#endif


/* Linked Lists */
#ifdef Z___TYPE_CONFIG__USE_TYPE_LINKEDLIST
    #include "types/llist.h"
#endif

#ifdef Z___TYPE_CONFIG__USE_STRING
	#include "types/string.h"
#endif


#endif
