#pragma once 
#include <PluginFactory/Exceptions.hpp>

#include <PluginFactory/details/PluginHandle.hpp>
#include <PluginFactory/platform/posix/OpenLibrary.hpp>

#include <boost/filesystem/path.hpp>
#include <dlfcn.h>
#include <string>

namespace PluginFactory { namespace platform { namespace posix {

    class PosixPluginLoader
    {
    public:
        PosixPluginLoader(const boost::filesystem::path& plugin);
        
        void validateCompiler(const std::string& /*compilerToken*/);
        void validatePluginVersion(const std::string& /*pluginVersion*/);
        void validatePluginServiceVersion(const std::string& /*serviceVersion*/);
        
        template<class PluginInterface, class PluginServiceInterface>
        details::PluginHandle<PluginInterface, PluginServiceInterface> getPluginCreatorHandle();
        
    private:
        LibraryHandle libraryHandle_;
        const boost::filesystem::path path_;
    };


    template<class PluginInterface, class PluginServiceInterface>
    details::PluginHandle<PluginInterface, PluginServiceInterface> PosixPluginLoader::getPluginCreatorHandle()
    {
        void* symbolAddress = dlsym(libraryHandle_.get(), "createPlugin");
        if(symbolAddress == nullptr)
        {
            throw PluginCreationMethodNotFoundInPluginCode(path_);
        }
        
        return details::PluginHandle<PluginInterface, PluginServiceInterface>(std::move(libraryHandle_), symbolAddress);
    }

}}}
