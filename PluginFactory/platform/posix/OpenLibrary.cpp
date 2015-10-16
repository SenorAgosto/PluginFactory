#include <PluginFactory/platform/posix/OpenLibrary.hpp>
#include <PluginFactory/Exceptions.hpp>

#include <boost/filesystem/path.hpp>
#include <dlfcn.h>

namespace PluginFactory { namespace details {

    void DlCloser::operator()(void* library)
    {
        if(library)
        {
            dlclose(library);
        }
    }
    
    std::unique_ptr<void, DlCloser> openLibrary(const boost::filesystem::path& plugin)
    {
        std::unique_ptr<void, DlCloser> lib(
            dlopen(plugin.string().c_str(), RTLD_NOW | RTLD_LOCAL), DlCloser());
        
        if(!lib)
        {
            throw PluginLoaderException(plugin, dlerror());
        }
        
        return lib;
    }
}}
