#include <PluginFactory/platform/win32/WindowsPluginLoader.hpp>

namespace PluginFactory { namespace platform { namespace win32 {  

	WindowsPluginLoader::WindowsPluginLoader(const boost::filesystem::path& plugin)
		: libraryHandle_(plugin)
		, path_(plugin)
	{
	}

	void WindowsPluginLoader::validateCompiler(const std::string& /*compilerToken*/)
	{
	}

	void WindowsPluginLoader::validatePluginVersion(const std::string& /*pluginVersion*/)
	{
	}

	void WindowsPluginLoader::validatePluginServiceVersion(const std::string& /*serviceVersion*/)
	{
	}

}}}
