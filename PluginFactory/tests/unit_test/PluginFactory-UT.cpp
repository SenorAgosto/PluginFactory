#include "./platform/UnitTestSupport.hpp"

#include <PluginFactory/PluginFactory.hpp>
#include <PluginFactory/Exceptions.hpp>

#include <vector>

namespace {

    class PluginInterface
    {
    public:
        virtual ~PluginInterface(){}
        virtual void foo() = 0;
    };

    struct PluginFactoryFixture
    {
        using PluginFactory = PluginFactory::PluginFactory<PluginInterface>;
        
        PluginFactoryFixture()
            : factory("./")
        {
        }
        
        PluginFactory factory;
    };
    
    TEST_FIXTURE(PluginFactoryFixture, verifyPluginFactoryInstantiation)
    {
    }
    
    TEST(verifyPluginFactoryInstantiationThrowsOnPathDoesntExist)
    {
        CHECK_THROW(PluginFactory::PluginFactory<PluginInterface> factory("/ThisPath/Doesnt/Exist"), PluginFactory::PluginPathDoesntExist);
    }
    
    TEST(verifyPluginFactoryInstantiationThrowsOnAPathWhichIsntDirectory)
    {
        CHECK_THROW(PluginFactory::PluginFactory<PluginInterface> factory("./cmake_install.cmake"), PluginFactory::PluginPathIsntDirectory);
    }
    
    TEST_FIXTURE(PluginFactoryFixture, verifyLoad)
    {
        auto plugins = factory.availablePlugins();
        CHECK_EQUAL(2U, plugins.size());
    }
    
    TEST_FIXTURE(PluginFactoryFixture, verifyPluginFactoryUnload)
    {
        auto plugins = factory.availablePlugins();
        REQUIRE CHECK_EQUAL(2U, plugins.size());
        
        factory.unload();
        auto afterUnloadPlugins = factory.availablePlugins();
        
        CHECK_EQUAL(0U, afterUnloadPlugins.size());
    }
}
