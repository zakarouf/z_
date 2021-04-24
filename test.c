#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/z_.h"

#if 0
void *newfn (char const * msg, char const * fl, char const * fn, int const l, void *ptr)
{
	FILE *fp = fopen("logtest", "a");

	fprintf(fp, "%s >> %s:%d (%s):: %p\n", msg, fl, l, fn, ptr);

	fclose(fp);
	return ptr;
}

void t1 (void)
{	
	z__mem_init();
	z__mem_logSet(newfn);
	char *s = z__mem_tmalloc(10);
	char *a = z__mem_tmalloc(42);
	z__mem_tfree(s);
	z__mem_tfree(a);

	char *f = z__tvMALLOC(23);
	z__tvFREE(f);

	printf("%d\n" , z__mem_checkfor_usedMemory());
}


void test_llist(void)
{
	z__Link(tag1, int);

	z__LList(tag1) t;
	z__LList_create(&t, 0);

	for (int i = 1; i < 12; ++i)
	{
		z__LList_pushHead(&t, i);
	}

	// Original
	z__LList_setCursorTail(&t);
	printf("[ ");
	while (z__LList_getCursor(t)->next)
	{
		printf("%d ", t.cursor->data);
		z__LList_inext(&t, 1);
	}
	printf("%d ]\n", t.cursor->data);


	// Deletion
	z__LList_setCursorTail(&t);
	z__LList_inext(&t, 5);
	z__LList_cursorDel(&t);


	// New List
	z__LList_setCursorTail(&t);
	printf("[ ");
	while (z__LList_getCursor(t)->next)
	{
		printf("%d ", t.cursor->data);
		z__LList_inext(&t, 1);
	}
	printf("%d ]\n", t.cursor->data);

}
#endif
/*
#define z__Arr_slice_5(arr, dest, from, upto, step)\
{                                                       \
    if ((arr).lenUsed > (dest)->len) {                  \
        z__Arr_resize(dest, (arr).lenUsed);             \
    }                                                   \
    int j = 0, i = from;                                \
    for (; i < upto; i += step,j++) {                   \
        (dest)->data[j] = (arr).data[i];                \
    }                                                   \
    (dest)->lenUsed = (j);                              \
}

#define z__Arr_slice_4(arr, dest, from, upto) z__Arr_slice_5(arr, dest, from, upto, 1)
#define z__Arr_slice_3(arr, dest, from) z__Arr_slice_4(arr, dest, from, (arr).lenUsed-1)
#define z__Arr_slice_2(arr, dest) z__Arr_slice_4(arr, dest, 0, (arr).lenUsed-1)
#define z__Arr_slice(...) zpp__Args_Overload(z__Arr_slice_, __VA_ARGS__)
*/

typedef z__Arr(z__u8) Array_u8;
Array_u8 getarray(void)
{
	Array_u8 f;
	z__Arr_new(&f, 30);
	z__Arr_map(&f);

	return f;
}

#define IF (
#define ENDIF )
#define THEN ?
#define ELSE :

#define and &&
#define or ||
#define not !
#define equals ==
#define notequals !=
#define be =

#define addedby +
#define subtratedby -
#define multipliedby *
#define dividedby /

void test_yo_wtf(void)
{
	int x be 2, y be 1;
	int a be ({ 
		IF (y > x ) THEN
			(x be x multipliedby x)
		ELSE
			IF y equals 1 THEN
				(y be 64) 
			ELSE
				(y be x - 1)
			ENDIF
		ENDIF;

		x multipliedby y;
	});
	printf("%d:%d\n", y ,a);
}


