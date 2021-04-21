#ifndef ZAKAROUF__ZTYPES_TYPES_H
#define ZAKAROUF__ZTYPES_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"

#ifdef Z___TYPE_INCLUED_CGLM
    #include <cglm/cglm.h>
#endif

/* Basic Types */
typedef uint8_t  z__u8;
typedef uint16_t z__u16;
typedef uint32_t z__u32;
typedef uint64_t z__u64;

typedef uint_fast8_t  z__u8_f;
typedef uint_fast16_t z__u16_f;
typedef uint_fast32_t z__u32_f;
typedef uint_fast64_t z__u64_f;

//uint_fast8_t;
typedef int8_t  z__i8;
typedef int16_t z__i16;
typedef int32_t z__i32;
typedef int64_t z__i64;

typedef int_fast8_t  z__i8_f;
typedef int_fast16_t z__i16_f;
typedef int_fast32_t z__i32_f;
typedef int_fast64_t z__i64_f;

typedef float z__f32;
typedef double z__f64;

typedef int z__int;
typedef float z__float;
typedef bool z__bool;
typedef void* z__ptr;
typedef z__u8 z__byte;

typedef intmax_t z__imax;
typedef uintmax_t z__umax;
typedef intptr_t z__iptr;
typedef uintptr_t z__uptr;

typedef ptrdiff_t z__ptrdiff;

#define z__sizeof sizeof
typedef size_t z__size;

#ifdef Z___TYPE_CONFIG__USE_MEM

    void *z__mem_safe_realloc(void * data, size_t size);

    #ifdef Z___TYPE_CONFIG__USE_MEM__TRACK

        void z__mem_init(void);
        void z__mem_end(void);
        z__ptr z__mem_tmalloc(z__size sz);
        z__ptr z__mem_tcalloc(z__size count ,z__size sz);
        void z__mem_tfree(z__ptr mem);
        z__u32 z__mem_checkfor_usedMemory(void);

        #define z__tMALLOC   z__mem_tmalloc
        #define z__tREALLOC  realloc
        #define z__tCALLOC   z__mem_tcalloc
        #define z__tFREE     z__mem_tfree

        #ifdef Z___TYPE_CONFIG__USE_MEM__VTRACK

            extern void * (*_Z__MEM_LOG_FN_PTR_)(char const *, char const *, char const *, int const, void *);
            void *z__mem_logSet(void * (*newfnptr)(char const *, char const *, char const *, int const, void *));

            #define z__tvMALLOC(s)      _Z__MEM_LOG_FN_PTR_("Malloc: " ,__FILE__, __func__, __LINE__, z__tMALLOC(s));
            #define z__tvCALLOC(c, s)   _Z__MEM_LOG_FN_PTR_("Calloc: " ,__FILE__, __func__, __LINE__, z__tMALLOC(c, s));
            #define z__tvFREE(ptr)      _Z__MEM_LOG_FN_PTR_("Free:   " ,__FILE__, __func__, __LINE__, ptr); z__tFREE(ptr)

        #endif

        #ifdef Z___TYPE_CONFIG__USE_MEM__TRACK_AS_DEFAULT

            #define z__MALLOC    z__tMALLOC   
            #define z__REALLOC   z__tREALLOC  
            #define z__CALLOC    z__tCALLOC   
            #define z__FREE      z__tFREE     

        #endif
    #endif

#endif

/* fallback */
#ifndef z__MALLOC
    #define z__MALLOC   malloc
#endif
#ifndef z__REALLOC
    #define z__REALLOC  realloc
#endif
#ifndef z__CALLOC
    #define z__CALLOC   calloc
#endif
#ifndef z__FREE
    #define z__FREE     free
#endif
#ifndef z__REALLOC_SAFE
    #define z__REALLOC_SAFE z__mem_safe_realloc
#endif

