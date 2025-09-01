<div align="center">
  <img src="docs/imgs/ztypes_preview0.png" width="400"/>
  <h1>z_</h1>

  Core Language Module with datatypes, memory tracker, and _more_.
</div>

## About 

This library provides Core Functionality built upon the C language. Inspired and taken from Modern Languages such as Python, Rust etc.

* **Memory Management:** Allocators, Memory Debugger.
* **Types & Data Structures:** Clean Systematic Data types and Structures with feature-full fuctionality.
* **Meta-Programming:** An absolute abuse of C-preprocessor.
* **Utilities:** Mini Libraries and modules for extendend fucntionality (e.g. TUI) and wrappers (e.g. curl, cglm)

## Sub-Modules
List of sub-modules of provided by the library.

|            Sub-module             |                         Description |
|:----------------------------------|:------------------------------------|
| **Data Types** |                                                        |
|[arr.h](./src/lib/arr.h)           | Implementation of Generic Dyanmic Array  |
|[arrfree.h](./src/lib/arrfree.h)   | Implementation of auto free for Dyanmic array type |
|[arrllist.h](./src/lib/arrllist.h) | Implementation of Array Allocated Generic Linked List |
|[autotype.h](./src/lib/autotype.h) | Autotype alias.                                       |
|[atomic.h](./src/lib/atomic.h)     | Custom atomic wrapper.                                |
|[bytes.h](./src/lib/bytes.h)       | Implementation of byte array                          |
|[dynt.h](./src/lib/dynt.h)         | Implementation of Opaque Array                        |
|[enum.h](./src/lib/enum.h)         | Implementation of [Sum Type](https://en.wikipedia.org/wiki/Tagged_union)|
|[fnptr.h](./src/lib/fnptr.h)       | Function pointer macro                                |
|[hashset.h](./src/lib/hashset.h)   | Implementation of Generic Hash List/Map/Table         |
|[hashstr.h](./src/lib/hashstr.h)   | Implementation of String Key, Hash Set.               |
|[irrg.h](./src/lib/irrg.h)         | Implementation of Opaque List                         |
|[map.h](./src/lib/map.h)           | Multi-layer tilemap.                    |
|[map2d.h](./src/lib/map2d.h)       | Single-layer tilemap.                   |
|[map3d.h](./src/lib/map3d.h)       | 3-Dimentional tilemap.                  |
|[mapch.h](./src/lib/mapch.h)       | Multi Chunk 3D tilemap                  |
|[matrix.h](./src/lib/matrix.h)     | Matrix Type                             |
|[llist.h](./src/lib/llist.h)       | Implementation of [Linked List](https://en.wikipedia.org/wiki/Linked_list)|
|[obj.h](./src/lib/obj.h)           | Closure & V-Tables                      |
|[option.h](./src/lib/option.h)     | Implementation of Option Sum Type       |
|[pairarr.h](./src/lib/pairarr.h)   | Implementation of Pair Array            |
|[record.h](./src/lib/record.h)     | Struct Gen that can be used by c macros, [Record](https://en.wikipedia.org/wiki/Record_(computer_science)).|
|[result.h](./src/lib/result.h)     | Result Type                                       |
|[return.h](./src/lib/return.h)     | Function return definitions                       |
|[soarr.h](./src/lib/soarr.h)       | Implementation of Struct of Arrays                |
|[string.h](./src/lib/string.h)     | Implementation of Byte String (ASCII).            |
|[string8.h](./src/lib/string8.h)   | Implementation of utf-8 compactible String.       |
|[tree.h](./src/lib/tree.h)         | [m-ary tree](https://en.wikipedia.org/wiki/M-ary_tree) Implentation   |
|[tuple.h](./src/lib/tuple.h)       | Implementation of [Tuple Type](https://en.wikipedia.org/wiki/Tuple).  |
|[u8arr.h](./src/lib/u8arr.h)       | u8 array                              |
|[vector.h](./src/lib/vector.h)     | Vector Type                           |
| **RNG** ||
|[random.h](./src/lib/random.h)     | PRNG & Hash Functions                 |
| **Processing**||
|[omp.h](./src/lib/omp.h)           | OpenMP wrapper                        |
|[subp.h](./src/lib/subp.h)         | Spawing a sub-process/child process   |
|[thread.h](./src/lib/thread.h)     | Thread Wrapper around pthread         |
| **File IO** ||
|[fio.h](./src/lib/fio.h)           | File IO                               |
| **Terminal IO** ||
|[ansifmt.h](./src/lib/ansifmt.h)   | ANSI Terminal string format. |
|[print.h](./src/lib/print.h)       | Print Implentation                      |
|[tui.h](./src/lib/tui.h)           | Terminal based UI, lightweight alternative to ncurses.                |
|[termio.h](./src/lib/termio.h)     | Terminal io functions                 |
|[tgprint.h](./src/lib/tgprint.h)   | Type Generic Print                    |
| **Web & Networking** ||
|[curl.h](./src/lib/curl.h)         | Wrapper around curl                   |
|[htmlfmt.h](./src/lib/htmlfmt.h)   | Format Macro for html                 |
| **System** ||
|[sys.h](./src/lib/sys.h)           | Functions for comunicating with system. |
|[time.h](./src/lib/time.h)         | Time based functionality                |
| **Utilities**||
|[bnf.h](./src/lib/bnf.h)           | Context free grammer notation [Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)    |
|[bitf.h](./src/lib/bitf.h)         | Macros for bit field manupilation       |
|[cglm.h](./src/lib/cglm.h)         | Wrapper for cglm                        |
|[contof.h](./src/lib/contof.h)     | Container of macro                      |
|[utf8.h](./src/lib/utf8.h)         | utf-8 functions                         |
|[utils.h](./src/lib/utils.h)       | Utility macro and functions             |
|[lexer.h](./src/lib/lexer.h)       | Generic Lexer                           |
|[offsetof.h](./src/lib/offsetof.h) | Custom Offset macro.                    |
|[strto.h](./src/lib/strto.h)       | Do a type generic sscanf                |
|[serial.h](./src/lib/serial.h)     | Serializer                              |
| **Design** ||
|[argparse.h](./src/lib/argparse.h) | Parse list of arguments of a program.                                                                       |
|[assert.h](./src/lib/assert.h)     | Custom assert implementation.                                                                               |
|[forrange.h](./src/lib/forrange.h) | For-range for different data types                                                                          |
|[gmath.h](./src/lib/gmath.h)       | Math functions for vectors and matrix                                                                       |
|[test.h](./src/lib/test.h)         | Test Suite Impletation                                                |
|[type.h](./src/lib/type.h)         | Define a Type Set                                                     |
|[typeid.h](./src/lib/typeid.h)     | List of Type-ids generated from `typegen.h`   |
|[typeof.h](./src/lib/typeof.h)     | `typeof` macro                                |
|[typegen.h](./src/lib/typegen.h)   | Macro for generating type info                |

### Pre-Processing Modules (PreP)
Meta-programming using C-preprocessor. [Explore Source](./src/lib/prep)

|             Sub-Module            |                         Description |
|:----------------------------------|:------------------------------------|
|[prep/args.h](./src/lib/prep/args.h)| Macro for passed-in arguments.|
|[prep/base.h](./src/lib/prep/base.h)| Basic Utility Macros|
|[prep/call.h](./src/lib/prep/call.h)| Function Call Wrapper|
|[prep/eval.h](./src/lib/prep/eval.h)| Eval Macro|
|[prep/loop.h](./src/lib/prep/loop.h)| Macro for compile-time loop|
|[prep/map.h](./src/lib/prep/map.h)| Map Macro|
|[prep/num.h](./src/lib/prep/num.h)| Macro for compile time small number arithmatic and comparism|
|[prep/nm/assert.h](./src/lib/prep/nm/assert.h)| Assert Constructors|
|[prep/nm/cond.h](./src/lib/prep/nm/cond.h)    | Condtional Statement, `doif` Constructors.|
|[prep/nm/ident.h](./src/lib/prep/nm/ident.h)  | Temporary Identifier Name Generator |
|[prep/nm/pragma.h](./src/lib/prep/nm/pragma.h)| Inline Compiler Pragma |
|[prep/nm/string.h](./src/lib/prep/nm/string.h)| Meta-String Functions |

Helper function for preprocessor macros, not used directly

| Name | Description |
|:-----|:-------------|
|[prep/comp/eval.h](./src/lib/prep/comp/eval.h) | Token Exaustor |
|[prep/gen/args/applyfxy.h](./src/lib/prep/gen/args/applyfxy.h) | Dual parameter functor |
|[prep/gen/args/get.h](./src/lib/prep/gen/args/get.h) | Parameter fetch |
|[prep/gen/args/getupto.h](./src/lib/prep/gen/args/getupto.h) | Parameter List fetch |
|[prep/gen/args/skip.h](./src/lib/prep/gen/args/skip.h) | Parameter Ignore |
|[prep/gen/args/var.h](./src/lib/prep/gen/args/var.h) | Parameter Vardic Count |
|[prep/gen/num/dec_u8.h](./src/lib/prep/gen/num/dec_u8.h) | |
|[prep/gen/num/dec_n1024.h](./src/lib/prep/gen/num/dec_n1024.h) | |
|[prep/gen/num/dec_n2048.h](./src/lib/prep/gen/num/dec_n2048.h) | |
|[prep/gen/num/inc_u8.h](./src/lib/prep/gen/num/inc_u8.h) | |
|[prep/gen/num/inc_n1024.h](./src/lib/prep/gen/num/inc_n1024.h) | |
|[prep/gen/num/inc_n2048.h](./src/lib/prep/gen/num/inc_n2048.h.h) | |


### Prelude
Stuff that is probably needed everywhere.


|                  Sub-Module                  |                         Description |
|:---------------------------------------------|:------------------------------------|
|[std/alloc.h](./src/lib/std/alloc.h)| Allocator |
|[std/arch.h](./src/lib/std/arch.h)| Macro for defining Architecture  |
|[std/io.h](./src/lib/std/io.h)| IO Functions |
|[std/mem.h](./src/lib/std/mem.h)| Memory Function |
|[std/primitives.h](./src/lib/std/primitives.h)| Primitives |


## Getting Started
`z_` is made with modularity in mind so many parts of it are as self-isolated as they can,
it doesn't even include standard library except `stddef.h`, `stdint.h` and `stdbool.h` for type
declaration **but** they still require the bare minimum `base` for to be working properly such
as, `z_/arr.h` can be included in itself but it still require `base.h` of `types`
for `z__u32` and `mem.h` for memory allocation definitions.

Therefore, You need to explicitly include the `<stdlib.h>`, `<string.h>`.

### Installing

#### Method 1: Local Integration

Inorder to integrated `z_` in your project only
```sh
git clone --depth=1 git://github.com/zakarouf/z_.git
sh build.sh lib
```
Will result headers at `./build/include` as `z_` directory. <br>
Copy the `z_` folder onto your `include` directory and we are good to go.

```c
#include <z_/z_.h>
```

#### Method 2: Global Installation

Run the `build.sh` script, with the following parameters <br>
```sh
sh build.sh install lib
```
By Default, the path for Headers is `usr/local/include/z_`, you can change it by editing the
`build.sh` file itself, `INCLUDE_DIR` to be specfic.

### Usage
`z_` is now uses stb-style header impletation macro without compiling a `.a` library to link to.
Define `Z__IMPLEMENTATION` in any one of the source file before including the header.
I would recommended creating a seperate empty source file with all the impletation defined.
```c
#define Z__IMPLEMENTATION
#include <z_/time.h>
```
> [Overview](./docs/overview.md) on the library

### Adding Syntax Highlighting (Vim & NeoVim)
Additional syntax Highlighting for types and such are include in the extra/c.vim.
To add it into your project, either copy the contents of the `c.vim` file or put
`c.vim` into your `after/syntax` folder, such as `~/.config/vim/after/syntax/` directory.
This will load on top of your syntax highlighting for every .c file.


## FAQs
### Why did I create this library? || History behind z_.
`z_` had a humble beginning as a single header for defining primitive types in [ztorg](https://github.com/zakarouf/ztorg) project.<br>
Later on I added more quality of life stuff such as Type-Generic Dyanmic Arrays etc. It was then I decided to move its development to a separate repo with more than just a "Data Type Library". I wanted to created a core, standard-library that I can just use anywhere as a starting point.

### Os & Compiler Support?
Linux and MacOS is fully supported while, with Windows your mileage might vary. <br>
As for Compiler GCC or Clang is recommended.

### Why heavy use of macros?
Bloat. Creating such library that I can use anywhere, I wanted to have as less bloated binary wise as posible, while also having to combat the non-type generic nature of the C language. <br>
If by any case, I dont want use a bare macro. I would wrap it up inside of a function.

```c
#define my_macro_function(a, b) { ... }

void my_function(int a, int b)
{
    my_macro_function(a, b);
}
```

### Who is this for?
Me. Or you if you stumble upon my stuff and found it cool. But as of writing, I created this for myself. This repo is so I can easily maintain and access the code and or share it with my friends. **I am not a good Programmer by a long shot**, I just like when my computer goes beep-boop.

## Credit & References
It takes many features from other libraries and projects. Whilst also some Reffrences and books.

### Types
#### Sum Types :: z__Enum
[Hirrolot](https://github.com/Hirrolot)'s [Datatype99](https://github.com/Hirrolot/datatype99). For my own implementation of Sum Types. The actual impletation is dis-similar to them. My implementation of [z__Enum](./src/types/enum.h) is no where near as elegant as Datatype99.

#### Misc
[Awesome C Preprocessor](https://github.com/Hirrolot/awesome-c-preprocessor) Helped to study on the C's magical Preprocessor.

## Previews & Example
<div align="center">
  <b> Sum of an Integer Array </b>
  <img src="docs/imgs/example/example_2.png">
</div>

<div align="center">
  <b> Intializing an Array of Functions in a single line </b>
  <img src="docs/imgs/example/fnptr_arr.png">
</div>

<div align="center">
  <b> Sum of Binary tree using Enum </b>
  <img src="docs/imgs/example/enum_binary_tree.png">
</div>

<div align="center">
  <b> Web Event with Enums </b>
  <img src="docs/imgs/example/enum_webevent.png">
</div>

<div align="center">
  <b> Fill Up an array of Vector2 with OpenMP </b>
  <img src="docs/imgs/example/ex3_omp_arr_fill.gif">
</div>

<div align="center">
  <b>Creating a Map with Pthread</b>
  <img src="docs/imgs/example/pt_pre_900px.gif">
</div>


---

## See Also

* [Awesome C Preprocessor](https://github.com/Hirrolot/awesome-c-preprocessor)
* [Generic-Print](https://github.com/exebook/generic-print)
* [P99](https://gitlab.inria.fr/gustedt/p99)
* [Cloak](https://github.com/pfultz2/Cloak)
* [Metatlang99](https://github.com/Hirrolot/metalang99)
* [Datatype99](https://github.com/Hirrolot/datatype99)

---

## Ending Note

This library is not perfect and I know there are many others like it, but this one is mine <3.

---
