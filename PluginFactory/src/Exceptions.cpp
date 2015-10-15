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
}
