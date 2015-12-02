#pragma once
#include <memory>

#ifdef WIN32 
	#define PLUGIN_FACTORY_DLL_EXPORT __declspec(dllexport)
	#define PLUGIN_FACTORY_CDECL __cdecl 
#else
	#define PLUGIN_FACTORY_DLL_EXPORT 
	#define PLUGIN_FACTORY_CDECL 
#endif


// Use this helper macro to create a plugin creation method in your plugin implementation.
#define MAKE_PLUGIN_METHODS(PluginInterface, ConcretePluginImpl) \
extern "C" { \
    PLUGIN_FACTORY_DLL_EXPORT void* PLUGIN_FACTORY_CDECL createPlugin(void* service) \
    { \
        static std::unique_ptr<PluginInterface> plugin_(new ConcretePluginImpl(service)); \
        return plugin_.get(); \
    } \
}
