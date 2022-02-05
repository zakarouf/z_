/**
 * z_ Example: hexdump
 * Prints out byte sequence of any file.
 * Flags:
 *  -f [FILENAME] -> Specify the file name/path. REQUIRED
 *  -w [WIDTH]    -> Specify how long the each line should be in bytes, default: 16
 */

#include <z_/types/arr.h>
#include <z_/types/string.h>
#include <z_/types/base_util.h>
#include <z_/imp/fio.h>
#include <z_/imp/argparse.h>

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct Config {
    z__size width;
    z__size from;
    z__String filename;
};

void print_hex_line(
      z__size const line
    , z__byte const *ori_bt
    , z__size size
    , z__size width)
{
    z__size i = line;
    z__size const len = z__util_min_unsafe(width+i, size);
    z__byte const *iter = ori_bt + i;

    printf("%010lx:", line);
    for (; i < len; i++, iter++) {
        printf(" %02hhx", *iter);
    }

    i = line;
    iter = ori_bt + i;
    fputs(" | ", stdout);
    for (; i < len; i++, iter++) {
        if(isprint(*iter)) {
            putchar(*iter);
        } else {
            putchar('.');
        }
    }
    putc('\n', stdout);
}

int main (int argc, char *argv[])
{
    struct Config config = {
        .width = 0x10
      , .filename = NULL
      , .from = 0
    };

    z__argp_start(argv, 1, argc) {
        z__argp_ifarg(&config.width, "-w");
        z__argp_ifarg(&config.from, "-s");
        z__argp_ifarg_custom("-f") {
            z__argp_next();
            config.filename = z__String_newFromStr(z__argp_get(), -1);
        }
    }

    if(config.width == 0) config.width = 0x10;
    if(config.filename.data == NULL) {
        perror("File name not specified, please use the " "-f" "flags to do so.");
        return 0;
    }

    z__byteArr filedata = {0};
    z__fio_Arr_newFromFile(&filedata, config.filename.data);

    if(filedata.data == NULL) {
        perror("FILE CANT BE LOAD");
        return 0;
    }

    printf("%s %ubytes\n", config.filename.data, filedata.lenUsed);

    z__size i = config.from;
    for (; i < filedata.lenUsed; i += config.width) {
        print_hex_line(i
            , filedata.data
            , filedata.lenUsed * sizeof(*filedata.data)
            , config.width);
    }
    
    z__Arr_delete(&filedata);
    z__String_delete(&config.filename);

    return 0;
}
