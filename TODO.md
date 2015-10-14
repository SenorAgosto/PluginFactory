# TODO

- implement framework for loading and instantiating c++ plugins. 
- implement abstract factory over DLLs
	- each DLL encapsulates a plugin interface
	- each DLL will have an instantiate method for instantiating the 
 		concrete implementation of the plugin. 
	- each instantiate_plugin() method will take a reference to the PluginFactory as an argument. The PluginFactory can provide alternative services to the plugin as the client code determines necessary (e.g. providing configuration information).  

