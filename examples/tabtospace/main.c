/**
 * z_ Example: tabtospace
 * Reads in a file, converts tabs to spaces.
 * Requies two argument:
 * [FILE] -> file name/path that will be read.
 * [FILE_OUT] -> file to written in.
 */

#include <stdio.h>
#include <stdlib.h>
#include <z_/types/string.h>
#include <z_/imp/fio.h>

int main(int argc, char const *argv[])
{
    if(argc < 2) {
        fprintf(stderr, "%s requires two arguments [FILE] [FILE_OUT]", argv[0]);
    }

    z__String str = z__String_newFromFile(argv[1]);
    if(str.data == NULL) {
        fprintf(stderr, "Cant Load File %s", argv[1]);
        goto _L_return_ERR;
    }

    z__String str_out = z__String_new(32);

    for (size_t i = 0; i < str.lenUsed; i++) {
        if(str.data[i] == '\t') {
            for (size_t i = 0; i < 4; i++) {
                z__String_pushChar(&str_out, ' ');
            }
        } else {
            z__String_pushChar(&str_out, str.data[i]);
        }
    }

    FILE *fp = fopen(argv[2], "w");
    if(fp == NULL) {
        fprintf(stderr, "Cant write to file %s\n", argv[2]);
        goto _L_return_ERR;
    }
    fwrite(str_out.data, sizeof(*str_out.data), str_out.lenUsed-1, fp);
    fclose(fp);

    z__String_delete(&str);
    z__String_delete(&str_out);
    return EXIT_SUCCESS;

    _L_return_ERR: {
        z__String_delete(&str);
        z__String_delete(&str_out);       
        return EXIT_FAILURE;
    }
}
