#pragma once
#include <PluginFactory/platform/win32/WindowsPluginLoader.hpp>

// the namespace here doesn't match the filesystem
// layout because we're implementing a specialization.
namespace PluginFactory { namespace details {
    
	template<>
	struct PluginLoaderImpl<build_traits::Platform::windows> : public platform::win32::WindowsPluginLoader
	{
		using platform::win32::WindowsPluginLoader::WindowsPluginLoader;
	};
}}
