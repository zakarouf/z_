# Ztypes
A small library for defining type and such

## What it does?
It provides common data types, Array types, Vectors, Dynamic Arrays etc.
It Also Provides An memory manager (NOT GARBAGE COLLECTOR); to Track allocated memory.

- Primitive Types
- String
- StringLines
- StringLines Array
- Dyanmic Array Types
  - Generic
  - Unknown Type
  - Unknown Object
- Fixed Length Arrays
  - Struct
  - Bare
- Vector Types
  - Struct
  - Array
- Matrices
- Linked List

_[See Overview](docs/overview.md)_

## Getting Started

Inorder to integrated ztypes in your project
```sh
git clone --depth=1 git://github.com/zakarouf/typed.git
cp -R typed/src /to/your/project/source/typed
```
Then include the header by
```c
#include "typed/ztypes.h"
```
Make sure to include the source files (*.c) from *typed* in your build script

**OR**

We can Create A library to link your program with
In that case, do
```sh
./make-lib
```
Will result a static library libzkztypes.a being made in the parent directory.

---
## Ending Note
This library is not perfect and I know there are many others like it, but this one is mine.

---
