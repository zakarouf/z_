/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** 
 * file: mpa.h
 * desc: Multi Precision Arithmatic
 * 
 * BigInt: ((2^63)*n) + m
 * Using Dynamic array of 64bit Uint to represent `n`, and carry to be `m`
 *
 */ 

#include "std/primitives.h"
#include "arr.h"

typedef struct {
	z__u64Arr degree;
	z__i64 msv;
} z__BigInt;

void z__BigInt_delete(z__BigInt *bi);
void z__BigInt_new(z__BigInt *bi);

#ifdef Z__IMPLEMENTATION

void z__BigInt_addi(z__BigInt *bi, z__i64 value)
{
	if(bi->msv >= 0) {
		z__i64 leftover = INT64_MAX - bi->msv;
		if(leftover >= value) { bi->msv += value; }
	} else {
		z__i64 leftover = INT64_MIN - bi->msv;
		if(leftover <= value) { bi->msv += value; }
	}
}

void z__BigInt_new(z__BigInt *bi)
{
	z__Arr_new(&bi->degree, 8);
	bi->msv = 0;
}

void z__BigInt_delete(z__BigInt *bi)
{
	z__Arr_delete(&bi->degree);
}

#endif

