#pragma once
#include <stdexcept>

namespace boost { namespace filesystem {
    class path;
}}

namespace PluginFactory {

    class PluginDirectoryDoesntExist : public std::runtime_error
    {
    public:
        PluginDirectoryDoesntExist(const boost::filesystem::path& path);
    };
    
    class PluginPathIsntDirectory : public std::runtime_error
    {
    public:
        PluginPathIsntDirectory(const boost::filesystem::path& path);
    };
}
