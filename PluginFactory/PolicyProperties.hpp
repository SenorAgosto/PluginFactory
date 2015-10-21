#pragma once 

namespace PluginFactory {
    
    // This tag type indicates the Policy lives outside,
    // and a reference to it is passed in on construction.
    struct PolicyIsExternal {};
    
    // This tag type indicates the Policy lives inside (composition).
    // This is the preferred method for simple policies.
    struct PolicyIsInternal {};

}