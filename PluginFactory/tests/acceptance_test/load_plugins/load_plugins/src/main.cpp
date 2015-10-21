#include <PluginFactory/PluginFactory.hpp>
#include <PluginFactory/details/PolicyProperties.hpp>

#include <load_plugins/PluginInterface.hpp>
#include <load_plugins/PluginServiceInterface.hpp>

#include "ConcreteService.hpp"

#include <iostream>
#include <memory> 

using MyPlugin = load_plugins::MyPlugin*;
using MyPluginFactory = PluginFactory::PluginFactory<load_plugins::MyPlugin, load_plugins::PluginServiceInterface, PluginFactory::details::PolicyIsExternal>;

int usage(char const * const programName);
int run(int argc, char** argv);

void printPluginNames(const std::vector<std::string>& plugins);
void createPlugins(MyPluginFactory& factory, const std::vector<std::string>& availablePlugins, std::deque<MyPlugin>& plugins);
void callPlugins(const std::deque<MyPlugin>& plugins);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        return usage(argv[0]);
    }
    
    try
    {
        return run(argc, argv);
    }
    catch(const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
    
    return -1;
}

int usage(char const * const programName)
{
    std::cerr << "Usage: " << programName << " <plugin_path>" << std::endl;
    return -1;
}

int run(int /*argc*/, char** argv)
{
    std::string pluginPath(argv[1]);
    std::deque<MyPlugin> plugins;
    
    std::unique_ptr<load_plugins::PluginServiceInterface> service(new load_plugins::ConcreteService());
    MyPluginFactory factory(pluginPath, *service);
    factory.load();
    
    auto availablePlugins = factory.availablePlugins();
    printPluginNames(availablePlugins);
    createPlugins(factory, availablePlugins, plugins);
    
    callPlugins(plugins);
    service->report();
    
    return 0;
}

void printPluginNames(const std::vector<std::string>& plugins)
{
    std::cout << "loaded: ";
    for(const auto& pluginName : plugins)
    {
        std::cout << pluginName << " ";
    }
    std::cout << std::endl;
}

void createPlugins(MyPluginFactory& factory, const std::vector<std::string>& availablePlugins, std::deque<MyPlugin>& plugins)
{
    for(const auto& pluginName : availablePlugins)
    {
        plugins.emplace_back(factory.instance(pluginName));
    }
}

void callPlugins(const std::deque<MyPlugin>& plugins)
{
    for(auto& plugin : plugins)
    {
        plugin->do_stuff();
    }
}


