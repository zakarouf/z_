/**
 * This is the source file for all the preview in the docs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/z_.h"


/* Arr */
	
	typedef z__Vint2 Route; /* x = distance, y = time */
	z__Arr(Route) routes ;
	
	void createRoutes(void)
	{
		z__Arr_new(&routes, 8); // Initializing w/ 8 space.
		for (int i = 0; i <	12; i++) {
			z__Arr_push(&routes, (Route){
							.x = random()&127, .y = random()&63
						});
		}
	}

	Route getTotal(void)
	{
		Route total = {.x = 0, .y = 0};
		for (int i = 0; i < z__Arr_getLen(routes); i++) {
			z__Vector2_A(z__Arr_getVal(routes, i), total, + , &total);
		}
		return total;
	}
	
	void dojob(void)
	{
		createRoutes();
		printf("|   Routes    |\n"
			   "---------------\n"
			   "|Distance|Time|\n"
		);
		for(int i = 0; i < 12; i++) {
			printf("|%8d|%4d|\n"
					, z__Arr_getVal(routes, i).x
					, z__Arr_getVal(routes, i).y);
		}

		Route total = getTotal();
		printf("Total\n"\
			   "Distance:%d\n"\
			   "Time:%d\n", total.x, total.y);
	}



/* Linked List */

	z__Link(Integers, z__i32);


	
	z__Link(
		Jist,			// <-- Tag Name
		int,			// <-- Main Data Type
		z__float dt;	// <-- Optional Members Start
		z__i64 id       // There Can be More Than One!
	);
	

	struct Buffer {
		int member1;
		/* More Members!!! ... */
	};

	z__Link(Tabs, struct Buffer);


	/* Linked List Structure */
	z__Link(Mats, z__Matrix4, z__Vector2 pos);

	/* Creating a new handler */


	z__LList(Mats, int total) matrices = {
		.head = NULL,
		.tail = NULL,
		.cursor = NULL,
		.total = 0
	};



	/*       ^         ^
	 *	"Tag Name" "New Linked List"
	 */

	void t(){;


		z__Matrix4 mat4 = {
			{
				{1, 4, 6, 2},
				{5, 2, 5, 7},
				{1, 5, 4, 5}
			}
		};

		z__LList_new(&matrices, mat4);

		

		z__Matrix4 appr = {
			{
				{25, 55, 26, 66},
				{02, 07, 20, 82},
				{52, 07, 24, 62},
				{90, 66, 01, 61}
			}
		};


	
		/* Iterates twice towards next */
		z__LList_inext(&matrices, 2);

		
		/* Iterates thrice towards prev */
		z__LList_iprev(&matrices, 3);


		
		z__LList_setCursorHead(&matrices);

		z__LList_setCursorTail(&matrices);

		z__LList_setCursorNext(&matrices);

		z__LList_setCursorPrev(&matrices);



	
		
		z__LList_pushCursor_next(&matrices, appr);
		z__LList_pushCursor_prev(&matrices, appr);


	}
