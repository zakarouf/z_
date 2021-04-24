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
							random()&127, random()&63
						});
		}
	}

	Route getTotal(void)
	{
		Route total = {0, 0};
		for (int i = 0; i < z__Arr_getLen(routes); i++) {
			z__Vector2_A(z__Arr_getVal(routes, i), total, + , total);
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
