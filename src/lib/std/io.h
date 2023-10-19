#ifndef ZAKAROUF_Z__STD_IO_H
#define ZAKAROUF_Z__STD_IO_H

#include "../types/primitives.h"
#include "../types/arr.h"
#include "../types/string.h"

typedef struct z__File z__File;
struct z__File {
    z__u8Arr buffer;
    z__u64 fd;   
    z__u16 flush_at;
    struct flags {
        z__u8 _read: 1
            , _append: 1
            , _write: 1;
    };
};

int z__File_open(z__File *file, z__CStr _path, const char *__restrict flag);
int z__File_close(z__File *file);
int z__File_flush(z__File *file);

int z__File_read(z__File *file, void *dest, z__size size);
int z__File_write(z__File *file, void const *data, z__size size);


#endif
