#!/bin/sh

CC=gcc
AR=ar
OUT="libzkcollection.a"
CFILES="$(find src -name '*.c')"

echo "Compiling\n"
$CC -Os -O3 -Wall -Wextra -c $CFILES

echo "Creating Library $OUT\n"
AR -q $OUT *.o
rm *.o

echo "Installing library\n"
rm -rf ./build/lib
mkdir build
mkdir ./build/lib
mv "$OUT" ./build/lib/

sh extract-headers.sh

