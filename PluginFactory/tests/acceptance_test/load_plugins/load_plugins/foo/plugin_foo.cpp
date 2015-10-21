#include <load_plugins/PluginInterface.hpp>
#include <load_plugins/PluginServiceInterface.hpp>

#include <PluginFactory/MakePluginMethods.hpp>
#include <iostream>

namespace foo {
    
    // Plugin Bar will print "bar" to std::out,
    // and it will call PluginServiceInterface::barCalled()
    class FooPlugin : public load_plugins::MyPlugin
    {
    public:
        FooPlugin(void* service)
            : service_(static_cast<load_plugins::PluginServiceInterface*>(service))
        {
        }
        
        void do_stuff() override
        {
            std::cout << "foo" << std::endl;
            service_->fooCalled();
        }
        
    private:
        load_plugins::PluginServiceInterface * const service_;
    };
}

MAKE_PLUGIN_METHODS(load_plugins::MyPlugin, foo::FooPlugin)
