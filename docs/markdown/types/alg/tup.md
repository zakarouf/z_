# Tuples

Tuples are structures holding values of different types, where each of its members are not named or specified by the user.

To Create a basic anonymous Tuple use:
```c
z__TupleX(T1, T2, ...) <variable>;
```
> Here we create a anonymous structure where each argument is the type of their respective index.
Example:
```c
z__TupleX(int, int, int) color_rgb;
z__TupleX(char *, size_t) message;
```

We can also create Named Structure
```c
z__Tuple(
    Clr_rgb,    
    int, int, int
);
struct Clr_rgb color_rgb; 
```

#### Accessing Variables

Each value are index from `_0` to `_n`.

To access one
```c
z__TupleX(int, int, int) color_rgb;
color_rgb._0 = 23;  // First Member
color_rgb._1 = 54;  // Second Member
color_rgb._2 = 211; // Third Member
```

Or we can use `z__Tuple_get(tup, n)`
```c
return z__Tuple_get(color_rgb, 1); // Return the second element
```

#### Assignment

For quick assignment you can use the Accessing Variables method or we can use the `z__Tuple_assign(&tup, ...)` Macro
It'll automatically assign the values corresponding to the index.
```c
z__TupleX(int, int, int) color_rgb;
z__Tuple_assign(&color_rgb, 23, 54, 211);
```

#### Create References

`z__Tuple_toReference(tup, ...)` Creates refferences to a tuples's members.

```c
z__TupleX(int, int, int) color_rgb;
z__Tuple_toReference(color_rgb, r, g, b);
*r = 23;
*g = 54;
*b = 211;
```

If you want the skip a or multiple indexs use `()` in their place
```c
z__TupleX(int, int, int) color_rgb;
z__Tuple_toReference(color_rgb, r, (), b);
*r = 23;
*b = 211;
// g pointer is never created.
```

#### Create Member Prototypes

You can Declare Variables Resembling the exact type of a members in a tuple
```c
z__TupleX(time_t, char *, size_t) types_tmp;
z__Tuple_toVarProto(types_tmp,
        time,       // Type: time_t
        message,    // Type: char *
        length      // Type: size_t
);

// `()` can be use to skip a member.
z__Tuple_toVarProto(types_tmp, (), message2, size2);
```

---

Thats it!! You can also see other Algebraic Types below:
* [Records](./rec.md)
* [Sum Types](./enum.md)

