echo "Initiating Test"
sh ./make-lib.sh

CC=gcc
SRC="./test"
LIB="./build/lib/libzkcollection.a"
OUT="./build/test"
CFILES="$(find $SRC -name '*.c')"

CFLAGS="-std=c99 -ggdb -fopenmp -ftrack-macro-expansion=2 -fsanitize=address -O3"

ERRFLAGS="-Wextra -Wall"

$CC $CFLAGS $ERRFLAGS $CFILES $LIB -o $OUT

cd build
./test

echo "Cleaning Up"
rm -rf ./build/*

echo "Finished!"
