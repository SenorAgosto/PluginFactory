# Try to find BuildTraits
# Once done this will define
# BuildTraits_FOUND - system has the lib 
# BuildTraits_INCLUDE_DIRS - the path to include directory 
# BuildTraits_LIBRARIES - the libraries needed to use
# BuildTraits_DEFINITIONS - compiler switches required for using BuildTraits

find_package(PkgConfig)
pkg_check_modules(PC_BuildTraits QUIET libBuildTraits)
set(BuildTraits_DEFINITIONS ${PC_BuildTraits_CFLAGS_OTHER})

# see if there is a brew path (useful when it is not /usr/local/)
set(PC_HOMEBREW_PATH $ENV{HOMEBREW})
if(PC_HOMEBREW_PATH)
    set(PC_HOMEBREW_INCLUDE_DIRS "$ENV{HOMEBREW}/include")
    set(PC_HOMEBREW_LIBRARY_DIRS "$ENV{HOMEBREW}/lib")
endif()

find_path(BuildTraits_INCLUDE_DIR build_traits/build_traits.hpp
    HINTS ${PC_BuildTraits_INCLUDEDIR} ${PC_BuildTraits_INCLUDE_DIRS} ${PC_HOMEBREW_INCLUDE_DIRS} /usr/include /usr/local/include
    PATH_SUFFIXES build_traits )

find_library(BuildTraits_LIBRARY NAMES build_traits libbuild_traits
    HINTS ${PC_BuildTraits_LIBDIR} ${PC_BuildTraits_LIBRARY_DIRS} ${PC_HOMEBREW_LIBRARY_DIRS} )

set(BuildTraits_LIBRARIES ${BuildTraits_LIBRARY} )
set(BuildTraits_INCLUDE_DIRS ${BuildTraits_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs) 
find_package_handle_standard_args(BuildTraits DEFAULT_MSG
    BuildTraits_LIBRARY BuildTraits_INCLUDE_DIR)

mark_as_advanced(BuildTraits_INCLUDE_DIR BuildTraits_LIBRARY)
 
