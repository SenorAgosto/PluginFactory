#pragma once 
#include <PluginFactory/details/PluginHandle.hpp>

#include <boost/filesystem/path.hpp>
#include <string>

#include <Windows.h>

namespace PluginFactory { namespace platform { namespace win32 {

	class WindowsPluginLoader
	{
	public:
		WindowsPluginLoader(const boost::filesystem::path& plugin);

		void validateCompiler(const std::string& /*compilerToken*/);
		void validatePluginVersion(const std::string& /*pluginVersion*/);
		void validatePluginServiceVersion(const std::string& /*serviceVersion*/);

		template<class PluginInterface, class PluginServiceInterface>
		details::PluginHandle<PluginInterface, PluginServiceInterface> getPluginHandle();

	private:
		LibraryHandle libraryHandle_;
		const boost::filesystem::path path_;
	};


	template<class PluginInterface, class PluginServiceInterface>
	details::PluginHandle<PluginInterface, PluginServiceInterface> WindowsPluginLoader::getPluginHandle()
	{
		FARPROC createPluginAddress = GetProcAddress(libraryHandle_.get(), TEXT("createPlugin"));
		if(createPluginAddress == nullptr)
		{
			throw PluginCreationMethodNotFoundInPluginCode(path_);
		}

		return details::template PluginHandle<PluginInterface, PluginServiceInterface>(std::move(libraryHandle_), createPluginAddress);
	}
}}}
