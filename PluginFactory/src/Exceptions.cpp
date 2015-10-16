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
    
    PluginLoaderValidationException::PluginLoaderValidationException(const std::string& message)
        : std::runtime_error(message)
    {
    }
}
