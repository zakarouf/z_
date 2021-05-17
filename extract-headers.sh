#!/bin/sh

echo "Getting Headers\n"
echo "Extracting in ./build/include/"

find src -name '*.h' | cpio -pdm  ./build/include/

rm -rf ./build/include/z_
mv ./build/include/src ./build/include/z_

echo "Extration Complete"
echo "\nAt ./build/include/z_"
