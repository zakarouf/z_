" Vim Syntax File
" Language: C, ztypes-Extention
" Author: Zakarouf

" This File is merely an extention for C syntax to be used for my self defined
" types. Do not use This as a standalone syntax file.
" Put it in your `after/syntax/` as `c.vim` folder or append these lines to your
" pre-exting syntax extention file


" BASIC START
syn keyword cType z__int z__float z__bool z__ptr z__byte
syn keyword cType z__iptr z__uptr z__umax z__imax
syn keyword cType z__size z__ptrdiff

syn keyword cType z__i8 z__i16 z__i32 z__i64
syn keyword cType z__i8_f z__i16_f z__i32_f z__i64_f

syn keyword cType z__u8 z__u16 z__u32 z__u64
syn keyword cType z__u8_f z__u16_f z__u32_f z__u64_f

syn keyword cType z__f32 z__f64

syn keyword cType z__Dynt z__Irrg z__voidArr z__byteArr
syn keyword cType z__i8Arr z__i16Arr z__i32Arr z__i64Arr
syn keyword cType z__u8Arr z__u16Arr z__u32Arr z__u64Arr
syn keyword cType z__ptrArr z__boolArr z__f32Arr z__f64Arr

syn keyword cType z__char z__String z__StringList z__StringListArr z__Str

" Types
syn keyword cType z__ivec2 z__ivec3 z__ivec4
syn keyword cType z__vec2 z__vec3 z__vec4
syn keyword cType z__mat2 z__mat3 z__mat4
syn keyword cType z__versor;

syn keyword cType z__Vector2 z__Vector3 z__Vector4 z__Versor
syn keyword cType z__Vint2 z__Vint3 z__Vint4

syn keyword cType z__Matrix2 z__Matrix3 z__Matrix4
syn keyword cType z__Mint2 z__Mint3 z__Mint4

syn keyword cStructure z__Vector z__Arr z__Martix z__VectorSt
syn keyword cStructure z__ArrFx z__ArrSx z__ArrSxDef z__ArrSxI z__ArrSxT
syn keyword cStructure z__Link z__LinkType z__LList

syn keyword cStructure z__Tuple z__TupleX z__Record z__RecordX record z__Enum z__EnumDef
syn keyword cStatement match slot unslot ifSlot emptyslot

syn keyword cStructure z__Result z__Option

syn keyword cType z__auto
syn keyword cOperator z__typeof z__sizeof z__typeID


"Mem

syn keyword cStatement z__autofree z__Arrfree

"OpenMP

syn keyword cStatement z__omp z__omp_parallel z__omp_for

"Pthread

"syn keyword cType z__pt_Thread z__pt_MetaData z__pt_UniqueData z__pt_Thread_Attr
"syn keyword cStructure z__pt_DataContext z__pt_DataContextType 
"Misc

syn keyword cStatement zpp__pragma

"syn match cFunction "\<[a-zA-Z_][a-zA-Z_0-9]*\>[^()]*)("me=e-2
"syn match cFunction "\<[a-zA-Z_][a-zA-Z_0-9]*\>\s*("me=e-1 
"hi cFunction gui=NONE guifg=#aff232

