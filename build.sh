#!/bin/sh

# Basic Config, edit these variabl
PROJECT_NAME="z_"
CC=gcc
CCFLAGS="-Wall -Wextra -O2"
LIBFLAGS=""
TESTFLAGS="-ggdb -g"
AR=ar
ARFLAGS="-q"
OUT_BIN="z_"
OUT_LIB="libz_.a"
OUT_HEAD="z_"
BIN_DIR="/usr/local/bin/"
LIB_DIR="/usr/local/lib/"
INC_DIR="/usr/local/include/"
BIN_DIR="$HOME/../usr/bin/"
LIB_DIR="$HOME/../usr/lib/"
INC_DIR="$HOME/../usr/include/"

check_mkdir() {
    if [ -d "$1" ]; then
        continue
    else
        $(mkdir "$1")
    fi
}

check_build() {
    check_mkdir "./build"
    check_mkdir "./build/lib"
    check_mkdir "./build/include"
    check_mkdir "./build/bin"
}

make_clean() {
    clean_what="./build"
    casevar=$1
    case "$casevar" in
        "lib") clean_what="$clean_what/lib"
        ;;
        "headers") clean_what="$clean_what/include"
        ;;
        "test") clean_what="$clean_what/test"
        ;;
        "bin") clean_what="$clean_what/bin"
        ;;
        "ofiles") clean_what="*.o"
        ;;
        "all") clean_what="./build/* *.o"
        ;;
        *) echo "Unknown option '$*'"
           return
        ;;
    esac

    $(rm -rf $clean_what)
}

make_lib_header() {
    name=$OUT_HEAD
    $(find "./src/lib" -name '*.h' | cpio -pdm ./build/include)
    $(rm -rf ./build/$name)
    $(mv ./build/include/src/lib ./build/include/$name)
    $(rm -rf ./build/include/src)
    echo "Made headers as $name in ./build/include"
}

make_lib(){
    extraflags="$1"
    FILES=$(find "./src/lib" -name '*.c')
    $($CC $CCFLAGS $extraflags -c $FILES)
    $($AR $ARFLAGS $OUT_LIB *.o)
    make_clean "all"
    check_build
    $(mv $OUT_LIB ./build/lib)
}

make_bin(){
    make_lib
    FILES=$(find "./src/bin" -name '*.c')
    $(mkdir ./build/bin)
    $($CC $CCFLAGS $LIBFLAGS $FILES ./build/lib/$OUT_LIB -o ./build/bin/$OUT_BIN)
}

make_install_lib() {
    make_lib
    $(mv -ni ./build/lib/$OUT_LIB "$LIB_DIR")
    make_lib_header
    $(cp -Rf ./build/include/$OUT_HEAD "$INC_DIR")
    $(rm -rf ./build/include/$OUT_HEAD)
}

make_install_bin() {
    make_bin
    $(mv -ni ./build/bin/$OUT_BIN "$BIN_DIR")
}

make_install() {
    case "$1" in
        "bin") make_install_bin
        ;;
        "lib") make_install_lib
        ;;
        *) echo "Unknown option '$1', either use 'bin' or 'lib'"
        ;;
    esac
}

make_test_lib(){
    make_lib $TESTFLAGS
    FILES=$(find "./src/testlib" -name '*.c')
    $($CC $CCFLAGS $TESTFLAGS $FILES ./build/lib/$OUT_LIB -o "./build/testlib")

    case "$1" in
        "run") $(./build/testlib)
        ;;
        *) echo "Use './build.sh testlib run' to build & run the test"
        ;;
    esac   
}

make() {
    check_build
    case "$1" in
        "lib") make_lib
        ;;
        "headers") make_lib_header
        ;;
        "bin") make_bin
        ;;
        "install") make_install $2
        ;;
        "testlib") make_test_lib $2
        ;;
        "testbin") make_test_bin $2
        ;;
        "clean") 
            make_clean $2
        ;;
        *)
            echo "Unknown option '$1'"
            echo "Usage: $0 [ lib | headers | bin | testlib | testbin | install[lib|bin]]"
        ;;
    esac

}

make $*
