#ifndef ZAKAROUF__ZTYPES_H
#define ZAKAROUF__ZTYPES_H

#include "../config_types.h"
#include "base.h"
#include "base_util.h"
#include "typeof.h"
#include "mem.h"

#include "bitf.h"

/* CGLM */
#ifdef Z___TYPE_INCLUED_CGLM
    #include "cglm.h"
#endif

/* Vectors And Matrices For Graphical Maths */
#ifdef Z___TYPE_CONFIG__USE_GMATHTYPE
    #include "gmath.h"
#endif 


/* Generic Array Type */
#ifdef Z___TYPE_CONFIG__USE_ARR_ARRAYTYPE
	#include "arr.h"
#endif

/* Irregular Type */
#ifdef Z___TYPE_CONFIG__USE_IRREGULAR_ARRAYTYPE
    #include "irrg.h"
#endif

/* Void Array Type */
#ifdef Z___TYPE_CONFIG__USE_DYNT_ARRAYTYPE
    #include "dynt.h"
#endif


/* Tuple Type */
#ifdef Z___TYPE_CONFIG__USE_TUPLE
    #include "tuple.h"
#endif

/* Enum Type (PRIMITIVE) */
#ifdef Z___TYPE_CONFIG__USE_ENUM_PRIMITIVE
    #include "enum_primitive.h"
#endif

/* Enum Type */
#ifdef Z___TYPE_CONFIG__USE_ENUM
    #include "enum.h"
#endif

/* Record Type */
#ifdef Z___TYPE_CONFIG__USE_RECORD
    #include "record.h"
#endif


/* Linked Lists */
#ifdef Z___TYPE_CONFIG__USE_TYPE_LINKEDLIST
    #include "llist.h"
#endif

#ifdef Z___TYPE_CONFIG__USE_STRING
	#include "string.h"
#endif


#endif

