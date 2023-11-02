#ifndef ZAKAROUF__ZTYPES_TYPES__LLIST_H
#define ZAKAROUF__ZTYPES_TYPES__LLIST_H

#include "std/mem.h"

#define z__LinkType(TAG)\
    struct _z__linkLs##TAG

#define z__Link(NEWTAG, T, ...)\
    z__LinkType(NEWTAG) {              \
        T data;                        \
        __VA_ARGS__;                   \
        z__LinkType(NEWTAG)  *_next;    \
        z__LinkType(NEWTAG)  *_prev;    \
    }

#define z__LList(TAG, ...)\
    struct {                       \
        z__LinkType(TAG)  *head;    \
        z__LinkType(TAG)  *tail;    \
        z__LinkType(TAG)  *cursor;  \
                     \
        __VA_ARGS__;        /* Additialnal members for the the user*/\
    }
/*
 * How to Create a Linked list
 *         z__Link(<NewTagName>, <MainDataType>, <AdditionalMembers> );
 * typedef z__Link(<NewTagName>, <MainDataType>, <AdditionalMembers> );  << Creates a typedef
 * :Create a Link
 *         z__LList(<TagName>, <AdditionalMembers>) <Var>;
 * typedef z__LList(<TagName>, <AdditionalMembers>) <newType>;  << Creates a typedef
 * Link list defination is complete;
 */

#define z__LList_new(zls, ...)\
    {                                                   \
        (zls)->head = z__MALLOC(sizeof(*(zls)->head));  \
        (zls)->head->_next = NULL;                       \
        (zls)->head->_prev = NULL;                       \
        (zls)->head->data = __VA_ARGS__;                \
        (zls)->cursor = (zls)->head;                    \
        (zls)->tail = (zls)->head;                      \
    }

#define z__LList_popHead(zls)\
    {                                           \
        if((zls)->head != NULL) {               \
            if(((zls)->head->_prev != NULL)) {   \
                (zls)->head = (zls)->head->_prev;\
                z__FREE((zls)->head->_next);     \
                (zls)->head->_next = NULL;       \
            }                                       \
        }                                           \
    }
#define z__LList_popTail(zls)\
    {                                               \
        if ((zls)->tail != NULL) {                  \
            if ((zls)->tail->_next) {                \
                (zls)->tail = (zls)->tail->_next;    \
                z__FREE((zls)->tail->_prev);         \
                (zls)->tail->_prev = NULL;           \
            }                                       \
        }                                           \
    }

#define z__LList_delete(zls)\
    {                                   \
        while((zls)->head->_prev != NULL)\
        {                               \
            z__LList_popHead(zls);      \
        }                               \
        z__FREE((zls)->head);           \
        (zls)->head = NULL;             \
    }
    
#define z__LList_pushHead(zls, D)\
    {                                                                   \
        (zls)->head->_next = z__MALLOC(sizeof( *(zls)->head->_next) );  \
        (zls)->head->_next->_prev = (zls)->head;                         \
        (zls)->head = (zls)->head->_next;                               \
                                                                        \
        (zls)->head->data = D;                                          \
        (zls)->head->_next = NULL;                                      \
    }

#define z__LList_pushTail(zls, D)\
    {                                                                   \
        (zls)->tail->_prev = z__MALLOC(sizeof( *(zls)->tail->_prev ) );   \
        (zls)->tail->_prev->_next = (zls)->tail;                         \
        (zls)->tail = (zls)->tail->_prev;                                \
        (zls)->tail->_prev = NULL;                                       \
                                                                        \
        (zls)->tail->data = D;                                          \
    }
    

#define z__LList_inext(zls, n)\
    {                                                               \
        for(int i = 0; i < n && (zls)->cursor->_next != NULL; i++)  \
        {                                                           \
            (zls)->cursor = (zls)->cursor->_next;                   \
        }                                                           \
    }

#define z__LList_iprev(zls, n)\
    {                                                               \
        for(int i = 0; i < n && (zls)->cursor->_prev != NULL; i++)   \
        {                                                           \
            (zls)->cursor = (zls)->cursor->_prev;                    \
        }                                                           \
    }

#define z__LList_setCursorHead(zls)\
    {                                           \
        (zls)->cursor = (zls)->head;            \
    }                                           

#define z__LList_setCursorTail(zls)\
    {                                           \
        (zls)->cursor = (zls)->tail;            \
    }
