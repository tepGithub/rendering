#pragma once

#if defined(_MSC_VER)
    #define DEBUGBREAK() __debugbreak()
#elif defined(__aarch64__)
    #if defined(__ANDROID__)
        #include <signal.h>
        #define DEBUGBREAK() raise(SIGTRAP)
    #else
        #define DEBUGBREAK()                                    \
            __extension__({                                     \
                __asm__ __volatile__("brk    #0xf000   \n\t"    \
                                    "mov    x0, x0");           \
            })
    #endif
#else
    // Not implemented for this platform
#endif
