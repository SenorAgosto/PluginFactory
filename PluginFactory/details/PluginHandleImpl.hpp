#pragma once 
#include <build_traits/build_traits.hpp>

namespace PluginFactory { namespace details {

    // The purpose of the PluginHandle is to wrap the plugin instantiation
    // method & hold the OS supplied shared lib handle.
    //
    // This is the primary template declaration.
    template<class PluginInterface, class PluginServiceInterface, build_traits::Platform platform>
    struct PluginHandleImpl
    {
    };
}}
