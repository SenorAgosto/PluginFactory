# A function for turning CMAKE_SYSTEM_NAME into 
# our prefered system family names.
function(determine_platform_family system)

    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    	set(${system} "posix" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    	set(${system} "posix" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    	set(${system} "posix" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    	set(${system} "win32" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")
    	set(${system} "posix" PARENT_SCOPE)
    endif()

endfunction(determine_platform_family)