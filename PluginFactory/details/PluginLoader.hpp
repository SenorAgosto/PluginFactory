#pragma once 
#include <PluginFactory/details/build_traits.hpp>

// include the primary template.
#include <PluginFactory/details/PluginLoaderImpl.hpp>

// include specialization for windows
#ifdef WIN32
    #include <PluginFactory/platform/win32/PluginLoaderImpl.hpp>
#endif

// include specialization for posix
#ifdef POSIX
    #include <PluginFactory/platform/posix/PluginLoaderImpl.hpp>
#endif

namespace PluginFactory { namespace details {
    
    using PluginLoader = PluginLoaderImpl<build_traits::platform()>;
}}
