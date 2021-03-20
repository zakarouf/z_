# Ztypes
A small library for defining type and such

# What it does?
It defines common data types, Array types, Vectors, Dynamic Type Arrays

# Generic Types

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
---
# Dyanmic Array Types

|Type|Description|
|---|---|
|`z__Arr(T)`| Type-safe, User generated Array, of type 'T'|
|`z__<type>Arr`| Dynamic Array for specified Type|
|`z__Dynt`| Dynamic Array for Unknown or Non-primitive Type|
---
# Fixed Length Arrays

|Type|Description|
|---|---|
|`z__FxArr`| Fixed length Array (minimal) |
|`z__SxArr`| Fixed length Array, Contained in a Struct with const len and lenUsed |
---
# Vector Types

## Struct
|Type|Description|
|---|---|
|`z__Vector(T)`| Creates User defined Vector Type |
|`z__Vector2`| 2D Vector {x, y} |
|`z__Vector3`| 3D Vector {x, y, z} |
|`z__Vector4`| 4D Vector {x, y, z, w} |
|`z__Vint2`| 2D Integer Vector {x, y} |
|`z__Vint3`| 3D Integer Vector {x, y, z} |
|`z__Vint4`| 4D Integer Vector {x, y, z, w} |

## Array
|Type|Description|
|---|---|
|`z__vec2`| 2D Vector {x, y} |
|`z__vec3`| 3D Vector {x, y, z} |
|`z__vec4`| 4D Vector {x, y, z, w} |
|`z__ivec2`| 2D Integer Vector {x, y} |
|`z__ivec3`| 3D Integer Vector {x, y, z} |
|`z__ivec4`| 4D Integer Vector {x, y, z, w} |


## Matrices

|Type|Description|
|---|---|
|`z__mat2`| 2x2 matrix |
|`z__mat3`| 3x3 matrix |
|`z__mat4`| 4x4 matrix |

---
# Dynamic Arrays
This Library Provides 2 types of Dynamic arrays
- Generic Type Array (int, float)
- Unknown Type Array (any struct or typedefs)

## Generic Type Array
Originally This library was meant to only provide 1 type of Arrays; Dynamic Unknown Type, which would work similarly to std::vector.
Generic Type was added later in order to replace the type checking hassle with array types which people will often use like i32 or f32 arrays which are essential even in small projects.

ztypes Provides Arr types for all int and float types
`z__<type>Arr` is the basic format for defining an Array, such as `z__i64Arr` means a singned 64bit integer Array.

`ztypes` Library also provides some funtions for Creating and Manupulating `Arr` types, NOTE the basic structure of types is same except for types names so macro functions are used in some cases.

### Functions

Create a initializes Array of <type> and of size <len> and Returns it.
```C
z__<type>Arr z__<type>Arr_create(z__u32 <len>);
```
```C
z__i8Arr i8_array = z__i8Arr_create(32);
```

Delete a `Arr` type 
```C
z__Arr_delete(arr);
```
```C
z__Arr_delete_(i8_array);
z__Arr_delete_(f32_array);
```

Push Value At top
*Reallocates the Array if No more space is Availiable*
```C
z__<type>Arr_push(<type>Arr \*array ,<type> value);
```
```C
z__i16Arr_push(array, 9);
```

Deletes the top Value
*Reallocates the Array if Unused space is are more than gross limit*
```C
z__<type>Arr_pop(array);
```
```C
z__u64_pop(array);
```

## Dynamic Unknown Type Array
A array which enables for quick initialization of array for non-standard types.
To initialize a Dynamic Unknown Type Array `z__Dynt` is used.

### Functions
>Create a initializes Array of <type> and of size <len> with a given Comment for the type and Returns it.
    
```C
z__Dynt_create(z__type type, z__u32 len, const char *comment, z__i32 commentLength);
```

```C
    typedef struct _objecttype
    {
        z__u8 info;
        z__u32 len
        z__Vector3 pos;
    }object;

    z__Dynt object_box = z__Dynt_create(z__typeof(object), 32, "Object:Box", -1);
```

>Delete a `Dynt` type and frees its comment if you dont want it be free set nameFree to False or 0.
```C
z__Dynt_delete(z__Dynt* arrt, z__bool nameFree);
```
```C
z__Dynt_delete(&object_box, true);
```

>Pushes Value At top
*Reallocates the Array if No more space is Availiable*
```C
z__Dynt_push( z__Dynt *arrt, void *val);
```
```C
z__Dynt_push( &object_box, (object){2, 1, (z__Vector3){0, 3 ,0}});
```

>Delete the top Value
*Reallocates the Array if Unused space is are more than gross limit*
```C
z__Dynt_pop( z__Dynt *arrt);
```

>Resizing array.
*Note: If array was larger then all values b/w oldsize and newsize is gone*
```C
z__Dynt_resize(object_box, 23);
```


```C
z__Dynt_makeCopy(const z__Dynt arrt);
```
>Creates a New copy arrt and returns it.
*NOTE: New Copy is not linked with the passed value so its safe to delete it*

