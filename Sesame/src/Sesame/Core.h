#pragma once

#ifdef SSM_PLATFORM_WINDOWS
    #ifdef SSM_BUILD_DLL
        #define SESAME_API __declspec(dllexport)
    #else
        #define SESAME_API __declspec(dllimport)
    #endif
#else
    #error This engine only is supported by Windows
#endif

#ifdef SSM_ENABLE_ASSERTS
    #define SSM_ASSERT(x, ...) { if(!(x)) {SSM_ERROR("Assertion Failed: {0}", __VA_ARGS); __debugbreak(); } }
    #define SSM_CORE_ASSERT(x, ...) { if(!(x)) {SSM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS); __debugbreak(); } }
#else
    #define SSM_ASSERT(x, ...)
    #define SSM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)