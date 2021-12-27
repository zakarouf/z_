#include "coroutine.h"
#include "../../types/arr.h"
#include "base.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct Thread {
    char *name;
    z__pt_Thread thread;
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

inline static void _z__pt_coroutine_thread_enable(struct Thread *thread, const char *name, z__i32 name_size)
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

inline static void _z__pt_coroutine_thread_disable(struct Thread *thread)
{
    z__FREE(thread->name);
    thread->name = NULL;
    thread->status_flags = 0;
    thread->_is_active = 0;
}

void z__pt_coroutine_start(void)
{
    z__Arr_new(&_g_threads, 8);
    z__Arr_mapnum(&_g_threads);
}

void z__pt_coroutine_end(void)
{
    z__Arr_foreach(struct Thread *i, _g_threads){
        _z__pt_coroutine_thread_disable(i);
    }
    z__Arr_delete(&_g_threads);
}

z__u32 z__pt_coroutine_run_raw(z__u32 *id, z__pt_Thread_Attr *attr, void *(*fn) (void *), void *arg, char const *name, z__u32 name_size)
{
    z__pt(mutex_lock, &thread_counter_lock);
        *id = z__Arr_getUsed(_g_threads);
        struct Thread tmp_t;
        _z__pt_coroutine_thread_enable(&tmp_t, name, name_size);
        z__Arr_push(&_g_threads, tmp_t);
        z__pt(create, &z__Arr_getTop(_g_threads).thread, attr, fn, arg);
    z__pt(mutex_unlock, &thread_counter_lock);

    return *id;
}

void z__pt_coroutine_run_setid_raw(
    z__u32 inp_id, z__u32 *id
  , z__pt_Thread_Attr *attr, void *(*fn)(void *), void *arg
  , const char *name, z__u32 name_size)
{
    z__pt(mutex_lock, &thread_counter_lock);
        *id = inp_id;
        if(inp_id > z__Arr_getLen(_g_threads)){
            z__Arr_resize(&_g_threads, inp_id);
        }
        _z__pt_coroutine_thread_enable(&z__Arr_getVal(_g_threads, inp_id), name, name_size);
        z__pt(create, &z__Arr_getTop(_g_threads).thread, attr, fn, arg);
    z__pt(mutex_unlock, &thread_counter_lock);

}

void z__pt_coroutine_join_raw(z__u32 id)
{
    struct Thread *tmp = &z__Arr_getVal(_g_threads, id);
    //`printf("%s\n", tmp->name);
    if(tmp->_is_active) {
        z__pt(join, tmp->thread, NULL);
//        z__pt(mutex_lock, &thread_counter_lock);
            _z__pt_coroutine_thread_disable(tmp);
//        z__pt(mutex_unlock, &thread_counter_lock);
    }
}

char *z__pt_coroutine_get_name_of_tid(z__u32 tid)
{
    if(tid < z__Arr_getUsed(_g_threads)){
        return z__Arr_getVal(_g_threads, tid).name;
    } else {
        return NULL;
    }
}

z__i32 z__pt_coroutine_search_tid_from_name(char const *name)
{
    return -1;
}

//-------------------------------//
z__u32 z__pt_coroutine_tstatus_is_done(z__u32 id)
{
    return z__Arr_getVal(_g_threads, id).status_flags & z__pt_thread_status_name(DONE);
}

void z__pt_coroutine_set_tstatus_done(z__u32 id)
{
    _g_threads.data[id].status_flags |= z__pt_thread_status_name(DONE);
}

z__bool z__pt_coroutine_is_thread_active(z__u32 id)
{
    return z__Arr_getVal(_g_threads, id)._is_active;
}

