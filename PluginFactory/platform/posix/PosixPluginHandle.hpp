#pragma once 
#include <PluginFactory/platform/posix/OpenLibrary.hpp>

namespace PluginFactory { namespace platform { namespace posix {

    template<class PluginInterface, class PluginServiceInterface>
    class PosixPluginHandle
    {
    public:
        using CreatePluginMethod = void* (*)(void*);
        
        PosixPluginHandle(LibraryHandle libraryHandle, void* symbolAddress);
        
        // invoke the createPlugin method contained in the plugin,
        // return the pointer to the created plugin.
        PluginInterface* operator()(PluginServiceInterface& service);
        
    private:
        // function pointer for the createPlugin in our loaded plugin
        CreatePluginMethod createPlugin_;
        LibraryHandle libraryHandle_;
    };
    
    
    template<class PluginInterface, class PluginServiceInterface>
    PosixPluginHandle<PluginInterface, PluginServiceInterface>::PosixPluginHandle(LibraryHandle libraryHandle, void* symbolAddress)
        : libraryHandle_(std::move(libraryHandle))
        , createPlugin_(reinterpret_cast<CreatePluginMethod>(symbolAddress))
    {
    }
    
    template<class PluginInterface, class PluginServiceInterface>
    PluginInterface* PosixPluginHandle<PluginInterface, PluginServiceInterface>::operator()(PluginServiceInterface& service)
    {
        auto plugin = createPlugin_(static_cast<void*>(&service));
        return static_cast<PluginInterface*>(plugin);
    }
}}}
