#pragma once 
#include <PluginFactory/platform/posix/PosixPluginHandle.hpp>

// the namespace here doesn't match the filesystem layout because
// these are POSIX specializations of PluginFactory::details::PluginHandleImpl
namespace PluginFactory { namespace details {

    template<class PluginInterface, class PluginServiceInterface>
    struct PluginHandleImpl<PluginInterface, PluginServiceInterface, build_traits::Platform::macosx>
        : public platform::posix::PosixPluginHandle<PluginInterface, PluginServiceInterface>
    {
        // pull in constructors from base.
        using platform::posix::PosixPluginHandle<PluginInterface, PluginServiceInterface>::PosixPluginHandle;
    };
    
    template<class PluginInterface, class PluginServiceInterface>
    struct PluginHandleImpl<PluginInterface, PluginServiceInterface, build_traits::Platform::linux>
        : public platform::posix::PosixPluginHandle<PluginInterface, PluginServiceInterface>
    {
        // pull in constructors from base.
        using platform::posix::PosixPluginHandle<PluginInterface, PluginServiceInterface>::PosixPluginHandle;
    };
}}
