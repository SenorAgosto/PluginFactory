function(remove_ignored_paths_contained filtered_paths)
    # given a list of paths in PATHS
    # and a list of FILTER_DIRS 
    # return a list of paths not containing 
    # paths in FILTER_DIRS 
    cmake_parse_arguments(PARSED_ARGS "" "" "PATHS;FILTER_DIRS" ${ARGN})
    set(paths ${PARSED_ARGS_PATHS})
    set(filter_dirs ${PARSED_ARGS_FILTER_DIRS})

    unset(filtered)
    set(filtered "")
    
    foreach(path ${paths})
        foreach(filter ${filter_dirs})
            # regex for the filter path
            string(REGEX MATCH "${filter}" matched ${path})
            if(NOT matched)
                list(APPEND filtered ${path})
            else()
                # message("*** FILTERED: ${path} ****")
            endif()
        endforeach(filter)
    endforeach(path)
    
    set(${filtered_paths} ${filtered} PARENT_SCOPE)
endfunction(remove_ignored_paths)