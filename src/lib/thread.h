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

#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "arr.h"
#include "thread.h"

struct Thread {
    char *name;
    z__Thread thread;
    z__bool _is_active;
    z__u32 status_flags;
};

static pthread_mutex_t thread_counter_lock = PTHREAD_MUTEX_INITIALIZER;
static z__Arr(struct Thread) _g_threads;


#define z__PRIV__pt_thread_status() z__pt_E_THREAD_STATUS_
#define z__pt_thread_status_name(of) zpp__CAT(z__PRIV__pt_thread_status(), of)

enum {
      z__pt_thread_status_name(DONE) = 1
    , z__pt_thread_status_name(CAUGHT_ERROR) = 1 << 1
};

inline static void _z__thread_thread_enable(struct Thread *thread, const char *name, z__i32 name_size)
{
    thread->_is_active = 1;
    if(name){
        if(name_size == -1){
            name_size = strnlen(name, 512);
        }
        thread->name = z__CALLOC(sizeof(*thread->name), name_size);
        memcpy(thread->name, name, sizeof(*thread->name) * name_size);
    } else {
        thread->name = z__CALLOC(sizeof("|UNNAMED|\0"), 1);
        memcpy(thread->name, "|UNNAMED|", sizeof("|UNNAMED|"));
    }
    thread->status_flags = 0;
}

inline static void _z__thread_thread_disable(struct Thread *thread)
{
    z__FREE(thread->name);
    thread->name = NULL;
    thread->status_flags = 0;
    thread->_is_active = 0;
}

void z__thread_start(void)
{
    z__Arr_new(&_g_threads, 8);
    z__Arr_mapnum(&_g_threads);
}

void z__thread_end(void)
{
    z__Arr_foreach(i, _g_threads){
        _z__thread_thread_disable(i);
    }
    z__Arr_delete(&_g_threads);
}

z__u32 z__thread_run_raw(z__u32 *id, z__Thread_Attr *attr, void *(*fn) (void *), void *arg, char const *name, z__u32 name_size)
{
    z__pt(mutex_lock, &thread_counter_lock);
        *id = z__Arr_getUsed(_g_threads);
        struct Thread tmp_t;
        _z__thread_thread_enable(&tmp_t, name, name_size);
        z__Arr_push(&_g_threads, tmp_t);
        z__pt(create, &z__Arr_getTop(_g_threads).thread, attr, fn, arg);
    z__pt(mutex_unlock, &thread_counter_lock);

    return *id;
}

void z__thread_run_setid_raw(
    z__u32 inp_id, z__u32 *id
  , z__Thread_Attr *attr, void *(*fn)(void *), void *arg
  , const char *name, z__u32 name_size)
{
    z__pt(mutex_lock, &thread_counter_lock);
        *id = inp_id;
        if(inp_id > z__Arr_getLen(_g_threads)){
            z__Arr_resize(&_g_threads, inp_id);
        }
        _z__thread_thread_enable(&z__Arr_getVal(_g_threads, inp_id), name, name_size);
        z__pt(create, &z__Arr_getTop(_g_threads).thread, attr, fn, arg);
    z__pt(mutex_unlock, &thread_counter_lock);

}

void z__thread_join_raw(z__u32 id)
{
    struct Thread *tmp = &z__Arr_getVal(_g_threads, id);
    //`printf("%s\n", tmp->name);
    if(tmp->_is_active) {
        z__pt(join, tmp->thread, NULL);
//        z__pt(mutex_lock, &thread_counter_lock);
            _z__thread_thread_disable(tmp);
//        z__pt(mutex_unlock, &thread_counter_lock);
    }
}

char *z__thread_get_name_of_tid(z__u32 tid)
{
    if(tid < z__Arr_getUsed(_g_threads)){
        return z__Arr_getVal(_g_threads, tid).name;
    } else {
        return NULL;
    }
}

#if 0
z__i32 z__thread_search_tid_from_name(char const *name)
{
    return -1;
}
#endif

//-------------------------------//
z__u32 z__thread_tstatus_is_done(z__u32 id)
{
    return z__Arr_getVal(_g_threads, id).status_flags & z__pt_thread_status_name(DONE);
}

void z__thread_set_tstatus_done(z__u32 id)
{
    _g_threads.data[id].status_flags |= z__pt_thread_status_name(DONE);
}

z__bool z__thread_is_thread_active(z__u32 id)
{
    return z__Arr_getVal(_g_threads, id)._is_active;
}

#endif //Z__IMPLEMENTATION

#endif
