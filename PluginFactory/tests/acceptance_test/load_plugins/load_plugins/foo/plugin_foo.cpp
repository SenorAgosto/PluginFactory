#include <load_plugins/PluginInterface.hpp>
#include <load_plugins/PluginServiceInterface.hpp>

#include <iostream>

namespace foo {
    
    // Plugin Bar will print "bar" to std::out,
    // and it will call PluginServiceInterface::barCalled()
    class FooPlugin : public load_plugins::MyPlugin
    {
    public:
        FooPlugin(load_plugins::PluginServiceInterface& service)
            : service_(service)
        {
        }
        
        void do_stuff() override
        {
            std::cout << "foo" << std::endl;
            service_.fooCalled();
        }
        
    private:
        load_plugins::PluginServiceInterface& service_;
    };
    
}

// NOTE: generally speaking it is good advice that memory shouldn't pass the process/shared-lib
// boundary because they may have been compiled with different allocators.
//
// We're going to ignore that advice and instead REQUIRE the plugins to be compiled
// with the same settings as the main process. It greatly simplifies working with
// the shared libs.
load_plugins::MyPlugin* createPlugin(load_plugins::PluginServiceInterface& service)
{
    return new foo::FooPlugin(service);
}
