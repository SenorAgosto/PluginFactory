#pragma once 
#include <PluginFactory/platform/posix/PosixPluginHandle.hpp>

namespace PluginFactory { namespace details {

    template<class PluginInterface, class PluginServiceInterface>
    struct PluginHandleImpl<PluginInterface, PluginServiceInterface, build_traits::Platform::macosx>
        : public platform::posix::PosixPluginHandle<PluginInterface, PluginServiceInterface>
    {
        // pull in constructors from base.
        using platform::posix::PosixPluginHandle<PluginInterface, PluginServiceInterface>::PosixPluginHandle;
    };
}}