/* Vectors And Matrices For Graphical Maths */
#ifdef Z___TYPE_CONFIG__USE_VECTORS

    // CGLM PRE_REQUSITE GOES HERE...
    #ifdef Z___TYPE_USE_CGLM
        
    #endif

    #ifdef Z___TYPE_CONFIG__USE_TYPE_ARR_VECTOR
        /* |x, y, z, w| -> w is the last */
        #ifdef Z___TYPE_INCLUED_CGLM


            typedef z__int                  z__ivec2[2];
            typedef ivec3                   z__ivec3;
            typedef z__int                  z__ivec4[4];

            typedef vec2                    z__vec2;
            typedef vec3                    z__vec3;
            typedef vec4                    z__vec4;

            typedef versor                  z__versor;

            typedef mat2                    z__mat2;
            typedef mat3                    z__mat3;
            typedef mat4                    z__mat4;



        #else


            typedef z__i32                  z__ivec2[2];
            typedef z__i32                  z__ivec3[3];
            typedef z__i32                  z__ivec4[4];

            typedef z__f32                  z__vec2[2];
            typedef z__f32                  z__vec3[3];
            typedef z__f32                  z__vec4[4];

            typedef z__vec4                 z__versor;

            typedef z__vec2                 z__mat2[2];
            typedef z__vec3                 z__mat3[3];
            typedef z__vec4                 z__mat4[4];

        #endif

        #define z__vec_x(vec) vec[0]
        #define z__vec_y(vec) vec[1]
        #define z__vec_z(vec) vec[2]
        #define z__vec_w(vec) vec[3]


    #endif

    #ifdef Z___TYPE_CONFIG__USE_TYPE_STRUCT_VECTOR

        /* New type declarator, Vector */
        #define z__Vector(T, ...)\
            struct              \
            {                   \
                T __VA_ARGS__;  \
            }

        #ifdef Z___TYPE_CONFIG__USE_f64_FOR_VECTOR_STRUCT
            #define __vecDefType z__f64
        #else
            #define __vecDefType z__f32
        #endif

            typedef z__Vector(__vecDefType, x, y) z__Vector2;
            typedef z__Vector(__vecDefType, x, y, z) z__Vector3;
            typedef z__Vector(__vecDefType, x, y, z, w) z__Vector4;
        #undef __vecDefType

        #ifdef Z___TYPE_CONFIG__USE_i64_FOR_INT_VECTOR_STRUCT
            #define __vecDefType z__i64
        #else
            #define __vecDefType z__i32
        #endif

            typedef z__Vector(__vecDefType, x, y) z__Vint2;
            typedef z__Vector(__vecDefType, x, y, z) z__Vint3;
            typedef z__Vector(__vecDefType, x, y, z, w) z__Vint4;
        #undef __vecDefType

    #endif

#endif //#ifdef Z___TYPE_CONFIG__USE_VECTORS

#ifdef Z___TYPE_CONFIG__USE_IRREGULAR_ARRAYTYPE
    /* Unsafe Irregular Object Holder array */
    typedef struct __ZAKAROUF__IRREGULAR_TYPE_STRUCT
    {
        z__ptr *data;
        z__size *size;
        z__u8  *typeID;
        z__i32 len;
        z__i32 lenUsed;
        char** comment;

    }z__Irrg;

    z__Irrg z__Irrg_create(z__u32 len);
    void z__Irrg_resize(z__Irrg *irgt, z__size newsize);
    void z__Irrg_push(z__Irrg *irgt, void *val, z__size size, z__u8 typeID, const char *comment, z__i32 commentLength);
    void z__Irrg_pop(z__Irrg *irgt);
    void z__Irrg_delete(z__Irrg *irgt);

    #define z__Irrg_getValSize(arr, of)       (arr.size[of])
    #define z__Irrg_gettypeID(arr, of)        (arr.typeID[of])
    #define z__Irrg_getComment(arr, of)       (arr.comment[of])
    #define z__Irrg_getVal(arr, of, T)        ( *( T *)(*arr.data[of]) )
    #define z__Irrg_getValTop(arr, T)         ( *( T *)(*arr.data[arr.lenUsed-1]) )
    #define z__Irrg_getAddress(arr, of)       (*arr.data[of])
    #define z__Irrg_getLen(arr)               (arr.len)
    #define z__Irrg_getUsed(arr)              (arr.lenUsed)

