#pragma once
#include <PluginFactory/Exceptions.hpp>
#include <PluginFactory/PolicyProperties.hpp>

#include <PluginFactory/details/NullPluginService.hpp>
#include <PluginFactory/details/PluginExtensionHelper.hpp>
#include <PluginFactory/details/PluginHandle.hpp>
#include <PluginFactory/details/PolicyHolder.hpp>
#include <PluginFactory/details/PluginLoader.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


namespace PluginFactory {

    // <PluginInterface> is the abstract interface of the plugin object itself. You'll need
    // a PluginFactory for each different type of plugin you wish to support.
    //
    // <PluginServiceInterface> is the interface given to the plugin to allow it to make
    // modifications to the main program. This is to encourage plugin developers not to
    // engage in crazy behavior like calling willy-nilly into the base process's code.
    //
    // NOTE: lifetime management using plugins can be difficult. It is essential
    // the PluginFactory stays in scope longer than any instanced plugin. Failure
    // to do so will most likely end in the process crashing.
    template<class PluginInterface, class PluginServiceInterface = details::NullPluginService, class PolicyOwnershipProperty = PolicyIsInternal>
    class PluginFactory : public details::PolicyHolder<PluginServiceInterface, PolicyOwnershipProperty>
    {
    public:
        // @pluginDirectory is the directory path to load plugins from.
        template<typename... Args>
        PluginFactory(const boost::filesystem::path& pluginDirectory, Args&&... pluginServiceArguments);
        
        void load();        // load all found plugins
        void load(const boost::filesystem::path& pluginPath);   // load a specific plugin (@pluginPath)
        
        void unload();      // unload all loaded plugins
        void unload(const boost::filesystem::path& pluginPath); // unload a specific plugin (@pluginPath)
        
        // You do not own this memory. The shared library owns this memory.
        PluginInterface* instance(const std::string& plugin);
        
        std::vector<std::string> availablePlugins() const;
        
    private:
        using PluginPath = std::string;
        std::unordered_map<PluginPath, details::PluginHandle<PluginInterface, PluginServiceInterface>> plugins_;
        
        boost::filesystem::path pluginDirectory_;
        
        std::string pluginVersion_;
        std::string compilerToken_;
        std::string serviceVersion_;
    };

    
    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    template<typename... Args>
    PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::PluginFactory(const boost::filesystem::path& pluginDirectory, Args&&... pluginServiceArguments)
        : details::PolicyHolder<PluginServiceInterface, PolicyOwnershipProperty>(std::forward<Args>(pluginServiceArguments)...)
        , pluginDirectory_(pluginDirectory)
    {
        if(!boost::filesystem::exists(pluginDirectory_))
        {
            throw PluginPathDoesntExist(pluginDirectory_);
        }
        
        if(!boost::filesystem::is_directory(pluginDirectory_))
        {
            throw PluginPathIsntDirectory(pluginDirectory_);
        }
    }
    
    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    void PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::load()
    {
        for(boost::filesystem::directory_iterator iter(pluginDirectory_), end; iter != end; ++iter)
        {
            const auto& path = iter->path();
            
            if(boost::filesystem::is_directory(path))
            {
                continue;
            }
            
            if(path.extension().string() == details::PluginExtensionHelper::extension())
            {
                load(path);
            }
        }
    }
    
    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    void PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::load(const boost::filesystem::path& pluginPath)
    {
        try
        {
            details::PluginLoader loader(pluginPath);

            loader.validateCompiler(compilerToken_);
            loader.validatePluginVersion(pluginVersion_);
            loader.validatePluginServiceVersion(serviceVersion_);
            
            auto pluginHandle = loader.getPluginHandle<PluginInterface, PluginServiceInterface>();
            plugins_.emplace(pluginPath.string(), std::move(pluginHandle));
        }
        catch(const PluginLoaderValidationException& )
        {
            // ... eat the exception
        }
    }
    
    
    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    void PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::unload()
    {
        plugins_.clear();
    }

    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    void PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::unload(const boost::filesystem::path& pluginPath)
    {
        auto iter = plugins_.find(pluginPath.string());
        if(iter != plugins_.end())
        {
            plugins_.erase(iter);
        }
    }

    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    PluginInterface* PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::instance(const std::string& pluginName)
    {
        auto iter = plugins_.find(pluginName);
        if(iter == plugins_.end())
        {
            throw PluginNotFoundException(pluginName);
        }
        
        auto& createPlugin = iter->second;
        return createPlugin(this->policy_);
    }
    
    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    std::vector<std::string> PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::availablePlugins() const
    {
        std::vector<std::string> plugins;
        plugins.reserve(plugins_.size());
        
        for(const auto& info : plugins_)
        {
            const auto& key = info.first;
            plugins.push_back(key);
        }
        
        return plugins;
    }
}
