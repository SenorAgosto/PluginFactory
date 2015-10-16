#pragma once 
#include <memory>

namespace boost { namespace filesystem {
    class path;
}}

namespace PluginFactory { namespace details {

    struct DlCloser
    {
        void operator()(void* library);
    };

    std::unique_ptr<void, DlCloser> openLibrary(const boost::filesystem::path& plugin);
}}
