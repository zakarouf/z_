# Ztypes
A small library for defining type and such

## What it does?
It defines common data types, Array types, Vectors, Dynamic Type Arrays

## Types

### Generic Types

|Type|Description|
|---|---|
|`z__i8`| signed 8bit integer |
|`z__i16`| signed 16bit integer |
|`z__i32`| signed 32bit integer |
|`z__i64`| signed 64bit integer |
|`z__u8`| unsigned 8bit integer |
|`z__u16`| unsigned 16bit integer |
|`z__u32`| unsigned 32bit integer |
|`z__u64`| unsigned 64bit integer |
|`z__int`| generic int system provides |
|`z__f32`| Single Precision Floating Point |
|`z__f64`| Double Precision Floating Point |
|`z__float`| Generic float system provides |
|`z__bool`| Bool Type |
|`z__ptr`| Void Pointer |

### Array Types

|Type|Description|
|---|---|
|`z__<type>Arr`| Dynamic Array for specified Type|
|`z__Dynt`| Dynamic Array for Unknown or Non-primitive Type|

### Vector Types

**Struct**
|Type|Description|
|---|---|
|`z__Vector2`| 2D Vector {x, y} |
|`z__Vector3`| 3D Vector {x, y, z} |
|`z__Vector4`| 4D Vector {x, y, z, w} |
|`z__Vint2`| 2D Integer Vector {x, y} |
|`z__Vint3`| 3D Integer Vector {x, y, z} |
|`z__Vint4`| 4D Integer Vector {x, y, z, w} |

**Array**
|Type|Description|
|---|---|
|`z__vec2`| 2D Vector {x, y} |
|`z__vec3`| 3D Vector {x, y, z} |
|`z__vec4`| 4D Vector {x, y, z, w} |
|`z__ivec2`| 2D Integer Vector {x, y} |
|`z__ivec3`| 3D Integer Vector {x, y, z} |
|`z__ivec4`| 4D Integer Vector {x, y, z, w} |


### Matrices

|Type|Description|
|---|---|
|`z__mat2`| 2x2 matrix |
|`z__mat3`| 3x3 matrix |
|`z__mat4`| 4x4 matrix |


### Arrays
This Library Provides 2 types of arrays
- Generic Type Array (int, float)
- Unknown Type Array (any struct or typedefs)

**Generic Type Array**
Originally This library was meant to only provide 1 type of Arrays; Dynamic Unknown Type, which would work similarly to std::vector.
Generic Type was added later in order to replace the type checking hassle with array types which people will often use like i32 or f32 arrays which are essential even in small projects.

`ztypes` Provides Arr types for all int and float types
`z__<type>Arr` is the basic format for defining an Array, such as `z__i64Arr` means a singned 64bit integer Array.

`ztypes` Library also provides some funtions for Creating and Manupulating `Arr` types, NOTE the basic structure of types is same except for types names so macro functions are used in some cases.

`z__<type>Arr z__<type>Arr_create(z__u32 <len>);`</ br>
    Creates a initializes Array of <type> and of size <len> and Returns it.
    USAGE: z__i8Arr i8_array = z__i8Arr_create(32);

`z__Arr_delete(arr);` </ br>
    Deletes a `Arr` type 
    USAGE: z__Arr_delete_(i8_array)
           z__Arr_delete_(f32_array)

`z__<type>Arr_push(<type>Arr \*array ,<type> value);`</ br>
    Pushes Value At top
    *Reallocates the Array if No more space is Availiable*
    USAGE: z__i16Arr_push(array, 9);

`z__<type>Arr_pop(array);`</ br>
    Deletes the top Value
    *Reallocates the Array if Unused space is are more than gross limit*
    USAGE: z__u64_pop(array);

**Dynamic Unknown Type Array**
A array which enables for quick initialization of array for non-standard types.
To initialize a Dynamic Unknown Type Array `z__Dynt` is used.

**Functions**
- ```z__Dynt_create(z__type type, z__u32 len, const char *comment, z__i32 commentLength);```
    Creates a initializes Array of <type> and of size <len> with a given Comment for the type and Returns it.
    USAGE: 
```
    typedef struct _objecttype
    {
        z__u8 info;
        z__u32 len
        z__Vector3 pos;
    }object;

    z__Dynt object_box = z__Dynt_create(z__typeof(object), 32, "Object:Box", -1);
```

- ```z__Dynt_delete(z__Dynt* arrt, z__bool nameFree);```
    Deletes a `Dynt` type and frees its comment if you dont want it be free set nameFree to False or 0.
    USAGE: z__Dynt_delete(&object_box, true);

- ```z__Dynt_push( z__Dynt *arrt, void *val);```
    Pushes Value At top
    *Reallocates the Array if No more space is Availiable*
    USAGE: z__Dynt_push( &object_box, (object){2, 1, (z__Vector3){0, 3 ,0}});

- ```z__Dynt_pop( z__Dynt *arrt);```
    Deletes the top Value
    *Reallocates the Array if Unused space is are more than gross limit*
    USAGE: z__Dynt_pop(&object_box);

- ```z__Dynt_resize(object_box, 23);```
    Resizes array.
    *Note: If array was larger then all values b/w oldsize and newsize is gone*
    USAGE: z__Dynt_resize(object_box, 70);

- ```z__Dynt_makeCopy(const z__Dynt arrt);```
    Creates a New copy arrt and returns it.
    *NOTE: New Copy is not linked with the passed value so its safe to delete it*

