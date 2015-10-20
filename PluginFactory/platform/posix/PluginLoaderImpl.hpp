#pragma once 
#include <PluginFactory/Exceptions.hpp>

#include <PluginFactory/details/build_traits.hpp>
#include <PluginFactory/details/PluginHandle.hpp>
#include <PluginFactory/details/PluginLoaderImpl.hpp>

#include <PluginFactory/platform/posix/OpenLibrary.hpp>
#include <PluginFactory/platform/posix/PosixPluginLoader.hpp>

#include <boost/filesystem/path.hpp>
#include <string>
#include <dlfcn.h>

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
