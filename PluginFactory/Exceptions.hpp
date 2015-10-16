#pragma once
#include <stdexcept>

namespace boost { namespace filesystem {
    class path;
}}

namespace PluginFactory {

    class PluginPathDoesntExist : public std::runtime_error
    {
    public:
        PluginPathDoesntExist(const boost::filesystem::path& path);
    };
    
    class PluginPathIsntDirectory : public std::runtime_error
    {
    public:
        PluginPathIsntDirectory(const boost::filesystem::path& path);
    };
    
    class PluginLoaderValidationException : public std::runtime_error
    {
    public:
        PluginLoaderValidationException(const std::string& message);
    };
}
