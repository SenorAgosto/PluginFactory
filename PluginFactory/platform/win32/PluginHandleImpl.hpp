#pragma once 
#include <PluginFactory/platform/win32/WindowsPluginHandle.hpp>

// the namespace here doesn't match the filesystem layout because
// these are win32 specializations of PluginFactory::details::PluginHandleImpl
namespace PluginFactory { namespace details {

	template<class PluginInterface, class PluginServiceInterface>
	struct PluginHandleImpl<PluginInterface, PluginServiceInterface, build_traits::Platform::windows>
		: public platform::win32::WindowsPluginHandle<PluginInterface, PluginServiceInterface>
	{
		// pull in constructors from base.
		using platform::win32::WindowsPluginHandle<PluginInterface, PluginServiceInterface>::WindowsPluginHandle;
	};

}}
