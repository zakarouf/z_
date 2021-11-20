#ifndef ZAKAROUF__Z__PROC_PT_SUBROUTINE_H
#define ZAKAROUF__Z__PROC_PT_SUBROUTINE_H

#include "base.h"

/**
 * Allocates ands initiates pthread handles.
 * - Should be called once before starting co-routines.
 * - After joining all the threads, z__pt_coroutine_end is called.
 */
void z__pt_coroutine_start(void);

/**
 * De-allocates memory set by the z__pt_coroutine_start.
 * - Should be called after co-routines are finished.
 */
void z__pt_coroutine_end(void);

z__u32 z__pt_coroutine_run_raw(z__u32 *id, z__pt_Thread_Attr *attr, void *(*fn) (void *), void *arg, char const *name, z__u32 name_size);
void z__pt_coroutine_join_raw(z__u32 id);

char *z__pt_coroutine_get_name_of_tid(z__u32 tid);

z__u32 z__pt_coroutine_tstatus_is_done(z__u32 id);
void z__pt_coroutine_set_tstatus_done(z__u32 id);
z__bool z__pt_coroutine_is_thread_active(z__u32 id);

/*-----------------------------------*/

#define z__pt_coroutine_run(fn, arg, attr)\
    z__pt_coroutine_run_raw(       \
            &(arg)->unique.id       \
          , attr, fn, arg           \
          , #fn, sizeof(#fn));

#define z__pt_coroutine_join(id)\
    z__pt_coroutine_join_raw(id);

#define z__pt_coroutine_setself_tstatus_done(arg)\
  z__pt_coroutine_set_tstatus_done((arg)->unique.id)

#define z__pt_coroutine_waitfor_tstatus(st, id)\
  while(!zpp__CAT(z__pt_coroutine_tstatus_, st)(id) && z__pt_coroutine_is_thread_active(id))

#define z__pt_coroutine_waitfor_thread_inactive(id)\
  while(z__pt_coroutine_is_thread_active(id))

#endif

