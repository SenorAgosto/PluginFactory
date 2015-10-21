#pragma once 
#include <memory>

// Use this helper macro to create a plugin creation method in your plugin implementation.
#define MAKE_PLUGIN_METHODS(PluginInterface, ConcretePluginImpl) \
extern "C" { \
    void* createPlugin(void* service) \
    { \
        static std::unique_ptr<PluginInterface> plugin_(new ConcretePluginImpl(service)); \
        return plugin_.get(); \
    } \
}
