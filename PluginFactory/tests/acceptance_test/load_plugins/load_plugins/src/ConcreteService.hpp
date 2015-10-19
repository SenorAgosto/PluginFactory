#pragma once 
#include <load_plugins/PluginServiceInterface.hpp>
#include <cstddef> 
#include <iostream>

namespace load_plugins {

    class ConcreteService : public PluginServiceInterface
    {
    public:
        ConcreteService()
            : barCalled_(0)
            , fooCalled_(0)
        {
        }
        
        void barCalled() override { barCalled_++; }
        void fooCalled() override { fooCalled_++; }
        
        void report() override
        {
            std::cout << barCalled_ << " " << fooCalled_ << std::endl;
        }
            
    private:
        std::size_t barCalled_;
        std::size_t fooCalled_;
    };
}
