#pragma once 
#include <build_traits/build_traits.hpp>
#include <string> 

namespace PluginFactory { namespace details {
    
    struct UnixPluginExtension
    {
        static inline std::string extension() { return ".so"; }
    };
    
    struct MacOsXPluginExtension
    {
        static inline std::string extension() { return ".dylib"; }
    };
    
    struct WindowsPluginExtension
    {
        static inline std::string extension() { return ".dll"; }
    };
    
    
    // Primary template
    template<build_traits::Platform>
    struct PluginExtensionHelperImpl : public UnixPluginExtension
    {
    };
    
    // windows specialization
    template<>
    struct PluginExtensionHelperImpl<build_traits::Platform::windows> : public WindowsPluginExtension
    {
    };
    
    // macosx specialization
    template<>
    struct PluginExtensionHelperImpl<build_traits::Platform::macosx> : public MacOsXPluginExtension
    {
    };
    
    using PluginExtensionHelper = PluginExtensionHelperImpl<build_traits::platform()>;
}}
