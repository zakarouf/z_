#ifndef ZAKAROUF__ZTYPES_TYPES__LLIST_H
#define ZAKAROUF__ZTYPES_TYPES__LLIST_H

#include "mem.h"

#define z__LinkType(TAG)\
    struct _z__linkLs##TAG

#define z__Link(NEWTAG, DT, ...)\
    z__LinkType(NEWTAG) {              \
        DT data;                       \
        __VA_ARGS__;                   \
        z__LinkType(NEWTAG)  *next;    \
        z__LinkType(NEWTAG)  *prev;    \
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

#define z__LList_new(zls, D...)\
    {                                                   \
        (zls)->head = z__MALLOC(sizeof(*(zls)->head));  \
        (zls)->head->next = NULL;                       \
        (zls)->head->prev = NULL;                       \
        (zls)->head->data = D;                          \
        (zls)->cursor = (zls)->head;                    \
        (zls)->tail = (zls)->head;                      \
    }

#define z__LList_popHead(zls)\
    {                                           \
        if((zls)->head != NULL) {               \
            if(((zls)->head->prev != NULL)) {   \
                (zls)->head = (zls)->head->prev;\
                z__FREE((zls)->head->next);     \
                (zls)->head->next = NULL;       \
            }                                       \
        }                                           \
    }
#define z__LList_popTail(zls)\
    {                                               \
        if ((zls)->tail != NULL) {                  \
            if ((zls)->tail->next) {                \
                (zls)->tail = (zls)->tail->next;    \
                z__FREE((zls)->tail->prev);         \
                (zls)->tail->prev = NULL;           \
            }                                       \
        }                                           \
    }

#define z__LList_delete(zls)\
    {                                   \
        while((zls)->head->prev != NULL)\
        {                               \
            z__LList_popHead(zls);      \
        }                               \
        z__FREE((zls)->head);           \
        (zls)->head = NULL;             \
    }
    
#define z__LList_pushHead(zls, D)\
    {                                                                   \
        (zls)->head->next = z__MALLOC(sizeof( *(zls)->head->next) );    \
        (zls)->head->next->prev = (zls)->head;                          \
        (zls)->head = (zls)->head->next;                                \
                                                                        \
        (zls)->head->data = D;                                          \
        (zls)->head->next = NULL;                                       \
    }
#define z__LList_pushTail(zls, D)\
    {                                                                   \
        (zls)->tail->prev = z__MALLOC(sizeof( *(zls)->tail->prev ) );   \
        (zls)->tail->prev->next = (zls)->tail;                          \
        (zls)->tail = (zls)->tail->prev;                                \
        (zls)->tail->prev = NULL;                                       \
                                                                        \
        (zls)->tail->data = D;                                          \
    }
    

#define z__LList_inext(zls, n)\
    {                                                               \
        for(int i = 0; i < n && (zls)->cursor->next != NULL; i++)   \
        {                                                           \
            (zls)->cursor = (zls)->cursor->next;                    \
        }                                                           \
    }

#define z__LList_iprev(zls, n)\
    {                                                               \
        for(int i = 0; i < n && (zls)->cursor->prev != NULL; i++)   \
        {                                                           \
            (zls)->cursor = (zls)->cursor->prev;                    \
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
    {                                           \
        if((zls)->cursor->next) {               \
            (zls)->cursor = (zls)->cursor->next;\
        }                                       \
    }                                           

#define z__LList_setCursorPrev(zls)\
    {                                           \
        if((zls)->cursor->prev) {               \
            (zls)->cursor = (zls)->cursor->prev;\
        }                                       \
    }

#define z__LList_pushCursor_next(zls, D)\
    {                                                                       \
        if((zls)->cursor) {                                                 \
            (zls)->head->next = (zls)->cursor->next;                        \
            (zls)->cursor->next = z__MALLOC(sizeof(*(zls)->cursor->next));  \
            (zls)->cursor->next->data = D;                                  \
            (zls)->cursor->next->prev = (zls)->cursor;                      \
            (zls)->cursor->next->next = (zls)->head->next;                  \
            (zls)->head->next->prev = (zls)->cursor->next;                  \
            (zls)->head->next = NULL;                                       \
        }                                                                   \
    }
#define z__LList_pushCursor_prev(zls, D)\
    {                                                                       \
        if ((zls)->cursor) {                                                \
            (zls)->head->next = (zls)->cursor->prev;                        \
            (zls)->cursor->prev = z__MALLOC(sizeof(*(zls)->cursor->prev));  \
            (zls)->cursor->prev->next = (zls)->cursor;                      \
            (zls)->cursor->prev->prev = (zls)->head->next;                  \
            (zls)->head->next->next = (zls)->cursor->prev;                  \
            (zls)->head->next = NULL;                                       \
        }                                                                   \
    }

#define z__LList_cursorDel_setPrev(zls)\
    {                                                               \
        if ((zls)->cursor->prev != NULL)                            \
        {                                                           \
            (zls)->head->next = (zls)->cursor->prev;                \
                                                                    \
            (zls)->cursor->prev->next = (zls)->cursor->next;        \
            (zls)->cursor->next->prev = (zls)->cursor->prev;        \
                                                                    \
            z__FREE((zls)->cursor);                                 \
            (zls)->cursor = (zls)->head->next;                      \
            (zls)->head->next = NULL;                               \
        }                                                           \
    }
#define z__LList_cursorDel_setNext(zls)\
    {                                                               \
        if ((zls)->cursor->next != NULL)                            \
        {                                                           \
            (zls)->head->next = (zls)->cursor->next;                \
                                                                    \
            (zls)->cursor->prev->next = (zls)->cursor->next;        \
            (zls)->cursor->next->prev = (zls)->cursor->prev;        \
                                                                    \
            z__FREE((zls)->cursor);                                 \
            (zls)->cursor = (zls)->head->next;                      \
            (zls)->head->next = NULL;                               \
        }                                                           \
    }
#define z__LList_cursorDel(zls)\
    {                                                           \
        if ((zls)->cursor->prev) {                              \
             (zls)->cursor->prev->next = (zls)->cursor->next;   \
        }                                                       \
        if ((zls)->cursor->next) {                              \
            (zls)->cursor->next->prev = (zls)->cursor->prev;    \
        }                                                       \
        z__FREE((zls)->cursor);                                 \
        (zls)->cursor = NULL;                                   \
    }
#define z__LList_cursorTakeOut(zls, var)\
    {\
        if ((zls)->cursor->prev) {                              \
             (zls)->cursor->prev->next = (zls)->cursor->next;   \
        }                                                       \
        if ((zls)->cursor->next) {                              \
            (zls)->cursor->next->prev = (zls)->cursor->prev;    \
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

