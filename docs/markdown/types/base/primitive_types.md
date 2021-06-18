# Primitive Types And Basics

**`#include <z_/types/base.h>`**

`ztypes` includes type defination of primitive types (a basic wrapper around what standard library provides).

## Showcase

**Fixed Sized Types** : These Types will be of same size *always*.

|                           Type                             |Description|
|------------------------------------------------------------|-----------|
|<font color="#663333"> **z__u\<N\>** | An unsigned 8-bit, 16-bit, 32-bit, 64-bit Integer.|
|<font color="#663333"> **z__i\<N\>** | A signed 8-bit, 16-bit, 32-bit, 64-bit Integer.|
|<font color="#663333"> **z__f\<N\>** | 32-bit or 64-bit floating Number.|
|<font color="#663333"> **z__bool**   | Boolean               |
|<font color="#663333"> **z__byte**   | Same as 8-bit Integer.|

---
> \<N\> is the the bit-space of that type, i.e. z__u32 is a 32=bit integer. <br>
> For Integer They are: 8, 16, 32, 64 <br>
> For Floats They are: 32, 64

- Any Integer type suffixed with _f will inidicate its a _fast_ variant of that datatype. Example being `z__u32_f` or `z__i8_f`

---

There is also un-specified<br>
|||
|---|---|
|<font color="#663333"> **z__int**   | System Specific Integer Type |
|<font color="#663333"> **z__float** | System Specific Float Type   |


Some Other Miscellaneous Types
|||
|---|---|
| **z__ptr**     | System Specific Pointer Type |
| **z__imax**    | Max Integer width type |
| **z__umax**    | Max Integer width type (unsigned) |
| **z__iptr**    | Pointer for Ptr arithmatic        |
| **z__uptr**    | Pointer for Ptr arithmatic (unsigned) |
| **z__ptddiff** | For Result of pointer subtraction (difference) |
| **z__size**    | Result for `sizeof` or `z__sizeof` operator    |
> Due the Architecture Difference in the _CPUs_ the pointer size also changes; <br>
> On a 32-bit machine, a pointer is of a 32-bit in size and in 64-bit machine it is of 64-bit in size.


</font>

