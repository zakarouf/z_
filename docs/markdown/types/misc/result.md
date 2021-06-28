# Result Type

**`#include <z_/types/result>`**

Result Type provides a definitive way handle recoverable errors.

---

A Result Type is created with the prototype shown below:
```c
z__Result(Tok, T, E);
```
`Tok` is the token name that does not pollute namespaces. `T` and `E` are generic type parameters; With `T` representing the type value that is to be returned on success and `E` is the Error type to be returned. 

`z__ResultType(Tok)` is used to retrieve the structure of the Result Type. `z__Ok(Tok, val)` and `z__Err(Tok, val)` is used for returning the result on success or failure of type `T` and `E` respectively.

##### Example
```c
z__Result(Mem, void *, char *);
z__ResultType(Mem) safe_malloc(size_t size)
{
    void *_tmp = malloc(size);
    if(_tmp) return z__Ok(Mem, _tmp);
    return z__Err(Mem, "Memory Allocation Failed");
}
```

#### Evaluating Errors

For evaluation `match` and `IfSlot` statement is used similar to `z__Enum`.

```c
z__Result(Mem, void *, char *);
z__ResultType(Mem) safe_malloc(size_t size)
{
    void *_tmp = malloc(size);
    if(_tmp) return z__Ok(Mem, _tmp);
    return z__Err(Mem, "Memory Allocation Failed");
}

int main(void)
{
    z__auto data = safe_malloc(1000);
    void *mem;
    ifSlot(data, Err, why) print("%s", *why) unslot;

    z__auto data_2 = safe_malloc(102424);
    void *mem_2;
    match(data_2) {
        slot(Ok, gt) mem = *gt; unslot;
        slot(Err, why) printf("%s", *why); unslot;
    }
}
```

#### Set Default value

Using `z__Result_unwrap_or(R_T, def_val)` you unwrap, evaluate and choose between the retrieve and default value.

```c
z__Result(Num, int, char *);
z__ResultType(Num) get_number(void)
{
    if (0) return z__Ok(10);
    z__Err("No Number for you");
}

int main(void)
{
    int a = z__Result_unwrap_or(get_number(), 25);
    printf("%d\n", a); // Will print 25.
}
```

---

* [Go Back](./index.md)
* [Homepage](../../index.md)
