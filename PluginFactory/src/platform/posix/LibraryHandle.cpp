#include <PluginFactory/platform/posix/LibraryHandle.hpp>
#include <PluginFactory/Exceptions.hpp>

#include <boost/filesystem/path.hpp>
#include <dlfcn.h>

namespace PluginFactory { namespace platform { namespace posix {

    void DlCloser::operator()(void* library)
    {
        if(library)
        {
            dlclose(library);
        }
    }
    
    LibraryHandle::LibraryHandle(const boost::filesystem::path& plugin)
        : lib_(dlopen(plugin.string().c_str(), RTLD_NOW | RTLD_LOCAL), DlCloser())
    {
        if(!lib_)
        {
            throw PluginLoaderException(plugin, dlerror());
        }
    }

    void* LibraryHandle::get()
    {
        return lib_.get();
    }
}}}
