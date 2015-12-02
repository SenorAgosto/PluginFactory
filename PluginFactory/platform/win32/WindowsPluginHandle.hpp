#pragma once
#include <PluginFactory/platform/win32/LibraryHandle.hpp>

namespace PluginFactory { namespace platform { namespace win32 {

	template<class PluginInterface, class PluginServiceInterface>
	class WindowsPluginHandle
	{
	public:
		using CreatePluginMethod = void* (*)(void*);
		WindowsPluginHandle(LibraryHandle libraryHandle, FARPROC createAddress);

		// invoke the createPlugin method contained in the plugin,
		// return the pointer to the created plugin.
		PluginInterface* operator()(PluginServiceInterface& service);

	private:
		// function pointer for the createPlugin in our loaded plugin
		CreatePluginMethod createPlugin_;
		LibraryHandle libraryHandle_;
	};


	template<class PluginInterface, class PluginServiceInterface>
	WindowsPluginHandle<PluginInterface, PluginServiceInterface>::WindowsPluginHandle(LibraryHandle libraryHandle, FARPROC createAddress)
		: createPlugin_(reinterpret_cast<CreatePluginMethod>(createAddress))
		, libraryHandle_(libraryHandle)
	{
	}

	template<class PluginInterface, class PluginServiceInterface>
	PluginInterface* WindowsPluginHandle<PluginInterface, PluginServiceInterface>::operator()(PluginServiceInterface& service)
	{
		void* plugin = createPlugin_(static_cast<void*>(&service));
		return static_cast<PluginInterface*>(plugin);
	}
}}}
