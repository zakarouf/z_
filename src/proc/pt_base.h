#ifndef ZAKAROUF__Z__PROC_PT_BASE_H
#define ZAKAROUF__Z__PROC_PT_BASE_H

#include <pthread.h>

#include "../types/base.h"
//#include "../types/arr.h"

// Wrapper //

typedef pthread_t z__pt_Thread;

#define z__pt_create(th, th_attr, fn, args)\
    pthread_create((th), (th_attr), (fn), (args))

#define z__pt_join(th, return_val)\
    pthread_join((th), (return_val))

// Args //

#define z__pt_ArgContext_Tag(TagN, ...)\
    struct z__pt_ArgContext__tag##TagN {    \
        z__u32 _id;                         \
        z__u32 _maxt;                       \
        __VA_ARGS__;                        \
    }

#define z__pt_ArgContext(TagN)  struct z__pt_ArgContext__tag##TagN
#define z__pt_ArgContext_assign(arg, memo, val)\
    {                           \
        (arg)->memo = (val);    \
    }

#define z__pt_ArgArr(TagN) z__Arr(z__pt_ArgContext(TagN))

//* Similar Jobs *//

#define z__pt_Job(ArgContext, ...)\
    struct {                          \
        z__fnptr(*fn, void *, void *);\
        struct z__pt_ArgContext__tag##ArgContext *Args;\
        pthread_t *Threads;           \
        z__u32 Thread_Num;            \
        __VA_ARGS__;                  \
    }

#define z__pt_Job_new(Job, n)\
    {                                                                               \
        (Job)->Thread_Num = n;                                                      \
        (Job)->Args = z__MALLOC(sizeof(*(Job)->Args) * (Job)->Thread_Num);                 \
        (Job)->fn = z__MALLOC(sizeof(*(Job)->fn) * (Job)->Thread_Num);              \
        (Job)->Threads = z__CALLOC(sizeof(*(Job)->Threads), (Job)->Thread_Num);    \
    }

#define z__pt_Job_bind_Arg(Job, ArgContext, of) \
    {                                           \
        (Job)->Args[of] = (ArgContext);          \
    }

#define z__pt_Job_bind_fn(Job, fn_name, of) \
    {                                     \
        (Job)->fn[of] =  (void*)fn_name;  \
    }

#define z__pt_Job_run(Job)\
    {\
        for (int i = 0; i < (Job)->Thread_Num; ++i) {\
            (Job)->Args[i]._id = i;\
            pthread_create(&(Job)->Threads[i], NULL, (Job)->fn[i], &(Job)->Args[i]);\
        }\
    }\

#define z__pt_Job_thread_join(Job)\
    {                                                   \
        for (int i = 0; i < (Job)->Thread_Num; ++i) {   \
            pthread_join((Job)->Threads[i] ,NULL);      \
        }                                               \
    }

#define z__pt_Job_end(Job)\
    {\
        z__pt_Job_thread_join(Job);\
        z__pt_Job_delete(Job);      \
    }

#define z__pt_Job_delete(Job)\
    {                               \
        z__FREE((Job)->Args);        \
        z__FREE((Job)->Threads);    \
        z__FREE((Job)->fn);         \
        (Job)->Thread_Num = 0;      \
    }


// Varied Jobs //

typedef
    struct {                          
        z__fnptr(*fn, void *, void *);
        void **Args;                  
        pthread_t *Threads;           
        z__u32 Thread_Num;            
    }z__pt_VarJob;

#define z__pt_VarJob_new(vj , n)\
    {\
        (vj)->Thread_Num = n;                                                      \
        (vj)->Args = z__MALLOC(sizeof(*(vj)->Args) * (vj)->Thread_Num);          \
        (vj)->fn = z__MALLOC(sizeof(*(vj)->fn) * (vj)->Thread_Num);              \
        (vj)->Threads = z__CALLOC(sizeof(*(vj)->Threads), (vj)->Thread_Num);     \
    }

#define z__pt_VarJob_delete(vj)\
    {                              \
        z__FREE((vj)->Args);       \
        z__FREE((vj)->Threads);    \
        z__FREE((vj)->fn);         \
        (vj)->Thread_Num = 0;      \
    }

inline void z__pt_VarJob_set_Arg_id(z__pt_VarJob *vj, z__u32 id, z__u32 of)
{
    z__u32 *arg_id = vj->Args[of];
    *arg_id = id;
}

#define z__pt_VarJob_bind_Arg(vj, ArgContext, of)\
    {                                   \
        (vj)->Args[of] = (ArgContext);  \
    }


#define z__pt_VarJob_bind_fn(vj, fn_name, of) \
    {                                     \
        (vj)->fn[of] =  (void*)fn_name;  \
    }

#define z__pt_VarJob_run(vj)\
    {\
        for (int i = 0; i < (vj)->Thread_Num; ++i) {\
            z__pt_VarJob_set_Arg_id(vj, i, i);\
            pthread_create(&(vj)->Threads[i], NULL, (vj)->fn[i], (vj)->Args[i]);   \
        }                                                                           \
    }\

#define z__pt_VarJob_thread_join(vj)\
    {                                                   \
        for (int i = 0; i < (vj)->Thread_Num; ++i) {   \
            pthread_join((vj)->Threads[i] ,NULL);      \
        }                                               \
    }

#define z__pt_VarJob_end(vj)\
    {\
        z__pt_VarJob_thread_join(vj);\
        z__pt_VarJob_delete(vj);      \
    }


#endif
