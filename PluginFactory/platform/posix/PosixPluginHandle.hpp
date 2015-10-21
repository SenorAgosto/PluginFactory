#pragma once
#include <PluginFactory/platform/posix/LibraryHandle.hpp>

namespace PluginFactory { namespace platform { namespace posix {

    template<class PluginInterface, class PluginServiceInterface>
    class PosixPluginHandle
    {
    public:
        using CreatePluginMethod = void* (*)(void*);
        PosixPluginHandle(LibraryHandle libraryHandle, void* createAddress);

        // invoke the createPlugin method contained in the plugin,
        // return the pointer to the created plugin.
        PluginInterface* operator()(PluginServiceInterface& service);
        
    private:
        // function pointer for the createPlugin in our loaded plugin
        CreatePluginMethod createPlugin_;
        LibraryHandle libraryHandle_;
    };
    
    
    template<class PluginInterface, class PluginServiceInterface>
    PosixPluginHandle<PluginInterface, PluginServiceInterface>::PosixPluginHandle(LibraryHandle libraryHandle, void* createAddress)
        : createPlugin_(reinterpret_cast<CreatePluginMethod>(createAddress))
        , libraryHandle_(std::move(libraryHandle))
    {
    }
    
    template<class PluginInterface, class PluginServiceInterface>
    PluginInterface* PosixPluginHandle<PluginInterface, PluginServiceInterface>::operator()(PluginServiceInterface& service)
    {
        void* plugin = createPlugin_(static_cast<void*>(&service));
        return static_cast<PluginInterface*>(plugin);
    }
}}}
