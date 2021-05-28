<div align="center">
  <img src="docs/imgs/ztypes_preview0.png" width="400"/>
  <h1>z_</h1>

  Core Language Module with datatypes, memory tracker, and _more_.
</div>

## About 

This library provides Core Functionality built upon the C language for the C language. Inspired and taken from Modern Languages such as Python, Rust etc. Sub-divided into Five major portions.

1. Memory Tracker
2. Type
3. Pre-Processing/Meta-Programming.
4. Multi-Threading
5. Standard Functions

### Memory Tracker

A simple memory tracker for debug purpose. **NOT GC (Garbage Collector)**.

* A wrapper around malloc, calloc, realloc, free. z__MALLOC, z__CALLOC, z__REALLOC, z__FREE.
* Logging memory allocation and de-allocation that can output in any file-stream including stdout.
* Evaluation of Total allocation and free, helps to combat memory leaks and such


### Types (types)

Types to allow more stable/systamatic programming procedure, no more impletate this basic functionaity 10 different ways in 10 different programs.

- [Primitive Types](https://en.wikipedia.org/wiki/Primitive_data_type)
- [Algebraic data type](https://en.wikipedia.org/wiki/Algebraic_data_type)
  - [Tuples](https://en.wikipedia.org/wiki/Tuple)
  - [Sum Types](https://en.wikipedia.org/wiki/Tagged_union)
- [String](https://en.wikipedia.org/wiki/String_(computer_science))
- [String List]()
- [String List Array]()
- [Arrays](https://en.wikipedia.org/wiki/Array_data_structure)
  - [Dyanmic Array Types](https://en.wikipedia.org/wiki/Dynamic_array)
    - [Generic](https://en.wikipedia.org/wiki/Generic_programming)
    - [Void Type](https://en.wikipedia.org/wiki/Void_type)
    - [Void Objects](./docs/in-depth/Irrg.md)
  - [Fixed Length Arrays]()
    - [Using Record]()
    - [Using Raw Array]()
- [Vector Types](https://en.wikipedia.org/wiki/Vector_(mathematics_and_physics))
  - [Using Record]()
  - [Using Raw Array]()
- [Matrices](https://en.wikipedia.org/wiki/Matrix_(mathematics))
  - [Using Record]()
  - [Using Raw Array]()
- [Linked List](https://en.wikipedia.org/wiki/Linked_list)

#### Resources

* [Documentation]()
* [Overview](docs/overview.md)

### Pre-Processing (PreP)

Meta-programming using C-preprocessor.

### Multi Threading (Proc)

Multi-Threading wrapper arround both OpenMP and Pthread with C11 `<threads.h>` considered for the future.

The Development has started with OpenMP.   <br>
Pthreads impletation has also started with its [base](src/proc/pt_base.h).

### Standard Functions (IMPs)

Lastly `z_` Also Provides Basic day-to-day set of functions revolving around Time, File IO, System, Logging and many more.


## Getting Started
`z_` is made with modularity in mind so many parts of it are as self-isolated as they can,
it doesnt even include standard library except `stddef.h`, `stdint.h` and `stdbool.h` for type
declaration **but** they still require the bare minimum `base` for to be working properly such
as, `z_/types/types/arr.h` can be included in itself but it still require `base.h` of `types`
for `z__u32` and `mem.h` for memory allocation definations.

### Installing

#### Method 1: Local Integration

Inorder to integrated `z_` in your project only
```sh
git clone --depth=1 git://github.com/zakarouf/z_.git
sh make-lib.sh
```

Will result a library libzkcollection.a created in the `./build/lib` and headers at `./build/include` as `z_` directory. <br>

Copy the `z_` folder onto your `include` directory. And copy the `libzkcollection.a` to the `lib` directory and link it against the executable and we are good to go.

```c
#include <z_/z_.h>
```

#### Method 2: Global Installation

Run the `install.sh` script. <br>
```sh
sh install.sh
```

This will run the `make-lib.sh` script and move the headers and the library to their designated path in your system.<br>
By Default, the path for Headers is `usr/local/include/z_` and for library it is `libzkcollection.a`, you can change it by editing the
`install.sh` file itself, `LIB_DIR` and `INCLUDE_DIR` to be specfic.

### Config
Inside the source directory `config_{MODULE}.h` that can be modified by the user in-order to change the behaviour, include, exclude the fuctionality of that sub-library.
> {MODULE} is the name of the Module i.e. config_imp.h, config_prep.h etc.

Such as inside of `src/config_types.h`
```c
#define Z___TYPE_CONFIG__USE_TYPE_LINKEDLIST

```
This particular config tells to include the Linked List type and its functionaity at core; when 
`z_.h` is included, and if we comment out it
```c
//#define Z___TYPE_CONFIG__USE_TYPE_LINKEDLIST
```
![error1](docs/imgs/readme_gs_conf_error_1.png) <br>
> Will result in a error
This forces to you to include linked list type manually.
```c
#include "z_/types/types/llist.h"
```
Now this will work as it should.

### Adding Syntax Highlighting (Vim)
Additional syntax Highlighting for types and such are include in the extra/c.vim.

To add it into your project, either copy the contents of the `c.vim` file or put
`c.vim` into your `after/syntax` folder, such as `~/.config/vim/after/syntax/` directory.
This will load on top of your syntax highlighting for every .c file.

## Previews & Example

<div align="center">
  <b> Getting Sum Of an Integer Array </b>
  <img src="docs/imgs/example/example_2.png">
</div>

<div align="center">
  <b> Enums </b>
  <img src="docs/imgs/enums/enum_preview1_fn.png">
</div>

<div align="center">
  <b>Array of Functions</b>
  <img src="docs/imgs/example/fnptr_arr.png">
</div>

<div align="center">
  <b>Fill Up an array with OpenMP</b>
  <img src="docs/imgs/example/ex3_omp_arr_fill.gif">
</div>

<div align="center">
  <b>Creating a Map with Pthread</b>
  <img src="docs/imgs/example/pt_pre_900px.gif">
</div>


---

## Reffrences & Credit

* [Awesome C Preprocessor](https://github.com/Hirrolot/awesome-c-preprocessor)
* [Generic-Print](https://github.com/exebook/generic-print)
* [P99](https://gitlab.inria.fr/gustedt/p99)
* [Cloak](https://github.com/pfultz2/Cloak)
* [Metatlang99](https://github.com/Hirrolot/metalang99)
* [Datatype99](https://github.com/Hirrolot/datatype99)

---

## Ending Note

This library is not perfect and I know there are many others like it, but this one is mine.

---
