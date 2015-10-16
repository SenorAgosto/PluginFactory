#pragma once
#include <PluginFactory/details/build_traits.hpp>
#include <string>

namespace boost { namespace filesystem {
    class path;
}}

namespace PluginFactory { namespace details {
    
    // The primary template has none of the methods specified.
    template<build_traits::Platform Platform>
    struct PluginLoaderImpl
    {
    };
}}
