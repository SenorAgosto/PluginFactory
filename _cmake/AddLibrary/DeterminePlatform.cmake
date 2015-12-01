# A function for turning CMAKE_SYSTEM_NAME into 
# our prefered system names.
function(determine_platform system)

    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    	set(${system} "macosx" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    	set(${system} "linux" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    	set(${system} "freebsd" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    	set(${system} "win32" PARENT_SCOPE)
    endif()

    if(${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")
    	set(${system} "openbsd" PARENT_SCOPE)
    endif()

endfunction(determine_platform)