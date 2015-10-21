#pragma once 
#include <PluginFactory/details/build_traits.hpp>
#include <PluginFactory/platform/posix/PosixPluginLoader.hpp>

// the namespace here doesn't match the filesystem layout because
// these are POSIX specializations of PluginFactory::details::PluginLoaderImpl
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
