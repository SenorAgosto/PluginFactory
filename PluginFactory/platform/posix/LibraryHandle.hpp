#pragma once 
#include <memory>

namespace boost { namespace filesystem {
    class path;
}}

namespace PluginFactory { namespace platform { namespace posix {

    // calls dlclose on the library if not null.
    struct DlCloser
    {
        void operator()(void* library);
    };


    // Helper class to hold a library handle loaded with a call to dlopen()
    // on destruction of LibraryHandle, dlclose() is called on the handle.
    class LibraryHandle
    {
    public:
        LibraryHandle(const boost::filesystem::path& pluginPath);
        void* get();
        
    private:
        std::unique_ptr<void, DlCloser> lib_;
    };

}}}
