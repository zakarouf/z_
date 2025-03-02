#ifndef ZAKAROUF_Z_STD_ARCH_H
#define ZAKAROUF_Z_STD_ARCH_H

    #if defined(__x86_64__) || defined(_M_X64)
        #define Z__ARCH_x86_64
        #define Z__ARCHSTR() "x86_64"

    #elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
        #define Z__ARCH_x86_32
        #define Z__ARCHSTR() "x86_32"

    #elif defined(__ARM_ARCH_2__)
        #define Z__ARCH_ARM2
        #define Z__ARCHSTR() "ARM2"

    #elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
        #define Z__ARCH_ARM3
        #define Z__ARCHSTR() "ARM3"

    #elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
        #define Z__ARCH_ARM4T
        #define Z__ARCHSTR() "ARM4T"

    #elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
        #define Z__ARCH_ARM5
        #define Z__ARCHSTR() "ARM5"

    #elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
        #define Z__ARCH_ARM6T2
        #define Z__ARCHSTR() "ARM6T2"

    #elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
        #define Z__ARCH_ARM6
        #define Z__ARCHSTR() "ARM6"

    #elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        #define Z__ARCH_ARM7
        #define Z__ARCHSTR() "ARM7"

    #elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        #define Z__ARCH_ARM7A
        #define Z__ARCHSTR() "ARM7A"

    #elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        #define Z__ARCH_ARM7R
        #define Z__ARCHSTR() "ARM7R"

    #elif defined(__ARM_ARCH_7M__)
        #define Z__ARCH_ARM7M
        #define Z__ARCHSTR() "ARM7M"

    #elif defined(__ARM_ARCH_7S__)
        #define Z__ARCH_ARM7S
        #define Z__ARCHSTR() "ARM7S"

    #elif defined(__aarch64__) || defined(_M_ARM64)
        #define Z__ARCH_ARM64
        #define Z__ARCHSTR() "ARM64"

    #elif defined(mips) || defined(__mips__) || defined(__mips)
        #define Z__ARCH_MIPS
        #define Z__ARCHSTR() "MIPS"

    #elif defined(__sh__)
        #define Z__ARCH_SUPERH
        #define Z__ARCHSTR() "SUPERH"

    #elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
        #define Z__ARCH_POWERPC
        #define Z__ARCHSTR() "POWERPC"

    #elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
        #define Z__ARCH_POWERPC64
        #define Z__ARCHSTR() "POWERPC64"

    #elif defined(__sparc__) || defined(__sparc)
        #define Z__ARCH_SPARC
        #define Z__ARCHSTR() "SPARC"

    #elif defined(__m68k__)
        #define Z__ARCH_M68K
        #define Z__ARCHSTR() "M68K"

    #else
        #define Z__ARCH_UNKNOWN
        #define Z__ARCHSTR() "UNKNOWN"

    #endif

#endif
