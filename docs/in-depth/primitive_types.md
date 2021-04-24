# Primitive Types And Basics
`ztypes` includes type defination of primitive types (a basic wrapper around what standard library provides).

## Run-Down
**Fixed Sized Types** : These Types will be of same size *always*.

|                           Type                             |Description|
|------------------------------------------------------------|-----------|
|<font color="#663333"> _**z__u< 8 \| 16 \| 32 \| 64 >**_    | An unsigned 8-bit, 16-bit, 32-bit, 64-bit Integer.|
|<font color="#663333"> _**z__i< 8 \| 16 \| 32 \| 64 >**_    | A signed 8-bit, 16-bit, 32-bit, 64-bit Integer.|
|<font color="#663333"> _**z__f< 32 \| 64 >**_               | 32-bit or 64-bit floating Number.|
|<font color="#663333"> _**z__bool**_                        | Boolean |
|<font color="#663333"> _**z__byte**_                        | Same as 8-bit Integer.|

---

>Any Integer type suffixed with _f will inidicate its a _fast_ variant of that datatype. <br>
Example being `z__u32_f` or `z__i8_f`

---
There is also..<br>
|||
|---|---|
|<font color="#663333"> _**z__int**_   | System Specific Integer Type |
|<font color="#663333"> _**z__float**_ | System Specific Float Type   |
|<font color="#663333"> _**z__ptr**_   | System Specific Pointer Type |
> Due the Architecture of the _CPUs_ the pointer size also changes; <br>
> On a 32-bit machine, a pointer is of a 32-bit in size and in 64-bit machine it is of 64-bit in size.


















</font>
