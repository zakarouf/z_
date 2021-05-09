#ifndef ZAKAROUF__DYNAMIC_TYPE__CONFIG_H
#define ZAKAROUF__DYNAMIC_TYPE__CONFIG_H

/*
 * Z__TYPES_CONFIG
 * ---------------------
 *	- Indentions refers to sub-config of the previous one:
 *			EXAMPLE: #define foo
 *						#define bar
 *						^
 *						Here `bar` is sub-config of `foo`
 *			Note: Sub-config generally imply that the parent config
 *				is Active, and if the there is #if #elif #else type of deal then
 *				`//##ELIF` and `//##ELSE` is used in the same indentation as config its
 *				part of
 *
 *		This type of Config Defination and Used in-order to easily specify which type
 *	of config it is? And how it is going to effect the compilation process.
 *		Many of these parent Config directly effects the weight of the code Base. So it
 *	is advised to turn off those config definations which are not needed by commentng
 *	them out.  Such as CGLM or Vector Types etc.
 */

#include "../z__exp.h"

/* General */
#define Z___TYPE_REALLOC_RESIZE_BY_DEFAULT 8
#define Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT 8

/*
 * Used Dollar-sign at the end of macros to explicitly tell they are indeed macros
 * z__Arr_new$() <- is a macros
 */
//#define Z___TYPE_CONFIG__ALIAS_DOLLARSIGN_FOR_MACROS
#ifdef Z___TYPE_CONFIG__ALIAS_DOLLARSIGN_FOR_MACROS
	#ifndef __GNUC__
		#error "z_:types: Used of Gnu Extention `Dollar-sign` but not availiable!!!\n"
	#endif
#endif

/* CGLM LIBRARY for graphics maths */
//#define Z___TYPE_INCLUED_CGLM
	//#define Z___TYPE_USE_CGLM_FOR_TYPES
	//#define Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_ARR_VECTOR_AND_MATRIX
	//#define Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_STRUCT_VECTOR_AND_MATRIX

/* Used String Type */
#define Z___TYPE_CONFIG__USE_STRING
	#define Z___TYPE_CONFIG__STRING__DEFAULT_SIZE 32

/* Array Types, Use Pre-defined typed arrays? */
#define Z___TYPE_CONFIG__USE_TYPE_ARR_PREDEFINED
	//#define Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS
	//#define Z___TYPE_CONFIG__USE_ARR_FUNTION_GENERATION_TEMPLATE

/* Linked List Type */
#define Z___TYPE_CONFIG__USE_TYPE_LINKEDLIST

/* Dynamic Arrays */
#define Z___TYPE_CONFIG__USE_ARR_ARRAYTYPE

/* Use Irregular Object holder */
#define Z___TYPE_CONFIG__USE_IRREGULAR_ARRAYTYPE
#define Z___TYPE_CONFIG__USE_DYNT_ARRAYTYPE

/* Memory Management */
//#define Z___TYPE_CONFIG__USE_MEM   /* Custom Mem is always included, this config is useless */
	//#define Z___TYPE_CONFIG__USE_MEM__VTRACK
	//#define Z___TYPE_CONFIG__USE_MEM__TRACK
	//#define Z___TYPE_CONFIG__USE_MEM__TRACK_AS_DEFAULT

/* Array Types, Use Vectors? */
#define Z___TYPE_CONFIG__USE_GMATHTYPE						
	#define Z___TYPE_CONFIG__USE_TYPE_ARR_VECTOR_AND_MATRIX			// Also include array for vectors defination, z__Vector2 is struct and z__vec2 is a Array
	#define Z___TYPE_CONFIG__USE_TYPE_STRUCT_VECTOR_AND_MATRIX
		//#define Z___TYPE_CONFIG__USE_f64_FOR_VECTOR_STRUCT
		//#define Z___TYPE_CONFIG__USE_i64_FOR_INT_VECTOR_STRUCT

#define Z___TYPES_CONFIG__USE_EXTENDED_FEATURES
	#define Z___TYPE_CONFIG__USE_TYPE_IDENTIFIER

#endif
