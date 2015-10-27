#pragma once 

// We need help from the build system to set these...
// Currently, only supporting the big 3

#ifdef MACOSX
#define BUILD_TRAITS_PLATFORM Platform::macosx 
#endif 

#ifdef LINUX 
#define BUILD_TRAITS_PLATFORM Platform::linux
#endif

#ifdef WIN32
#define BUILD_TRAITS_PLATFORM Platform::windows
#endif

