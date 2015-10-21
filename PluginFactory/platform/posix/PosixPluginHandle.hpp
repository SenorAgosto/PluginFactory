#pragma once 
#include <PluginFactory/PluginDeleter.hpp>
#include <PluginFactory/platform/posix/LibraryHandle.hpp>

namespace PluginFactory { namespace platform { namespace posix {

    template<class PluginInterface, class PluginServiceInterface>
    class PosixPluginHandle
    {
    public:
        using CreatePluginMethod = void* (*)(void*);
        using DeletePluginMethod = void (*)(void*);
        
        struct AsSharedPtr {} static create_shared;
        
        PosixPluginHandle(LibraryHandle libraryHandle, void* createAddress, void* deleteAddress);

        // invoke the createPlugin method contained in the plugin,
        // return the pointer to the created plugin.
        std::unique_ptr<PluginInterface, PluginDeleter<PluginInterface>> operator()(PluginServiceInterface& service);
        std::shared_ptr<PluginInterface> operator()(PluginServiceInterface& service, AsSharedPtr /*create_shared*/);
        
    private:
        // function pointer for the createPlugin in our loaded plugin
        CreatePluginMethod createPlugin_;
        DeletePluginMethod deletePlugin_;
        
        LibraryHandle libraryHandle_;
    };
    
    
    // initialize static member
    template<class PluginInterface, class PluginServiceInterface>
    typename PosixPluginHandle<PluginInterface, PluginServiceInterface>::AsSharedPtr PosixPluginHandle<PluginInterface, PluginServiceInterface>::create_shared;
    
    template<class PluginInterface, class PluginServiceInterface>
    PosixPluginHandle<PluginInterface, PluginServiceInterface>::PosixPluginHandle(LibraryHandle libraryHandle, void* createAddress, void* deleteAddress)
        : createPlugin_(reinterpret_cast<CreatePluginMethod>(createAddress))
        , deletePlugin_(reinterpret_cast<DeletePluginMethod>(deleteAddress))
        , libraryHandle_(std::move(libraryHandle))
    {
    }
    
    template<class PluginInterface, class PluginServiceInterface>
    std::unique_ptr<PluginInterface, PluginDeleter<PluginInterface>> PosixPluginHandle<PluginInterface, PluginServiceInterface>::operator()(PluginServiceInterface& service)
    {
        auto plugin = createPlugin_(static_cast<void*>(&service));
        return std::unique_ptr<PluginInterface, PluginDeleter<PluginInterface>>(static_cast<PluginInterface*>(plugin), PluginDeleter<PluginInterface>(deletePlugin_));
    }
    
    template<class PluginInterface, class PluginServiceInterface>
    std::shared_ptr<PluginInterface> PosixPluginHandle<PluginInterface, PluginServiceInterface>::operator()(PluginServiceInterface& service, AsSharedPtr /*create_shared*/)
    {
        auto plugin = createPlugin_(static_cast<void*>(&service));
        return std::shared_ptr<PluginInterface>(static_cast<PluginInterface*>(plugin), PluginDeleter<PluginInterface>(deletePlugin_));
    }
}}}
