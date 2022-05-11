echo "Initiating Test"
sh ./make-lib.sh

echo "Making Test"
CC=clang
SRC="./test"
LIB="./build/lib/libzkcollection.a"
OUT="./build/test"
CFILES="$(find $SRC -name '*.c')"

CFLAGS="-std=c99 -ggdb -fsanitize=address -O3"

ERRFLAGS="-Wextra -Wall"

$CC $CFLAGS $ERRFLAGS $CFILES $LIB -o $OUT

echo "Running Test"
cd build
./test

echo "Cleaning Up"
rm -rf ./build/*

echo "Finished!"
