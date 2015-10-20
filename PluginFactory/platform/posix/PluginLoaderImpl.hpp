#pragma once 
#include <PluginFactory/Exceptions.hpp>

#include <PluginFactory/details/build_traits.hpp>
#include <PluginFactory/details/PluginCreatorHandle.hpp>
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
            , path_(plugin)
        {
        }

        void validateCompiler(const std::string& /*compilerToken*/){}
        void validatePluginVersion(const std::string& /*pluginVersion*/){}
        void validatePluginServiceVersion(const std::string& /*serviceVersion*/){}
        
        template<class PluginInterface, class PluginServiceInterface>
        PluginCreatorHandle<PluginInterface, PluginServiceInterface> getPluginCreatorHandle()
        {
            void* symbolAddress = dlsym(libraryHandle_.get(), "createPlugin");
            if(symbolAddress == nullptr)
            {
                throw PluginCreationMethodNotFoundInPluginCode(path_);
            }
            
            return PluginCreatorHandle<PluginInterface, PluginServiceInterface>();
        }
        
    private:
        LibraryHandle libraryHandle_;
        const boost::filesystem::path path_;
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
