#pragma once 

namespace PluginFactory { namespace details {

    // a function with proper signature to be used by PluginDeleter,
    // but that doesn't do anything.
    void null_deleter(void*);

}}
