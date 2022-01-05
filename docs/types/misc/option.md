# Option Type

**`#include <z_/types/option>`**

Option Type types provides optional values for handling exceptions and such.

---

A Option Type is created with the prototype shown below:
```c
z__Option(Tok, T...);
```
`Tok` is the token name that does not pollute namespaces. `T...` is tuple/list of generic types.

`z__OptionType(Tok)` is used to retrieve the structure of the Option Type. `z__Some(Tok, val...)` and `z__None(Tok)`.

##### Example

---

* [Go Back](./index.md)
* [Homepage](../../index.md)m
