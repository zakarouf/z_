# z_
A Small System Module.

## What it does?
### Memory Tracker
A simple memory tracker for debug purpose. **NOT GC (Garbage Collector)**.

### Types
It provides common data types, Array types, Vectors, Dynamic Arrays etc.

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

### Multi Threading?
Whilst Still in Process & Totally Optional. A multi thread implementation around pthread and OpenMP is on the to-do list.

## Getting Started, Only Types

Inorder to integrated ztypes in your project
```sh
git clone --depth=1 git://github.com/zakarouf/typed.git
cp -R z_/src/types /to/your/project/source/types
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
