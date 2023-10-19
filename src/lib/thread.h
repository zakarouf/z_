#ifndef ZAKAROUF__Z__IMP_THREAD_H
#define ZAKAROUF__Z__IMP_THREAD_H

#include <pthread.h>

#include "std/primitives.h"
#include "record.h"

#include "prep/base.h"
#include "prep/args.h"

#include "atomic.h"

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

/**/


/**
 * Allocates ands initiates pthread handles.
 * - Should be called once before starting co-routines.
 * - After joining all the threads, z__thread_end is called.
 */
void z__thread_start(void);

/**
 * De-allocates memory set by the z__thread_start.
 * - Should be called after co-routines are finished.
 */
void z__thread_end(void);

/**
 * Create a new Thread
 * First Arg takes in the pointer to an integer that will return as the thread id.
 */
z__u32 z__thread_run_raw(z__u32 *id, z__Thread_Attr *attr, void *(*fn) (void *), void *arg, char const *name, z__u32 name_size);

/**
 */
void z__thread_run_setid_raw(
    z__u32 inp_id, z__u32 *id
  , z__Thread_Attr *attr, void *(*fn)(void *), void *arg
  , const char *name, z__u32 name_size);

/**
 */
void z__thread_join_raw(z__u32 id);


char *z__thread_get_name_of_tid(z__u32 tid);


z__u32 z__thread_tstatus_is_done(z__u32 id);
void z__thread_set_tstatus_done(z__u32 id);
z__bool z__thread_is_thread_active(z__u32 id);

/*-----------------------------------*/

#define z__thread_run(fn, arg, attr)\
    z__thread_run_raw(       \
            &(arg)->unique.id       \
          , attr, fn, arg           \
          , #fn, sizeof(#fn))

#define z__thread_run_setid(id, fn, arg, attr)\
    z__thread_run_setid_raw(  \
          id, &(arg)->unique.id \
        , attr, fn, arg         \
        , #fn, sizeof(#fn))

#define z__thread_join(id)\
    z__thread_join_raw(id);

#define z__thread_setself_tstatus_done(arg)\
  z__thread_set_tstatus_done((arg)->unique.id)

#define z__thread_waitfor_tstatus(st, id)\
  while(!zpp__CAT(z__thread_tstatus_, st)(id) && z__thread_is_thread_active(id))

#define z__thread_waitfor_thread_inactive(id)\
  while(z__thread_is_thread_active(id))


#endif
