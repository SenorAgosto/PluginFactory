# PluginFactory notes

PluginFactory should take a path in its constructor, this is the path used to locate & load plugins.

Interface:

- load()
- unload()

- load(pluginPath)
- unload(pluginPath)

- interface instance(std::string implementationName)
- std::unique_ptr<interface> instance(std::string implementationName, on_heap)

- std::vector<std::string> availablePlugins() const 


Load() will load all new plugins from the plugins directory. Each plugin will be instantiated and registered with the PluginFactory. Access to the plugin will be obtained through the instance() method.

Plugins will be unloaded at deconstruction of PluginFactory. 

# Compiling Plugins 

## Linux

Plugins need to be compiled with the linker option `-Xlinker -Bsymbolic` to prevent routing issues (redirecting calls with same name into the owning process)

# Loading Plugin Libraries and Resolving Method Addresses

## POSIX

Plugin libraries can be loaded using [dlopen](http://linux.die.net/man/3/dlopen). We recommend using the flags RTLD_NOW and RTLD_LOCAL.

The RTLD_NOW flag instructs the loader to fully resolve all symbols contained in the plugin library or return an error. 

The RTLD_LOCAL flag instructs the loader to prevent symbols in the loaded library from being used to resolve symbols in libs loaded later on. All plugins should be indepentent of each other. If they need to share dependencies those should be pushed to a shared lib.

## Windows

Plugin libraries can be loaded using [LoadLibrary](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684175(v=vs.85).aspx), which returns a handle. 

Resources in the library can be located using [GetProcAddress](https://msdn.microsoft.com/en-us/library/windows/desktop/ms683212(v=vs.85).aspx)

