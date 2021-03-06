#pragma once

#include <memory>

#ifdef SSM_PLATFORM_WINDOWS
    #ifdef SSM_DYNAMIC_LINK
        #ifdef SSM_BUILD_DLL
            #define SESAME_API __declspec(dllexport)
        #else
            #define SESAME_API __declspec(dllimport)
        #endif
    #else
        #define SESAME_API
    #endif
#else
    #error This engine only is supported by Windows
#endif

#ifdef SSM_DEBUG
    #define SSM_ENABLE_ASSERTS
#endif

#ifdef SSM_ENABLE_ASSERTS
#define SSM_ASSERT(x, ...) { if(!(x)) {SSM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SSM_CORE_ASSERT(x, ...) { if(!(x)) {SSM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define SSM_ASSERT(x, ...)
    #define SSM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SSM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Sesame {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}