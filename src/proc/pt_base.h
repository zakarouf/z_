#ifndef ZAKAROUF__Z__PROC_PT_BASE_H
#define ZAKAROUF__Z__PROC_PT_BASE_H


#define z__pt_Context_Tag(TagN, ...)\
    struct z__pt_Context__tag##TagN {   \
        __VA_ARGS__                     \
    }

#define z__pt_ArgContext_Tag(ContextTag, TagN, ...)\
    struct z__pt_ArgContext__tag##TagN {                \
        z__u32 id;                                      \
        struct z__pt_Context__tag##ContextTag *context; \
        __VA_ARGS__;                                    \
    }

#define z__pt_Context(TagN)     struct z__pt_Context__tag##TagN
#define z__pt_ArgContext(TagN)  struct z__pt_ArgContext__tag##TagN


#define z__pt_Job(ArgContext)\
    struct {                          \
        z__fnptr(*fn, void *, void *);\
        struct z__pt_ArgContext__tag##ArgContext *Arg;\
        pthread_t *Threads;           \
        z__u32 Thread_Num;            \
    }

#define z__pt_Job_new(Job, n)\
    {                                                                               \
        (Job)->Thread_Num = n;                                                      \
        (Job)->Arg = z__MALLOC(sizeof(*(Job)->Arg) * (Job)->Thread_Num);                 \
        (Job)->fn = z__MALLOC(sizeof(*(Job)->fn) * (Job)->Thread_Num);              \
        (Job)->Threads = z__CALLOC(sizeof(*(Job)->Threads), (Job)->Thread_Num);    \
    }

#define z__pt_Job_bind_Arg(Job, ArgContext, of) \
    {                                           \
        (Job)->Arg[of] = (ArgContext);          \
    }

#define z__pt_Job_bind_fn(Job, fn_name, of) \
    {                                     \
        (Job)->fn[of] =  (void*)fn_name;  \
    }

#define z__pt_ArgContext_bind_Context(ArgContext, Context)\
    {                                   \
        (ArgContext)->context = Context;\
    }

#define z__pt_Job_run(Job)\
    {\
        for (int i = 0; i < (Job)->Thread_Num; ++i) {\
            (Job)->Arg[i].id = i;\
            pthread_create(&(Job)->Threads[i], NULL, (Job)->fn[i], &(Job)->Arg[i]);\
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
        z__FREE((Job)->Arg);        \
        z__FREE((Job)->Threads);    \
        z__FREE((Job)->fn);         \
        (Job)->Thread_Num = 0;      \
    }

#define z__pt_Arg_getContext(Arg) (Arg).context


#endif
