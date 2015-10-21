#pragma once 
#include <PluginFactory/details/NullDeleter.hpp>

namespace PluginFactory {

    template<class PluginInterface>
    class PluginDeleter
    {
    public:
        using PluginDeletionMethod = void (*)(void*);

        PluginDeleter() noexcept;
        PluginDeleter(PluginDeletionMethod pluginDeleter) noexcept;
        ~PluginDeleter() noexcept;
        
        PluginDeleter(const PluginDeleter& other) noexcept;
        
        void operator()(PluginInterface* interface);
        
    private:
        PluginDeletionMethod pluginDeleter_;
    };
    

    template<class PluginInterface>
    PluginDeleter<PluginInterface>::PluginDeleter() noexcept
        : pluginDeleter_(details::null_deleter)
    {
    }
    
    template<class PluginInterface>
    PluginDeleter<PluginInterface>::PluginDeleter(PluginDeletionMethod pluginDeleter) noexcept
        : pluginDeleter_(pluginDeleter)
    {
    }
  
    template<class PluginInterface>
    PluginDeleter<PluginInterface>::PluginDeleter(const PluginDeleter& other) noexcept
        : pluginDeleter_(other.pluginDeleter_)
    {
    }

    template<class PluginInterface>
    PluginDeleter<PluginInterface>::~PluginDeleter() noexcept
    {
    }

    template<class PluginInterface>
    void PluginDeleter<PluginInterface>::operator()(PluginInterface* interface)
    {
        if(interface)
        {
            pluginDeleter_(interface);
        }
    }
}
