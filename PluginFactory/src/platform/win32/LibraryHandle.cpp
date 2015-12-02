#include <PluginFactory/platform/win32/LibraryHandle.hpp>
#include <PluginFactory/Exceptions.hpp>

#include <boost/filesystem/path.hpp>

namespace PluginFactory { namespace platform { namespace win32 {

	LibraryHandle::LibraryHandle(const boost::filesystem::path& plugin)
		: lib_(LoadLibrary(TEXT(plugin.string().c_str())))
	{
		if(!lib_)
		{
			auto errorCode = GetLastError();
			std::string errorMessage = "LoadLibrary error: " + std::to_string(errorCode);

			throw PluginLoaderException(plugin, errorMessage);
		}
	}

	LibraryHandle::~LibraryHandle()
	{
		if(lib_)
		{
			FreeLibrary(lib_);
		}
	}

	HMODULE LibraryHandle::get()
	{
		return lib_;
	}

}}}
