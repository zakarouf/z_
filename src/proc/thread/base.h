#ifndef ZAKAROUF__Z__PROC_PT_BASE_H
#define ZAKAROUF__Z__PROC_PT_BASE_H

#include <pthread.h>

#include "../../types/base.h"
#include "../../types/record.h"

#include "../../prep/base.h"
#include "../../prep/args.h"

#include "../atomic.h"

// Wrapper Arround pthread_t
typedef pthread_t z__Thread;

// Wrapper Arround pthread_attr_t
typedef pthread_attr_t z__Thread_Attr;

/**
 * z__UniqueData
 *  .id => Stores the id of the thread function is on.
 */
typedef
    struct z__UniqueData {
        z__u32 id;
} z__UniqueData;

/**
 * z__MetaData
 * Misc meta data about threads
 */
typedef
    struct z__MetaData {
        z__u32 Total_Thread;
} z__MetaData;


// Context  //

#define z__DataContextType(TagName) struct z__DataContextType__##TagName
#define z__DataContextName(TagName) z__DataContextType__##TagName

//#define z__PRIV__pt_ismt_0(...) , __VA_ARGS__
//#define z__PRIV__pt_ismt_1(...) __VA_ARGS__
//#define z__PRIV__pt_ismt(...) zpp__CAT(z__PRIV__pt_ismt_, zpp__Args_IS_EMPTY(__VA_ARGS__))(__VA_ARGS__)

/**
 * z__DataContext
 * Create a structured type that will be passed onto a
 * threaded function.
 */
#define z__DataContext(TagName, S, P)\
    z__DataContextType(TagName) { \
        S                   *shared; \
        P                   private; \
        z__UniqueData    unique;  \
        z__MetaData      meta;    \
    } 


// Access the shared data of Arg.
#define z__DataArg_access_shared(Arg, mem) (Arg)->shared->mem

// Set the value of shared data of Arg.
#define z__DataArg_set_shared(Arg, mem, val) (Arg)->shared->mem = val

/*------------------------------------*/

// Pthread binding
#define z__pt(f, ...) zpp__CAT(pthread_, f)(__VA_ARGS__)

#endif

