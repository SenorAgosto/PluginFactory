#pragma once
#include <stdexcept>
#include <string>

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

    class PluginNotFoundException : public std::runtime_error
    {
    public:
        PluginNotFoundException(const std::string& pluginName);
    };
    
    class PluginLoaderException : public std::runtime_error
    {
    public:
        PluginLoaderException(const boost::filesystem::path& path, const std::string& message);
    };
    
    class PluginLoaderValidationException : public PluginLoaderException
    {
    public:
        PluginLoaderValidationException(const boost::filesystem::path& path, const std::string& message);
    };
 
    class PluginCreationMethodNotFoundInPluginCode : public PluginLoaderException
    {
    public:
        PluginCreationMethodNotFoundInPluginCode(const boost::filesystem::path& path);
    };    
}
