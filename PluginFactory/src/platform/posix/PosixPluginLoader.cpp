#include <PluginFactory/platform/posix/PosixPluginLoader.hpp>

namespace PluginFactory { namespace platform { namespace posix {

    PosixPluginLoader::PosixPluginLoader(const boost::filesystem::path& plugin)
        : libraryHandle_(plugin)
        , path_(plugin)
    {
    }

    void PosixPluginLoader::validateCompiler(const std::string& /*compilerToken*/){}
    void PosixPluginLoader::validatePluginVersion(const std::string& /*pluginVersion*/){}
    void PosixPluginLoader::validatePluginServiceVersion(const std::string& /*serviceVersion*/){}

}}}