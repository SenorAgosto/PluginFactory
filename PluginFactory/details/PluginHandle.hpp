#pragma once 

namespace PluginFactory {
    
    // [ARG]: todo: implement a struct to hold plugin handles
    // returned by the PluginLoader
    template<class PluginInterface, class PluginServiceInterface>
    struct PluginHandle
    {
        PluginInterface* operator()(PluginServiceInterface&)
        {
            return nullptr;
        }
    };
}
