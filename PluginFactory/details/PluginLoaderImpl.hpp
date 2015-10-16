#pragma once
#include <PluginFactory/details/build_traits.hpp>

namespace PluginFactory { namespace details {
    
    // The primary template has none of the methods specified.
    template<build_traits::Platform Platform>
    struct PluginLoaderImpl
    {
    };
}}
