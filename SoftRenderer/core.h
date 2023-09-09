#pragma once

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
