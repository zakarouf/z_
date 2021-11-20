#ifndef ZAKAROUF__Z__PROC_PT_BASE_H
#define ZAKAROUF__Z__PROC_PT_BASE_H

#include <pthread.h>

#include "../../types/base.h"
#include "../../types/record.h"

#include "../../prep/base.h"
#include "../../prep/args.h"

#include "../atomic.h"

// Wrapper Arround pthread_t
typedef pthread_t z__pt_Thread;

// Wrapper Arround pthread_attr_t
typedef pthread_attr_t z__pt_Thread_Attr;

/**
 * z__pt_UniqueData
 *  .id => Stores the id of the thread function is on.
 */
typedef
    struct z__pt_UniqueData {
        z__u32 id;
} z__pt_UniqueData;

/**
 * z__pt_MetaData
 * Misc meta data about threads
 */
typedef
    struct z__pt_MetaData {
        z__u32 Total_Thread;
} z__pt_MetaData;


// Context  //

#define z__pt_DataContextType(TagName) struct z__pt_DataContextType__##TagName
#define z__pt_DataContextName(TagName) z__pt_DataContextType__##TagName

//#define z__PRIV__pt_ismt_0(...) , __VA_ARGS__
//#define z__PRIV__pt_ismt_1(...) __VA_ARGS__
//#define z__PRIV__pt_ismt(...) zpp__CAT(z__PRIV__pt_ismt_, zpp__Args_IS_EMPTY(__VA_ARGS__))(__VA_ARGS__)

/**
 * z__pt_DataContext
 * Create a structured type that will be passed onto a
 * threaded function.
 */
#define z__pt_DataContext(TagName, S, P)\
    z__pt_DataContextType(TagName) { \
        S                   *shared; \
        P                   private; \
        z__pt_UniqueData    unique;  \
        z__pt_MetaData      meta;    \
    } 


// Access the shared data of Arg.
#define z__pt_DataArg_access_shared(Arg, mem) (Arg)->shared->mem

// Set the value of shared data of Arg.
#define z__pt_DataArg_set_shared(Arg, mem, val) (Arg)->shared->mem = val

/*------------------------------------*/

// Pthread binding
#define z__pt(f, ...) zpp__CAT(pthread_, f)(__VA_ARGS__)

#endif

