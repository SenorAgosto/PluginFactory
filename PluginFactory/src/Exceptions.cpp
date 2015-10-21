#include <PluginFactory/Exceptions.hpp>
#include <boost/filesystem/path.hpp>

namespace PluginFactory {

    PluginPathDoesntExist::PluginPathDoesntExist(const boost::filesystem::path& path)
        : std::runtime_error("Plugin Path '" + path.string() + "' does not exist")
    {
    }
    
    PluginPathIsntDirectory::PluginPathIsntDirectory(const boost::filesystem::path& path)
        : std::runtime_error("Plugin Path '" + path.string() + "' isn't directory")
    {
    }
    
    PluginLoaderException::PluginLoaderException(const boost::filesystem::path& path, const std::string& message)
        : std::runtime_error("Plugin (" + path.string() + ") failed to load : " + message)
    {
    }

    PluginLoaderValidationException::PluginLoaderValidationException(const boost::filesystem::path& path, const std::string& message)
        : PluginLoaderException(path, message)
    {
    }
    
    PluginCreationMethodNotFoundInPluginCode::PluginCreationMethodNotFoundInPluginCode(const boost::filesystem::path& path)
        : PluginLoaderException(path, "Symbol 'createPlugin' not found in plugin library.")
    {
    }
    
    PluginDeletionMethodNotFoundInPluginCode::PluginDeletionMethodNotFoundInPluginCode(const boost::filesystem::path& path)
        : PluginLoaderException(path, "Symbol 'deletePlugin' not found in plugin library.")
    {
    }
}
