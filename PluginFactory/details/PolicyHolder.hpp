#pragma once 
#include <PluginFactory/details/PolicyProperties.hpp>
#include <utility>

namespace PluginFactory { namespace details {
    
    // Composition helper class template
    template<class Policy>
    struct PolicyComposition
    {
        template<typename... Args>
        PolicyComposition(Args&&... args)
            : policy_(std::forward<Args>(args)...)
        {
        }
        
        Policy policy_;
    };
    
    // Reference helper class template
    template<class Policy>
    struct PolicyReference
    {
        template<typename... Args>
        PolicyReference(Policy& policy, Args&&... /*ignored*/)
            : policy_(policy)
        {
        }
        
        Policy& policy_;
    };
    
    // The purpose of this class is to allow another
    // class template to hold a template parameter as
    // either a ref or a internal variable - the choice
    // is controllable via the tag types defined above.
    //
    // Primary class template definition.
    template<class Policy, class PolicyProperty>
    struct PolicyHolder : public PolicyComposition<Policy>
    {
        template<typename... Args>
        PolicyHolder(Args&&... args)
            : PolicyComposition<Policy>(std::forward<Args>(args)...)
        {
        }
    };
    
    // a specialization of PolicyHolder for holding the policy by reference.
    template<class Policy>
    struct PolicyHolder<Policy, PolicyIsExternal> : public PolicyReference<Policy>
    {
        template<typename... Args>
        PolicyHolder(Args&&... args)
            : PolicyReference<Policy>(std::forward<Args>(args)...)
        {
        }
    };
    
}}
