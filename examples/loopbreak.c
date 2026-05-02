#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i = 1;
    while (1) {
        printf("%i", i);
        i += 1;
        if(i >= 10) break;
    }
    return EXIT_SUCCESS;
}

