#pragma once 
#include <PluginFactory/details/build_traits.hpp>

// include the primary template.
#include <PluginFactory/details/PluginLoaderImpl.hpp>

// include specialization for windows
#ifdef WIN32
    #include <PluginFactory/platform/win32/PluginLoaderImpl.hpp>
    #define PluginLoaderPlatform build_traits::Platform::windows
#endif

// include specialization for posix
#ifdef POSIX
    #include <PluginFactory/platform/posix/PluginLoaderImpl.hpp>
    #define PluginLoaderPlatform build_traits::Platform::posix
#endif

namespace PluginFactory { namespace details {
    
    using PluginLoader = PluginLoaderImpl<PluginLoaderPlatform>;
}}
