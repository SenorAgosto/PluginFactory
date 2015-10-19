#pragma once 

namespace load_plugins {

    class PluginServiceInterface
    {
    public:
        virtual ~PluginServiceInterface(){}
        
        virtual void barCalled() = 0;
        virtual void fooCalled() = 0;
        
        virtual void report() = 0;
    };
}