#endif

/* Unknown Similar size Unsafe type Arrays */
typedef struct __ZAKAROUF__SIMPARR_TYPE_STRUCT
{
    z__ptr data;
    z__size size;
    z__u8  typeID;
    z__u32 len;
    z__u32 lenUsed;
    char *comment;

}z__Dynt;


z__Dynt z__Dynt_create(z__size size, z__u32 len, const char *comment, z__i32 commentLength, z__u8 typeID);
z__Dynt z__Dynt_createFromFile(const char filepath[], z__size sizePerVal, const char *comment, z__i32 commentLength, z__u8 typeID);
void z__Dynt_delete(z__Dynt* arrt, z__bool nameFree);
void z__Dynt_push( z__Dynt *arrt, void *val);
void z__Dynt_pop( z__Dynt *arrt);
void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize);
z__Dynt z__Dynt_makeCopy(const z__Dynt arrt);

#define z__Dynt_getValSize(arr)           (arr.size)
#define z__Dynt_getTop(arr, T)         ( *( T *)( (arr.data) + ((arr.lenUsed-1) * arr.size)) )
#define z__Dynt_getVal(arr, index , T) ( *( T *)( (arr.data) + (index * arr.size)) )
#define z__Dynt_getAddress(arr, index) ((arr.data) + (index * arr.size))
#define z__Dynt_getComment(arr)           (arr.comment)
#define z__Dynt_getLen(arr)               (arr.len)
#define z__Dynt_getUsed(arr)              (arr.lenUsed)

/* Known Type-safe arrays */
#define z__ArrFx(T, sz, N) T N[sz]

#define z__ArrSxDef(T, sz, tagName)\
    struct  _z__SxArr_deftag_ ## tagName	\
    {                           		\
        T data[sz];             		\
        const z__i32 len;       		\
        z__i32 lenUsed;         		\
    }

#define z__ArrSx(SDeftag, N)\
    struct _z__SxArr_deftag_ ## SDeftag N = {.len = sizeof(N.data)/sizeof(N.data[0]), .lenUsed = 0}

#define z__ArrSxT(T, N)\
    T N = {.len = sizeof(N.data)/sizeof(N.data[0]), .lenUsed = 0}

#define z__ArrSxI(T, sz, N)\
    z__SxArrDef(T, sz, N) N = {.len = sz, .lenUsed = 0}

#define z__ArrSx_push(arr)\
    {                                           \
        if((arr)->lenUsed < (arr->len))         \
        {                                       \
            (arr)->data[(arr)->lenUsed] = val;  \
            (arr)->lenUsed += 1;                \
        };                                      \
    }
#define z__ArrSx_pop(arr)\
    {                           \
        if((arr)->lenUsed >= 0) \
        {                       \
            (arr)->lenUsed -= 1;\
        };                      \
    }

#define z__Arr(T)\
    struct              \
    {                   \
        T* data;        \
        z__i32 len;     \
        z__i32 lenUsed; \
    }

#define z__Arr_delete(arr)\
    {                           \
        (arr)->len = -1;        \
        (arr)->lenUsed = -1;    \
        free((arr)->data);      \
    }

#define z__Arr_create(arr, sz)\
    {                                                   \
        (arr)->data = malloc(sizeof(*(arr)->data)*sz);  \
        (arr)->len = sz;                                \
        (arr)->lenUsed = 0;                             \
    }
