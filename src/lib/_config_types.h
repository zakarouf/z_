/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

#include "_export.h"


/* Config Start */
/*------------------------------------------*/

/* General */
/* Pretty self Explanatory, Edit them with Caution */
#define Z___TYPE_REALLOC_RESIZE_BY_DEFAULT 8

#define Z___TYPE_CONFIG__ARR__GROWTH_FACTOR__NUM 8
#define Z___TYPE_CONFIG__ARR__GROWTH_FACTOR__OPERATOR +
#define Z___TYPE_CONFIG__ARR__SHRINK_FACTOR__NUM 8

#define Z___TYPE_STRINGLINES_REALLOC_RESIZE_BY_DEFAULT 8

/*
 * Used Dollar-sign at the end of macros to explicitly tell they are indeed macros
 * Currently not all macros are aliased sadly.
 * z__Arr_new$() <- is a macros
 */
//#define Z___TYPE_CONFIG__ALIAS_DOLLARSIGN_FOR_MACROS


/* CGLM LIBRARY for graphics maths */
//#define Z___TYPE_INCLUED_CGLM
	//#define Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_VECTOR
	//#define Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_MATRIX

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

/* Use Enum Type */
//#define Z___TYPE_CONFIG__USE_ENUM_PRIMITIVE
#define Z___TYPE_CONFIG__USE_ENUM
	#define Z___TYPE_CONFIG__USE_ENUM_ALIAS_MATCH_STATEMENT

/* Use Tuple Type */
#define Z___TYPE_CONFIG__USE_TUPLE

/* Use Record Type */
#define Z___TYPE_CONFIG__USE_RECORD

/* Memory Management */
//#define Z___TYPE_CONFIG__USE_MEM   /* Custom Mem is always included, this config is useless */
	//#define Z___TYPE_CONFIG__USE_MEM__VTRACK
	//#define Z___TYPE_CONFIG__USE_MEM__TRACK
	//#define Z___TYPE_CONFIG__USE_MEM__TRACK_AS_DEFAULT

/* Use Vectors and stuff */
#define Z___TYPE_CONFIG__USE_GMATHTYPE						
		//#define Z___TYPE_CONFIG__USE_f64_FOR_VECTOR_STRUCT
		//#define Z___TYPE_CONFIG__USE_i64_FOR_INT_VECTOR_STRUCT

#define Z___TYPE_CONFIG__USE_EXTENDED_FEATURES
	#define Z___TYPE_CONFIG__USE_TYPE_IDENTIFIER



/* Config End */
/*------------------------------------------*/
/* Checks of Conflicting Configs and Errors */

#ifdef Z___TYPE_CONFIG__ALIAS_DOLLARSIGN_FOR_MACROS
    #ifndef __GNUC__
        #error "z_:types: Used of Gnu Extention `Dollar-sign` but not availiable!!!\n"
    #endif
#endif

#endif

