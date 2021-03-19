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

/* CGLM LIBRARY for graphics maths */
//#define Z___TYPE_INCLUED_CGLM

/* Array Types, Use Pre-defined typed arrays? */
#define Z___TYPE_CONFIG__USE_TYPE_ARRAYS
	#define Z___TYPE_REALLOC_RESIZE_BY_DEFAULT 8

		

/* Array Types, Use Vectors? */
#define Z___TYPE_CONFIG__USE_VECTORS						
	#define Z___TYPE_CONFIG__USE_TYPE_ARR_VECTOR			// Also include array for vectors defination, z__Vector2 is struct and z__vec2 is a Array
	//#define Z___TYPE_CONFIG__USE_f64_FOR_VECTOR_STRUCT
	//#define Z___TYPE_CONFIG__USE_i64_FOR_INT_VECTOR_STRUCT



#endif
