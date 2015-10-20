#pragma once 

// Use this helper macro to create a plugin creation method in your plugin implementation &
// your base process. In the base process, the signature of the method will be used to lookup
// the createPlugin() in the plugin shared library.
#define MAKE_PLUGIN_CREATION_METHOD(ConcretePluginImpl) \
extern "C" { \
    void* createPlugin(void* service) \
    { \
        return new ConcretePluginImpl(service); \
    } \
}\
