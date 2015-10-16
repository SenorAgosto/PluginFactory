#pragma once

namespace PluginFactory { namespace details {
    
    class WindowsPluginLoader
    {
    public:
        PosixPluginLoader(const boost::filesystem::path& /*plugin*/){}
        
        void validateCompiler(const std::string& /*compilerToken*/){}
        void validatePluginVersion(const std::string& /*pluginVersion*/){}
        void validatePluginServiceVersion(const std::string& /*serviceVersion*/){}
        
        template<class PluginInterface, class PluginServiceInterface>
        PluginHandle<PluginInterface, PluginServiceInterface> getPluginHandle()
        {
            return PluginHandle<PluginInterface, PluginServiceInterface>();
        }
        
    private:
        HMODULE libraryHandle_;
    };
    
}}
