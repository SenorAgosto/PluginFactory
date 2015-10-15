#pragma once
#include <PluginFactory/details/PluginHandle.hpp>
#include <PluginFactory/details/build_traits.hpp>

#include <boost/filesystem/path.hpp>
#include <string>

namespace PluginFactory { namespace details {
    
    // The primary template has a null implementation.
    // Actual implementations will live in specializations.
    template<build_traits::Platform Platform>
    class PluginLoaderImpl
    {
    public:
        PluginLoaderImpl(const boost::filesystem::path& /*pluginPath*/){}
        
        void validateCompiler(const std::string& /*compilerToken*/) {}
        void validatePluginVersion(const std::string& /*pluginVersion*/) {}
        void validatePluginServiceVersion(const std::string& /*serviceVersion*/) {}
        
        template<class PluginInterface, class PluginServiceInterface>
        PluginHandle<PluginInterface, PluginServiceInterface> getPluginHandle()
        {
            return PluginHandle<PluginInterface, PluginServiceInterface>();
        }
    };
}}
