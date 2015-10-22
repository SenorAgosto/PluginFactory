# PluginFactory

A small interface-driven toolkit for adding plugins to C++ applications. 

### Quick Tour

The following code snippet shows how to use the PluginFactory.

    PluginFactory::PluginFactory<MyPluginInterface, MyAppInterface> factory("plugins/");
    
    factory.load();

    // store for instantiated plugin pointers,
    // the ownership of the pointers resides with 
    // the shared library, not the parent process.
    using MyPlugin = MyPluginInterface*;
    std::deque<MyPlugin> plugins;

    // list all available plugins
    auto availablePlugins = factory.availablePlugins();

    // instantiate all available plugins
    for(const auto& pluginName : availablePlugins)
    {
    	plugins.push_back(factory.instance(pluginName));
    }

    // invoke MyPluginInterface::foo() on all loaded plugins
    for(auto& plugin : plugins)
    {
    	plugin->foo();
    }

#### Creating a plugin

PluginFactory plugins are concrete implementatinos of a C++ abstract interface. Interactions with the plugin from the main program happen through this interface. Let's define a simple plugin interface to use with our example plugin.

    namespace plugin_example {

        class PluginInterface
        {
        public:
            virtual ~PluginInterface(){}

            virtual void do_stuff() = 0;
        };
    }

When creating concrete plugins, we can provide an interface to them so they can affect change in the main process. This interface is refered to as the `PluginServiceInterface`. 

    namespace plugin_example {

        class PluginService 
        {
        public:
            virtual ~PluginService(){}
            virtual pluginCalled(char const * const name) = 0;
        };
    }

Providing this interface is _not_ required, the default is a null interface that does nothing. Whether or not the service interface is desired, because plugins reside in shared libraries, we have to take the service interface as a `void*` in the constructor.  

Let's implement a concrete plugin implementing the plugin_example::PluginInterface example. 

    #include <PluginFactory/MakePluginMethods.hpp>

    namespace MyPlugin {

        class MyPlugin : public plugin_example::PluginInterface
        {
        public:
            MyPlugin(void* pluginService)
                : pluginService_(static_cast<plugin_example::PluginService*>(pluginService))
            {
            }

            void do_stuff() override 
            {
                std::cout << "I'm a plugin!!" << std::endl;
                pluginService_->pluginCalled("MyPlugin");
            }

        private:
            plugin_example::PluginService* pluginService_;
        };
    }

    // use a helper macro to define required creation methods in our shared 
    // library.
    MAKE_PLUGIN_METHODS(plugin_example::PluginInterface, MyPlugin::MyPlugin)

Then somewhere in the main process, we would use the PluginFactory to load the plugin and interact with it. In this case, the plugin factory declaration would look like `PluginFactory::PluginFactory<plugin_example::MyPlugin, plugin_example::PluginService>`.

See PluginFactory/tests/acceptance_test/load_plugin for example code.

#### Compiling your plugin on POSIX 

On POSIX systems, you'll most likely have to supply linker arguments to get the symbols in your shared library exported. (e.g. GCC on Linux and clang on Mac support the --export-dynamic to export symbols.)

#### Compiling your plugin on Windows 

On Windows, you'll need to use a compiler intrinsic attribute to indicate which symbols you want exported. 

    __declspec(dllexport) MyPlugin* createPlugin(PluginServiceInterface&);

### Dependencies 

- c++11
- [boost](http://boost.org). Uses boost::filesystem::path.

Used for unit testing on all platforms:

- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp). Unit test framework.

Windows Platforms:

- Visual Leak Detector (VLD). Used on windows to detect memory leaks in unit tests)

### Contributors 

Austin Gilbert <ceretullis@gmail.com>

### License

4-Clause BSD license, see [LICENSE.md](LICENSE.md) for details. Other licensing available upon request. 

### Related Projects 

- plexx
- [CPF](http://sourceforge.net/projects/cpp-plugin/)
- [3xc](https://github.com/rhcad/x3c)
- Qt provides plugin capabilities as well
