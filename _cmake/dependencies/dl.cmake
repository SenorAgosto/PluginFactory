if(UNIX)
    find_package(dl REQUIRED)    
    include_directories(${dl_INCLUDE_DIR})
endif()

if(POSIX)
    find_package(dl REQUIRED)
    include_directories(${dl_INCLUDE_DIR})
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(dl REQUIRED)
    include_directories(${dl_INCLUDE_DIR})
endif()