#define z__LList_setCursorNext(zls)\
    {                                               \
        if((zls)->cursor->_next) {                  \
            (zls)->cursor = (zls)->cursor->_next;   \
        }                                           \
    }                                           

#define z__LList_setCursorPrev(zls)\
    {                                           \
        if((zls)->cursor->_prev) {               \
            (zls)->cursor = (zls)->cursor->_prev;\
        }                                       \
    }

#define z__LList_pushCursor_next(zls, D)\
    {                                                                       \
        if((zls)->cursor) {                                                 \
            (zls)->head->_next = (zls)->cursor->_next;                      \
            (zls)->cursor->_next = z__MALLOC(sizeof(*(zls)->cursor->_next));\
            (zls)->cursor->_next->data = D;                                  \
            (zls)->cursor->_next->_prev = (zls)->cursor;                      \
            (zls)->cursor->_next->_next = (zls)->head->_next;                  \
            (zls)->head->_next->_prev = (zls)->cursor->_next;                  \
            (zls)->head->_next = NULL;                                       \
        }                                                                   \
    }
#define z__LList_pushCursor_prev(zls, D)\
    {                                                                       \
        if ((zls)->cursor) {                                                \
            (zls)->head->_next = (zls)->cursor->_prev;                        \
            (zls)->cursor->_prev = z__MALLOC(sizeof(*(zls)->cursor->_prev));  \
            (zls)->cursor->_prev->_next = (zls)->cursor;                      \
            (zls)->cursor->_prev->_prev = (zls)->head->_next;                  \
            (zls)->head->_next->_next = (zls)->cursor->_prev;                  \
            (zls)->head->_next = NULL;                                       \
        }                                                                   \
    }

#define z__LList_cursorDel_setPrev(zls)\
    {                                                               \
        if ((zls)->cursor->_prev != NULL)                            \
        {                                                           \
            (zls)->head->_next = (zls)->cursor->_prev;               \
                                                                    \
            (zls)->cursor->_prev->_next = (zls)->cursor->_next;      \
            (zls)->cursor->_next->_prev = (zls)->cursor->_prev;       \
                                                                    \
            z__FREE((zls)->cursor);                                 \
            (zls)->cursor = (zls)->head->_next;                     \
            (zls)->head->_next = NULL;                              \
        }                                                           \
    }
#define z__LList_cursorDel_setNext(zls)\
    {                                                               \
        if ((zls)->cursor->_next != NULL)                           \
        {                                                           \
            (zls)->head->_next = (zls)->cursor->_next;              \
                                                                    \
            (zls)->cursor->_prev->_next = (zls)->cursor->_next;      \
            (zls)->cursor->_next->_prev = (zls)->cursor->_prev;       \
                                                                    \
            z__FREE((zls)->cursor);                                 \
            (zls)->cursor = (zls)->head->_next;                      \
            (zls)->head->_next = NULL;                               \
        }                                                           \
    }

#define z__LList_cursorDel(zls)\
    {                                                           \
        if ((zls)->cursor->_prev) {                              \
             (zls)->cursor->_prev->_next = (zls)->cursor->_next;   \
        }                                                       \
        if ((zls)->cursor->_next) {                              \
            (zls)->cursor->_next->_prev = (zls)->cursor->_prev;    \
        }                                                       \
        z__FREE((zls)->cursor);                                 \
        (zls)->cursor = NULL;                                   \
    }
#define z__LList_cursorTakeOut(zls, var)\
    {\
        if ((zls)->cursor->_prev) {                              \
             (zls)->cursor->_prev->_next = (zls)->cursor->_next;   \
        }                                                       \
        if ((zls)->cursor->_next) {                              \
            (zls)->cursor->_next->_prev = (zls)->cursor->_prev;    \
        }                                                       \
        var = (zls)->cursor;									\
        (zls)->cursor = NULL;                                   \
    }


#define z__LList_getCursor(zls)         		(zls).cursor         		// Get Cursor  
#define z__LList_getCursorData(zls)           	(zls).cursor->data     		// Get Data From Cursor
#define z__LList_getCursorMember(zls, member) 	(zls).cursor->member   		// Get Member Data from Cursor
#define z__LList_getMember(zls, member) 		(zls).member   			    // Get Member Data from Cursor
#define z__LList_getHead(zls)           		(zls).head             		// Get Head
#define z__LList_getTail(zls)           		(zls).tail             		// Get Tail


#endif

