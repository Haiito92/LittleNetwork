#pragma once

#if !defined(LN_STATIC)
    #ifdef LN_COMPILE
        #define LN_API __declspec(dllexport)
    #else
        #define LN_API __declspec(dllimport)
    #endif
#else
    #define LN_API
#endif
