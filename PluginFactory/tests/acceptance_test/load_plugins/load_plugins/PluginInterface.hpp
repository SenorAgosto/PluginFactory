#pragma once 

namespace load_plugins {

    class MyPlugin
    {
    public:
        virtual ~MyPlugin(){}
        virtual void do_stuff() = 0;
    };
}
