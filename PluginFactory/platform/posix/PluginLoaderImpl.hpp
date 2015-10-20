#pragma once 
#include <PluginFactory/details/build_traits.hpp>
#include <PluginFactory/platform/posix/PosixPluginLoader.hpp>

namespace PluginFactory { namespace details {
    
    // Mac OS X specialization
    template<>
    struct PluginLoaderImpl<build_traits::Platform::macosx> : public platform::posix::PosixPluginLoader
    {
        using platform::posix::PosixPluginLoader::PosixPluginLoader;
    };
    
    // Linux specialization
    template<>
    struct PluginLoaderImpl<build_traits::Platform::linux> : public platform::posix::PosixPluginLoader
    {
        using platform::posix::PosixPluginLoader::PosixPluginLoader;
    };
    
    // BSD... etc.
}}
