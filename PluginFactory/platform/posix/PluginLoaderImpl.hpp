#pragma once 
#include <PluginFactory/details/build_traits.hpp>
#include <PluginFactory/details/PluginHandle.hpp>
#include <PluginFactory/details/PluginLoaderImpl.hpp>

#include <PluginFactory/platform/posix/OpenLibrary.hpp>

#include <boost/filesystem/path.hpp>
#include <string>
#include <dlfcn.h>

namespace PluginFactory { namespace details {
    
    class PosixPluginLoader
    {
    public:
        PosixPluginLoader(const boost::filesystem::path& plugin)
            : libraryHandle_(openLibrary(plugin))
        {
        }

        void validateCompiler(const std::string& /*compilerToken*/){}
        void validatePluginVersion(const std::string& /*pluginVersion*/){}
        void validatePluginServiceVersion(const std::string& /*serviceVersion*/){}
        
        template<class PluginInterface, class PluginServiceInterface>
        PluginHandle<PluginInterface, PluginServiceInterface> getPluginHandle()
        {
            return PluginHandle<PluginInterface, PluginServiceInterface>();
        }
        
    private:
        std::unique_ptr<void, DlCloser> libraryHandle_;
    };
    
    
    // Mac OS X specialization
    template<>
    struct PluginLoaderImpl<build_traits::Platform::macosx> : public PosixPluginLoader
    {
        using PosixPluginLoader::PosixPluginLoader;
    };
    
    // Linux specialization
    template<>
    struct PluginLoaderImpl<build_traits::Platform::linux> : public PosixPluginLoader
    {
        using PosixPluginLoader::PosixPluginLoader;
    };
    
    // BSD... etc.
}}
