#pragma once 

#define BUILD_TRAITS_PLATFORM Platform::macosx

struct build_traits
{
    enum class Platform {
          macosx
        , windows
        , posix
    };
    
    static const Platform platform = BUILD_TRAITS_PLATFORM;
};
