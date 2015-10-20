#pragma once 
#include <PluginFactory/details/build_traits.hpp>

// primary template declaration
#include <PluginFactory/details/PluginHandleImpl.hpp>

// template specializations for Windows operating systems
#ifdef WIN32
    #include <PluginFactory/platform/win32/PluginHandleImpl.hpp>
#endif

// template specializations for POSIX operating systems
#ifdef POSIX
    #include <PluginFactory/platform/posix/PluginHandleImpl.hpp>
#endif

namespace PluginFactory { namespace details {

    template<class PluginInterface, class PluginServiceInterface>
    using PluginHandle = PluginHandleImpl<PluginInterface, PluginServiceInterface, build_traits::platform()>;
}}
