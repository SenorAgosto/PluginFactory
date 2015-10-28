#pragma once 
#include <build_traits/build_traits.hpp>

////////////////////////////////////
// This header is organized in the following way:
// - The primary template declaration is included first.
// - every platform's template specializations are included next.
//
// This arrangement allows us to avoid an over abundance
// of macro logic. All of the macro logic is contained
// here or in build_traits. Everything else is
// normal C++ code.

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
