#!/bin/sh

LIB_DIR="/usr/local/lib/"
INCLUDE_DIR="/usr/local/include/"

sh make-lib.sh

mv -vi build/lib/libzkcollection.a "$LIB_DIR"

cp -Ri build/include/z_ "$INCLUDE_DIR"

rm -rf build/include/z_
