cmake_minimum_required(VERSION 2.8)
Project("load_plugins")

# suppress warnings about not setting rpath
if(APPLE)
  if(UNIX)
    cmake_policy(SET CMP0042 OLD)
  endif()
endif() 

include_directories(".")

# create two shared libs
file(GLOB foo_src ${CMAKE_CURRENT_SOURCE_DIR}/load_plugins/foo/*)
add_library(plugin_foo SHARED ${foo_src})

file(GLOB bar_src ${CMAKE_CURRENT_SOURCE_DIR}/load_plugins/bar/*)
add_library(plugin_bar SHARED ${bar_src})

# create one executable
file(GLOB load_plugins_src 
	${CMAKE_CURRENT_SOURCE_DIR}/load_plugins/src/*
	${CMAKE_CURRENT_SOURCE_DIR}/load_plugins/*)
add_executable(load_plugins ${load_plugins_src})
add_dependencies(PluginFactory plugin_foo plugin_bar) 
target_link_libraries(load_plugins PluginFactory ${Boost_LIBRARIES} ${DL_LIBRARIES})

if(POSIX)
    set_property(TARGET plugin_foo PROPERTY COMPILE_FLAGS --export-dynamic)
    set_property(TARGET plugin_bar PROPERTY COMPILE_FLAGS --export-dynamic)
endif()

