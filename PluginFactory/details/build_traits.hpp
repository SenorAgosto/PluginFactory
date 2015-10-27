#pragma once 
#include <PluginFactory/details/PlatformConfig.hpp>

struct build_traits
{
    enum class Platform {
          linux
        , macosx
        , windows
    };
    
    constexpr static Platform platform()
    {
        return BUILD_TRAITS_PLATFORM;
    }
    
    constexpr static bool is_posix()
    {
        return
            (platform() == Platform::linux) ||
            (platform() == Platform::macosx);
    }
};
