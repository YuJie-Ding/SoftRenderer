#pragma once

#include <iostream>
#include <assert.h>

#ifdef __GNUC__
    #ifdef BUILD_DLL
        #define DLL_API   __attribute__((dllexport)) 
    #else
        #define DLL_API   __attribute__((dllimport))
    #endif
#else
    #ifdef BUILD_DLL
        #define DLL_API   __declspec(dllexport) 
    #else
        #define DLL_API   __declspec(dllimport)
    #endif
#endif


#define SR_ASSERT(x, ...) { if(!(x)) { std::cout << "Assertion Failed: {0}" << __VA_ARGS__; assert(0); } }

