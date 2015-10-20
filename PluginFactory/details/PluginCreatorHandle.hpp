#pragma once 

namespace PluginFactory {
    
    // [ARG]: todo: implement a struct to hold plugin handles
    // returned by the PluginLoader
    //
    // The purpose of the PluginHandle is to wrap the plugin instantiation
    // method & hold the OS supplied shared lib handle.
    template<class PluginInterface, class PluginServiceInterface>
    struct PluginCreatorHandle
    {
        PluginInterface* operator()(PluginServiceInterface&)
        {
            // TODO: implement
            return nullptr;
        }
    };
}