#define z__Arr_push(arr, val...)\
    {                                                                                           \
        if ((arr)->lenUsed >= (arr)->len)                                                       \
        {                                                                                       \
            (arr)->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;                                   \
            (arr)->data = z__REALLOC_SAFE((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );   \
        }                                                                                       \
        (arr)->data[(arr)->lenUsed] = val;                                                      \
        (arr)->lenUsed += 1;                                                                    \
    }
#define z__Arr_pushMC(arr, val...)\
    {                                                                                           \
        if ((arr)->lenUsed >= (arr)->len)                                                       \
        {                                                                                       \
            (arr)->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;                                   \
            (arr)->data = z__REALLOC_SAFE((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );   \
        }                                                                                       \
        memcpy(&(arr)->data[(arr)->lenUsed], (val), sizeof(*(arr)->data));                      \
        (arr)->lenUsed += 1;                                                                    \
    }
#define z__Arr_pushN(arr, val...)\
    {                                           \
        (arr)->data[(arr)->lenUsed] = val;      \
        (arr)->lenUsed += 1;                    \
    }
#define z__Arr_pushNMC(arr, val...)\
    {                                                                       \
        memcpy(&(arr)->data[(arr)->lenUsed], (val), sizeof(*(arr)->data));  \
        (arr)->lenUsed += 1;                                                \
    }
#define z__Arr_resize(arr, newSize)\
    {                                                                               \
        if ((arr)->lenUsed > newSize)                                               \
        {                                                                           \
           ( arr)->lenUsed = newSize;                                               \
        }                                                                           \
        (arr)->data = z__REALLOC_SAFE((arr)->data, newSize * sizeof(*(arr)->data)); \
        (arr)->len = newSize;                                                       \
    }
#define z__Arr_pop(arr)\
    {                                                                               \
        (arr)->lenUsed -= 1;                                                        \
        if (((arr)->len - (arr)->lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)     \
        {                                                                           \
            z__Arr_resize(arr, (arr)->len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);    \
        }                                                                           \
    }
#define z__Arr_join(dest, from)\
    {                                                                                                   \
        z__i32 totalLength = (dest)->lenUsed*sizeof(*(dest)->data) + from.lenUsed*sizeof(*from.data);   \
        if (totalLength > (dest)->len)                                                                  \
        {                                                                                               \
            z__Arr_resize(dest, totalLength+1)                                                          \
        }                                                                                               \
        memcpy(&(dest)->data[(dest)->lenUsed], from.data, from.lenUsed * sizeof(*(dest)->data));        \
    }

#ifdef Z___TYPE_CONFIG__USE_TYPE_ARR_PREDEFINED

    // Signed
    typedef z__Arr(z__i8)  z__i8Arr;
    typedef z__Arr(z__i16) z__i16Arr;
    typedef z__Arr(z__i32) z__i32Arr;
    typedef z__Arr(z__i64) z__i64Arr;

    // Unsigned
    typedef z__Arr(z__u8)  z__u8Arr;
    typedef z__Arr(z__u16) z__u16Arr;
    typedef z__Arr(z__u32) z__u32Arr;
    typedef z__Arr(z__u64) z__u64Arr;

    // Floats
    typedef z__Arr(z__f32) z__f32Arr;
    typedef z__Arr(z__f64) z__f64Arr;

    // Boolean
    typedef z__Arr(z__bool) z__boolArr;

    // Void *
    typedef z__Arr(z__ptr) z__ptrArr;
    typedef z__Arr(void) z__voidArr;



    #ifdef Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS

        // Initialization
        z__i8Arr z__i8Arr_create(z__u32 len);
        z__i16Arr z__i16Arr_create(z__u32 len);
        z__i32Arr z__i32Arr_create(z__u32 len);
        z__i64Arr z__i64Arr_create(z__u32 len);

        z__u8Arr z__u8Arr_create(z__u32 len);
        z__u16Arr z__u16Arr_create(z__u32 len);
        z__u32Arr z__u32Arr_create(z__u32 len);
        z__u64Arr z__u64Arr_create(z__u32 len);

        z__f64Arr z__f64Arr_create(z__u32 len);

        z__boolArr z__boolArr_create(z__u32 len);

        z__ptrArr z__ptrArr_create(z__u32 len);

        // Adding Value At top
        void z__i8Arr_push( z__i8Arr *arr, z__i8 val);
        void z__i16Arr_push( z__i16Arr *arr, z__i16 val);
        void z__i32Arr_push( z__i32Arr *arr, z__i32 val);
        void z__i64Arr_push( z__i64Arr *arr, z__i64 val);

        void z__u8Arr_push( z__u8Arr *arr, z__u8 val);
        void z__u16Arr_push( z__u16Arr *arr, z__u16 val);
        void z__u32Arr_push( z__u32Arr *arr, z__u32 val);
        void z__u64Arr_push( z__u64Arr *arr, z__u64 val);

        void z__f32Arr_push( z__f32Arr *arr, z__f32 val);
        void z__f64Arr_push( z__f64Arr *arr, z__f64 val);

        void z__boolArr_push( z__boolArr *arr, z__bool val);

        // Resizing Arrays
        void z__i8Arr_resize( z__i8Arr *arr, z__i8 newSize);
        void z__i16Arr_resize( z__i16Arr *arr, z__i16 newSize);
        void z__i32Arr_resize( z__i32Arr *arr, z__i32 newSize);
        void z__i64Arr_resize( z__i64Arr *arr, z__i64 newSize);

        void z__u8Arr_resize( z__u8Arr *arr, z__u8 newSize);
        void z__u16Arr_resize( z__u16Arr *arr, z__u16 newSize);
        void z__u32Arr_resize( z__u32Arr *arr, z__u32 newSize);
        void z__u64Arr_resize( z__u64Arr *arr, z__u64 newSize);

        void z__f32Arr_resize( z__f32Arr *arr, z__f32 newSize);
        void z__f64Arr_resize( z__f64Arr *arr, z__f64 newSize);

        void z__boolArr_resize( z__boolArr *arr, z__bool newSize);


        // Removing Value from the top
        #define _z__Arrpop_tmpl(arr, func)\
            {                                                                           \
                (arr)->lenUsed -= 1;                                                    \
                if (((arr)->len - (arr)->lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT) \
                {                                                                       \
                    func (arr, (arr)->len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);        \
                }                                                                       \
            }

        #define z__i8Arr_pop(arr)   _z__Arrpop_tmpl(arr, z__i8Arr_resize )
        #define z__i16Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__i16Arr_resize)
        #define z__i32Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__i32Arr_resize)
        #define z__i64Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__i64Arr_resize)
        #define z__u8Arr_pop(arr)   _z__Arrpop_tmpl(arr, z__u8Arr_resize )
        #define z__u16Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__u16Arr_resize)
        #define z__u32Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__u32Arr_resize)
        #define z__u64Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__u64Arr_resize)
        #define z__f32Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__f32Arr_resize)
        #define z__f64Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__f64Arr_resize)
        #define z__boolArr_pop(arr) _z__Arrpop_tmpl(arr, z__boolArr_resize)


    #endif //Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS


#endif

#ifdef Z___TYPE_CONFIG__USE_ARR_FUNTION_GENERATION_TEMPLATE

    #define z__Arr_FN(T, vT)                            \
        typedef z__Arr(vT) T;                           \
        Z__INLINE T z__Arr ## T ## _create(z__u32 len)  \
        {                                               \
            return (T) {                                \
                .data = malloc(sizeof (vT) * len),      \
                .len = len,                             \
                .lenUsed = 0                            \
            };                                          \
        }                                               \
        \
        Z__INLINE T z__Arr ## T ## _push(z__u32 len)
        

#endif


 #define z__Arr_getLen(arr)          arr.len
 #define z__Arr_getUsed(arr)         arr.lenUsed
 #define z__Arr_getData(arr)         arr.data
 #define z__Arr_getVal(arr, index)   arr.data[index]
 #define z__Arr_getTop(arr)          arr.data[arr.lenUsed-1]
 #define z__Arr_getTopMT(arr)        arr.data[arr.lenUsed]

// Link Lists
#ifdef Z___TYPE_CONFIG__USE_TYPE_LINKLIST
    #define z__LinkStruct(NEWTAG, DT, ...)\
        struct _z__linkLs##NEWTAG {              \
            DT data;                             \
            __VA_ARGS__;                         \
            struct _z__linkLs##NEWTAG  *next;    \
            struct _z__linkLs##NEWTAG  *prev;    \
        }

    #define z__LinkDef(TAG)\
        struct _z__linkLs##TAG

    #define z__Link(TAG, ...)\
        struct {                     \
            z__LinkDef(TAG)  *head;    \
            z__LinkDef(TAG)  *tail;    \
            z__LinkDef(TAG)  *cursor;  \
                         \
            __VA_ARGS__;        /* Additialnal members for the the user*/\
        }
    /*
     * How to Create a Link list
     *         z__LinkStruct(<Name>, <typename>, <AdditionalMembers> );
     * typedef z__LinkStruct(<Name>, <typename>, <AdditionalMembers> );  << Creates a typedef
     * :Create a Link
     *         z__Link(<z__LinkStruct>, <AdditionalMembers>) <Var>;
     * typedef z__Link(<z__LinkStruct>, <AdditionalMembers>) <newType>;  << Creates a typedef
     * Link list defination is complete;
     */

    #define z__Link_create(zls, D...)\
        {                                                   \
            (zls)->head = z__MALLOC(sizeof(*(zls)->head));  \
            (zls)->head->next = NULL;                       \
            (zls)->head->prev = NULL;                       \
            (zls)->head->data = D;                          \
            (zls)->cursor = (zls)->head;                    \
            (zls)->tail = (zls)->head;                      \
        }

    #define z__Link_popHead(zls)\
        {                                           \
            if((zls)->head != NULL) {               \
                if(((zls)->head->prev != NULL)) {   \
                    (zls)->head = (zls)->head->prev;\
                    z__FREE((zls)->head->next);     \
                    (zls)->head->next = NULL;       \
                }                                       \
            }                                           \
        }
    #define z__Link_popTail(zls)\
        {                                               \
            if ((zls)->tail) {                          \
                if ((zls)->tail->next) {                \
                    (zls)->tail = (zls)->tail->next;    \
                    z__FREE((zls)->tail->prev);         \
                    (zls)->tail->prev = NULL;           \
                }                                       \
            }                                           \
        }

    #define z__Link_delete(zls)\
        {                                   \
            while((zls)->head->prev != NULL)\
            {                               \
                z__Link_popHead(zls);       \
            }                               \
            z__FREE((zls)->head);           \
            (zls)->head = NULL;             \
        }
    
    #define z__Link_pushHead(zls, D...)\
        {                                                                   \
            (zls)->head->next = z__MALLOC(sizeof( *(zls)->head->next) );    \
            (zls)->head->next->prev = (zls)->head;                          \
            (zls)->head = (zls)->head->next;                                \
                                                                            \
            (zls)->head->data = D;                                          \
            (zls)->head->next = NULL;                                       \
        }
        

    #define z__Link_inext(zls, n)\
        {                                                               \
            for(int i = 0; i < n && (zls)->cursor->next != NULL; i++)   \
            {                                                           \
                (zls)->cursor = (zls)->cursor->next;                    \
            }                                                           \
        }

    #define z__Link_iprev(zls, n)\
        {                                                               \
            for(int i = 0; i < n && (zls)->cursor->prev != NULL; i++)   \
            {                                                           \
                (zls)->cursor = (zls)->cursor->prev;                    \
            }                                                           \
        }

    #define z__Link_setCursorHead(zls)\
        {                                               \
            while((zls)->cursor->next != NULL)          \
            {                                           \
                (zls)->cursor = (zls)->cursor->next;    \
            }                                           \
        }                                               \

    #define z__Link_setCursorTail(zls)\
        {                                           \
            while((zls)->cursor->prev != NULL)      \
            {                                       \
               (zls)->cursor = (zls)->cursor->prev; \
            }                                       \
        }


    #define z__Link_getCursor(zls)         (zls.cursor)           // Get Cursor  
    #define z__Link_getData(zls)           (zls.cursor->data)     // Get Data From Cursor
    #define z__Link_getMember(zls, member) (zls.cursor->member)   // Get Member Data from Cursor
    #define z__Link_getHead(zls)           (zls.head)             // Get Head
    #define z__Link_getTail(zls)           (zls.tail)             // Get Tail

#endif

#endif // Header Guard
