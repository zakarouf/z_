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

- [ansifmt.h](./src/lib/ansifmt.h): 
- [argparse.h](./src/lib/argparse.h): 
- [arr.h](./src/lib/arr.h): Implementation of Generic Dyanmic Array
- [arrfree.h](./src/lib/arrfree.h)
- [arrllist.h](./src/lib/arrllist.h): Implementation of Array Allocated Generic Linked List
- [assert.h](./src/lib/assert.h)
- [atomic.h](./src/lib/atomic.h)
- [autotype.h](./src/lib/autotype.h)
- [bitf.h](./src/lib/bitf.h)
- [bnf.h](./src/lib/bnf.h)
- [bytes.h](./src/lib/bytes.h): Implementation of byte array
- [cglm.h](./src/lib/cglm.h)
- [contof.h](./src/lib/contof.h): Container of macro
- [curl.h](./src/lib/curl.h): Wrapper around curl
- [dynt.h](./src/lib/dynt.h): Implementation of Opaque Array
- [enum.h](./src/lib/enum.h): Implementation of [Sum Type](https://en.wikipedia.org/wiki/Tagged_union)
- [fio.h](./src/lib/fio.h)
- [fnptr.h](./src/lib/fnptr.h)
- [forrange.h](./src/lib/forrange.h)
- [gmath.h](./src/lib/gmath.h)
- [hashset.h](./src/lib/hashset.h): Implementation of Generic Hash List/Map/Table
- [hashstr.h](./src/lib/hashstr.h): Implementation of String Key, Hash Set. 
- [htmlfmt.h](./src/lib/htmlfmt.h): 
- [irrg.h](./src/lib/irrg.h): Implementation of Opaque List
- [lexer.h](./src/lib/lexer.h)
- [llist.h](./src/lib/llist.h): Implementation of [Linked List](https://en.wikipedia.org/wiki/Linked_list)
- [map.h](./src/lib/map.h)
- [map2d.h](./src/lib/map2d.h)
- [map3d.h](./src/lib/map3d.h)
- [mapch.h](./src/lib/mapch.h)
- [matrix.h](./src/lib/matrix.h)
- [obj.h](./src/lib/obj.h)
- [omp.h](./src/lib/omp.h)
- [option.h](./src/lib/option.h): Implementation of Option Sum Type
- [offsetof.h](./src/lib/offsetof.h)
- [pairarr.h](./src/lib/pairarr.h): Implementation of Pair Array
- [print.h](./src/lib/print.h)
- [record.h](./src/lib/record.h): Struct Gen that can be used by c macros, [Record](https://en.wikipedia.org/wiki/Record_(computer_science)).
- [result.h](./src/lib/result.h)
- [return.h](./src/lib/return.h)
- [sys.h](./src/lib/sys.h)
- [subp.h](./src/lib/subp.h)
- [soarr.h](./src/lib/soarr.h): Implementation of Struct of Arrays
- [strto.h](./src/lib/strto.h)
- [serial.h](./src/lib/serial.h)
- [string.h](./src/lib/string.h): Implementation of Byte String (ASCII).
- [string8.h](./src/lib/string8.h): Implementation of utf-8 compactible String.
- [structarr.h](./src/lib/structarr.h)
- [tui.h](./src/lib/tui.h)
- [time.h](./src/lib/time.h)
- [test.h](./src/lib/test.h)
- [tree.h](./src/lib/tree.h)
- [type.h](./src/lib/type.h)
- [tuple.h](./src/lib/tuple.h): Implementation of [Tuple Type](https://en.wikipedia.org/wiki/Tuple).
- [termio.h](./src/lib/termio.h)
- [thread.h](./src/lib/thread.h)
- [typeid.h](./src/lib/typeid.h)
- [typeof.h](./src/lib/typeof.h)
- [tgprint.h](./src/lib/tgprint.h)
- [typegen.h](./src/lib/typegen.h)
- [utf8.h](./src/lib/utf8.h)
- [u8arr.h](./src/lib/u8arr.h)
- [utils.h](./src/lib/utils.h)
- [vector.h](./src/lib/vector.h)

### Pre-Processing Modules (PreP)
Meta-programming using C-preprocessor. [Explore Source](./src/lib/prep)

- [prep/args.h](./src/lib/prep/args.h)
- [prep/base.h](./src/lib/prep/base.h)
- [prep/call.h](./src/lib/prep/call.h)
- [prep/eval.h](./src/lib/prep/eval.h)
- [prep/loop.h](./src/lib/prep/loop.h)
- [prep/map.h](./src/lib/prep/map.h)
- [prep/num.h](./src/lib/prep/num.h)

- [prep/comp/eval.h](./src/lib/prep/comp/eval.h)

- [prep/gen/args/applyfxy.h](./src/lib/prep/gen/args/applyfxy.h)
- [prep/gen/args/get.h](./src/lib/prep/gen/args/get.h)
- [prep/gen/args/getupto.h](./src/lib/prep/gen/args/getupto.h)
- [prep/gen/args/skip.h](./src/lib/prep/gen/args/skip.h)
- [prep/gen/args/var.h](./src/lib/prep/gen/args/var.h)

- [prep/gen/num/dec_u8.h](./src/lib/prep/gen/num/dec_u8.h)
- [prep/gen/num/dec_n1024.h](./src/lib/prep/gen/num/dec_n1024.h)
- [prep/gen/num/dec_n2048.h](./src/lib/prep/gen/num/dec_n2048.h)
- [prep/gen/num/inc_u8.h](./src/lib/prep/gen/num/inc_u8.h)
- [prep/gen/num/inc_n1024.h](./src/lib/prep/gen/num/inc_n1024.h)
- [prep/gen/num/inc_n2048.h](./src/lib/prep/gen/num/inc_n2048.h.h)

- [prep/nm/assert.h](./src/lib/prep/nm/assert.h)
- [prep/nm/cond.h](./src/lib/prep/nm/cond.h)
- [prep/nm/ident.h](./src/lib/prep/nm/ident.h)
- [prep/nm/pragma.h](./src/lib/prep/nm/pragma.h)
- [prep/nm/string.h](./src/lib/prep/nm/string.h)

### Prelude
Stuff that is probably needed everywhere.

- [std/alloc.h](./src/lib/std/alloc.h)
- [std/arch.h](./src/lib/std/arch.h)
- [std/io.h](./src/lib/std/io.h)
- [std/mem.h](./src/lib/std/mem.h)
- [std/primitives.h](./src/lib/std/primitives.h)

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

Will result a library libz_.a created in the `./build/lib` and headers at `./build/include` as `z_` directory. <br>

Copy the `z_` folder onto your `include` directory. And copy the `libz_.a` to the `lib` directory and link it against the executable and we are good to go.

```c
#include <z_/z_.h>
```

#### Method 2: Global Installation

Run the `build.sh` script, with the following parameters <br>
```sh
sh build.sh install lib
```
By Default, the path for Headers is `usr/local/include/z_` and for library it is `libz_.a`, you can change it by editing the
`build.sh` file itself, `LIB_DIR` and `INCLUDE_DIR` to be specfic.

### Config
Inside the source directory `config_{MODULE}.h` that can be modified by the user in-order to change the behaviour, include, exclude the fuctionality of that sub-library.
> {MODULE} is the name of the Module i.e. config_imp.h, config_prep.h etc.

Such as inside of `src/lib/_config_types.h`
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
#include <z_/types/llist.h>
```
Now this will work as it should.

### Adding Syntax Highlighting (Vim & NeoVim)

Additional syntax Highlighting for types and such are include in the extra/c.vim.

To add it into your project, either copy the contents of the `c.vim` file or put
`c.vim` into your `after/syntax` folder, such as `~/.config/vim/after/syntax/` directory.
This will load on top of your syntax highlighting for every .c file.

## Documentation

* [Documentation](./docs/markdown/index.md)
* [Overview](./docs/overview.md)

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
