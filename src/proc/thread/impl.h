#ifndef ZAKAROUF__Z__PROC_PT_SUBROUTINE_H
#define ZAKAROUF__Z__PROC_PT_SUBROUTINE_H

#include "base.h"

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

