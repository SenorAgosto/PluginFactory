#pragma once
#include <Windows.h>

namespace boost { namespace filesystem {
	class path;
}}

namespace PluginFactory { namespace platform { namespace win32 {

	class LibraryHandle
	{
	public:
		LibraryHandle(const boost::filesystem::path& plugin);
		~LibraryHandle();

		HMODULE get();

	private:
		HMODULE lib_;
	};
}}}
