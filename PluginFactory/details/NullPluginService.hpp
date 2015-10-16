#pragma once

namespace PluginFactory { namespace details {

    class NullPluginService
    {
    public:
        
        template<typename... Args>
        NullPluginService(Args&&... /*ignored*/)
        {
        }
    };
}}
