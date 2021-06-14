# Records

Create a Record using `z__Record(...)`
```c
z__Record(
    <Name>,
   (<typename>, <member-1>, <member-2> .. <member-n>),
    ...
) <variable>;
```

* `Name` is the new datatype. Followed by their fields.
* Each field is enclosed inside a parentheses.
* First Argument is reserved for the `typename`, following which are its member of that `type`.

Example:
```c
z__Record(
    Map2D,
    (int, height, width),
    (char *, data)
);

struct Map2D map;
```

Creating a Anonymous Record
```c
// This time no Name Required.
z__RecordX(
    (int, height, width),
    (char *, data)
) map;
```

#### Creating Bit-Fields

Records has built-in support for generating bit-fields.
```c
z__RecordX(
    (int, id),
    (char, (1, // <= Specify how many bits each field has access to
            attr_is_toxic,
            attr_is_liquid,
            attr_is_invisible))
) TileData;
```

The above code generates a structure with four members `(id, attr_is_toxic, attr_is_liquid, attr_is_invisible)`.
Performing a `sizeof` on TileData will yield `5` bytes. 
- `4` bytes for `id`.
- `1` bytes for `(attr_is_toxic, attr_is_liquid, attr_is_invisible)`
- `(attr_is_toxic, attr_is_liquid, attr_is_invisible)` Has access to each bit of a `char` which is of 8 bytes.


#### Nested Records

Records Can be nested; Declare a record inside a record. And also with Tuples too!!
```c
z__Record(
    Player,
    (z__RecordX((float, x, y)), pos),
    (z__Tuple(float, float), HP, MP, AP )
);
```

#### Accessing Member

Accessing a Record Member is same as struct
```c
Player player1; // Using The record from previous example
player1.pos.x = 10.0f;
```

#### Assignment

Assignment can be done in a bulk using `z__Record_assign`
```c
z__RecordX(
    (int, height, width),
    (char *, data)
) map;

z__Record_assign(&map,
    (height, 10),
    (width, 10),
    (data, calloc(sizeof(char), map.height * map.width)));
```

#### Create References

Similar to Tuples Reffrences can be created using `z__Record_toReference`
```c
z__Record_toReference(&map,(height, h), (width, w));
printf("%d %d", *h, *w);
```

---

Move on to:
* [Sum Types](./enum.h)
* [Tuples](./tup.md)

