#ifndef ZAKAROUF__ZPREP_ASSERT_H
#define ZAKAROUF__ZPREP_ASSERT_H

#define zpp__assert_ptr(x, y) ( x==y?true:false )

#define zpp__assert_ptr_checkNULL(x) (x==NULL?true:false)

// Panic

#define zpp__panicif(condition, method)\
    {                   \
        if(condition) { \
            method;     \
        }               \
    }


#endif
