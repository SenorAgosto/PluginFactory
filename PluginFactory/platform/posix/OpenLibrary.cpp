#include <PluginFactory/platform/posix/OpenLibrary.hpp>
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
    
    LibraryHandle openLibrary(const boost::filesystem::path& plugin)
    {
        LibraryHandle lib(dlopen(plugin.string().c_str(), RTLD_NOW | RTLD_LOCAL), DlCloser());
        
        if(!lib)
        {
            throw PluginLoaderException(plugin, dlerror());
        }
        
        return lib;
    }
}}}
