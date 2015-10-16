#pragma once
#include <PluginFactory/details/NullPluginService.hpp>
#include <PluginFactory/details/PluginHandle.hpp>
#include <PluginFactory/details/PolicyHolder.hpp>
#include <PluginFactory/details/PluginLoader.hpp>
#include <PluginFactory/details/PolicyProperties.hpp>
#include <PluginFactory/Exceptions.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


namespace PluginFactory {

    // A tag type to indicate we want to create a std::shared_ptr of the plugin
    // rather than std::unique_ptr
    struct AsSharedTagType {};
    
    
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
    template<class PluginInterface, class PluginServiceInterface = details::NullPluginService, class PolicyOwnershipProperty = details::PolicyIsInternal>
    class PluginFactory : public details::PolicyHolder<PluginServiceInterface, PolicyOwnershipProperty>
    {
    public:
        static AsSharedTagType create_shared;
        
        // @pluginDirectory is the directory path to load plugins from.
        template<typename... Args>
        PluginFactory(const boost::filesystem::path& pluginDirectory, Args&&... args);
        
        void load();        // load all found plugins
        void load(const boost::filesystem::path& pluginPath);   // load a specific plugin (@pluginPath)
        
        void unload();      // unload all loaded plugins
        void unload(const boost::filesystem::path& pluginPath); // unload a specific plugin (@pluginPath)
        
        std::unique_ptr<PluginInterface> instance(const std::string& plugin);
        std::shared_ptr<PluginInterface> instance(const std::string& pluginName, AsSharedTagType /*create_shared*/);
        
        std::vector<std::string> availablePlugins() const;
        
    private:
        using PluginPath = std::string;
        using PluginInstanceMethod = std::function<PluginInterface* (PluginServiceInterface&)>;
        std::unordered_map<PluginPath, PluginHandle<PluginInterface, PluginServiceInterface>> plugins_;
        
        boost::filesystem::path pluginDirectory_;
        
        std::string pluginVersion_;
        std::string compilerToken_;
        std::string serviceVersion_;
    };
    
    
    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    template<typename... Args>
    PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::PluginFactory(const boost::filesystem::path& pluginDirectory, Args&&... args)
        : details::PolicyHolder<PluginServiceInterface, PolicyOwnershipProperty>(std::forward<Args>(args)...)
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
            // TODO: check each regular file's extension to see if it is the correct
            // extension for a shared lib on this platform.
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
            plugins_.emplace(pluginPath.string(), pluginHandle);
        }
        // TODO: make this exception more specific, we don't want to catch all of
        // e
        catch(const std::exception& e)
        {
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
    std::unique_ptr<PluginInterface> PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::instance(const std::string& pluginName)
    {
        std::unique_ptr<PluginInterface> p;
        
        auto iter = plugins_.find(pluginName);
        if(iter != plugins_.end())
        {
            auto& createPlugin = iter->second;
            p.reset(createPlugin(this->policy_));
        }
        
        return p;
    }
    
    template<class PluginInterface, class PluginServiceInterface, class PolicyOwnershipProperty>
    std::shared_ptr<PluginInterface> PluginFactory<PluginInterface, PluginServiceInterface, PolicyOwnershipProperty>::instance(const std::string& pluginName, AsSharedTagType)
    {
        std::shared_ptr<PluginInterface> p;
        
        auto iter = plugins_.find(pluginName);
        if(iter != plugins_.end())
        {
            auto& createPlugin = iter->second;
            p.reset(createPlugin(this->policy_));
        }

        return p;
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
