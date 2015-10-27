# Try to find UnitTest++
# Once done this will define
# dl_FOUND - system has the lib 
# dl_INCLUDE_DIRS - the path to include directory 
# dl_LIBRARIES - the libraries needed to use
# dl_DEFINITIONS - compiler switches required for using UnitTest++

find_package(PkgConfig)
pkg_check_modules(PC_DL QUIET libdl)
set(UNITTEST++_DEFINITIONS ${PC_DL_CFLAGS_OTHER})

# see if there is a brew path (useful when it is not /usr/local/)
set(PC_HOMEBREW_PATH $ENV{HOMEBREW})
if(PC_HOMEBREW_PATH)
    set(PC_HOMEBREW_INCLUDE_DIRS "$ENV{HOMEBREW}/include")
    set(PC_HOMEBREW_LIBRARY_DIRS "$ENV{HOMEBREW}/lib")
endif()

find_path(DL_INCLUDE_DIR dlfcn.h 
    HINTS ${PC_DL_INCLUDEDIR} ${PC_DL_INCLUDE_DIRS} ${PC_HOMEBREW_INCLUDE_DIRS} /usr/include /usr/local/include
    PATH_SUFFIXES dl )

find_library(DL_LIBRARY NAMES dl libdl
    HINTS ${PC_DL_LIBDIR} ${PC_DL_LIBRARY_DIRS} ${PC_HOMEBREW_LIBRARY_DIRS} )

set(DL_LIBRARIES ${DL_LIBRARY} )
set(DL_INCLUDE_DIRS ${DL_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs) 
find_package_handle_standard_args(DL DEFAULT_MSG
    DL_LIBRARY DL_INCLUDE_DIR)

mark_as_advanced(DL_INCLUDE_DIR DL_LIBRARY)
 
