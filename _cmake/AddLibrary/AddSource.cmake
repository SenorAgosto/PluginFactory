function(add_source BASE_DIR INSTALL_HEADER_FILES HEADER_FILES IMPLEMENTATION_FILES)

    # INSTALL_HEADER_FILES with the header files with relative paths.
    # HEADER_FILES with be header files with base directories.
    # IMPLEMENTATION_FILES will be implementation files with base directories.

	cmake_parse_arguments(PARSED_ARGS "" "" "HEADER_PATTERNS;SRC_PATTERNS;PATTERNS;FILTER_DIRS" ${ARGN})
	set(patterns ${PARSED_ARGS_PATTERNS})
	set(header_patterns ${PARSED_ARGS_HEADER_PATTERNS})
	set(src_patterns ${PARSED_ARGS_SRC_PATTERNS})
	set(filter_dirs ${PARSED_ARGS_FILTER_DIRS})

	# default patterns
	if(NOT patterns)
		list(APPEND patterns *.h *.hpp *.hxx *.hh *.H *.c *.C *.cc *.CC *.cxx *.cpp)
	endif()

	if(NOT header_patterns)
	    list(APPEND header_patterns *.h *.hpp *.hxx *.hh *.H)
	endif()
	
	if(NOT src_patterns)
	    list(APPEND src_patterns *.c *.C *.cc *.CC *.cxx *.cpp)
	endif() 
	
	file(GLOB_RECURSE source_files RELATIVE ${BASE_DIR} ${patterns})	
	filter_path_list(header_files SOURCES ${source_files} PATTERNS ${header_patterns})
	filter_path_list(implementation_files SOURCES ${source_files} PATTERNS ${src_patterns})
	
	remove_ignored_paths(header_files PATHS ${header_files} FILTER_DIRS ${filter_dirs} "platform")
	remove_ignored_paths(implementation_files PATHS ${implementation_files} FILTER_DIRS ${filter_dirs} "platform")
	remove_ignored_paths_regex(implementation_files PATHS ${implementation_files} FILTER_DIRS "platform")

	# determine platform and add platform folder contents
	determine_platform(platform)
	determine_platform_family(platform_family)

	if(EXISTS ${BASE_DIR}/src/platform/${platform})
		file(GLOB_RECURSE platform_sources RELATIVE ${BASE_DIR}/src/platform/${platform} ${src_patterns})
	endif()

	if(EXISTS ${BASE_DIR}/platform/${platform})
		file(GLOB_RECURSE platform_headers RELATIVE ${BASE_DIR}/platform/${platform} ${header_patterns})
	endif()

	if(EXISTS ${BASE_DIR}/platform/${platform_family})
		file(GLOB_RECURSE platform_family_headers RELATIVE ${BASE_DIR}/platform/${platform_family} ${header_patterns})
	endif()

	if(EXISTS ${BASE_DIR}/src/platform/${platform_family})
		file(GLOB_RECURSE platform_family_sources RELATIVE ${BASE_DIR}/src/platform/${platform_family} ${src_patterns})
	endif()

	remove_ignored_paths_regex(platform_headers PATHS ${platform_headers} FILTER_DIRS "\\.\\.")
	remove_ignored_paths_regex(platform_sources PATHS ${platform_sources} FILTER_DIRS "\\.\\.")
	remove_ignored_paths_regex(platform_family_headers PATHS ${platform_family_headers} FILTER_DIRS "\\.\\.")
	remove_ignored_paths_regex(platform_family_sources PATHS ${platform_family_sources} FILTER_DIRS "\\.\\.")

	# Setup Groups for Project Solutions
	unset(header_groups)
	foreach(header ${header_files})
		get_group(${header} "interface" header_group)
		list(APPEND header_group_${header_group} ${header})
		list(APPEND header_groups ${header_group})
	endforeach(header)

	foreach(header ${platform_headers})
		get_group("platform/${platform}/${header}" "interface" header_group)
		list(APPEND platform_header_group_${header_group} ${header})
		list(APPEND platform_header_groups ${header_group})
	endforeach(header)

	foreach(header ${platform_family_headers})
		get_group("platform/${platform_family}/${header}" "interface" header_group)
		list(APPEND platform_family_header_group_${header_group} ${header})
		list(APPEND platform_family_header_groups ${header_group})
	endforeach(header)

	# Setup Groups for Project Solutions
	unset(source_groups)
	foreach(source ${implementation_files})
		get_group(${source} "source" source_group)
		list(APPEND source_group_${source_group} ${source})
		list(APPEND source_groups ${source_group})
	endforeach(source)

	foreach(source ${platform_sources})
		get_group("src/platform/${platform}/${source}" "source" source_group)
		list(APPEND platform_source_group_${source_group} ${source})
		list(APPEND platform_source_groups ${source_group})
	endforeach(source)

	foreach(source ${platform_family_sources})
		get_group("src/platform/${platform_family}/${source}" "source" source_group)
		list(APPEND platform_family_source_group_${source_group} ${source})
		list(APPEND platform_family_source_groups ${source_group})
	endforeach(source)


	if(header_groups)
		list(REMOVE_DUPLICATES header_groups)
	endif()

	if(platform_header_groups)
		list(REMOVE_DUPLICATES platform_header_groups)
	endif()

	if(platform_family_header_groups)
		list(REMOVE_DUPLICATES platform_family_header_groups)
	endif()

	if(source_groups)
		list(REMOVE_DUPLICATES source_groups)
	endif()
	
	if(platform_source_groups)
		list(REMOVE_DUPLICATES platform_source_groups)
	endif()

	if(platform_family_source_groups)
		list(REMOVE_DUPLICATES platform_family_source_groups)
	endif()


	foreach(header_group ${header_groups})
		# add base_dir back to the paths
		add_base_dir(header_group_${header_group} PATHS ${header_group_${header_group}} BASE_DIR ${BASE_DIR})
		source_group(${header_group} FILES ${header_group_${header_group}})	
		unset(header_group_${header_group})
	endforeach(header_group)

	foreach(header_group ${platform_header_groups})
		add_base_dir(platform_header_group_${header_group} PATHS ${platform_header_group_${header_group}} BASE_DIR "${BASE_DIR}/platform/${platform}")
		source_group(${header_group} FILES ${platform_header_group_${header_group}})		
		unset(platform_header_group_${header_group})
	endforeach(header_group)

	foreach(header_group ${platform_family_header_groups})
		add_base_dir(platform_family_header_group_${header_group} PATHS ${platform_family_header_group_${header_group}} BASE_DIR "${BASE_DIR}/platform/${platform_family}")
		source_group(${header_group} FILES ${platform_family_header_group_${header_group}})
		unset(platform_family_header_group_${header_group})
	endforeach(header_group)


	foreach(source_group ${source_groups})	
		# add base_dir back to the paths
		add_base_dir(source_group_${source_group} PATHS ${source_group_${source_group}} BASE_DIR ${BASE_DIR})
		source_group(${source_group} FILES ${source_group_${source_group}})
		unset(source_group_${source_group})
	endforeach(source_group)

	foreach(source_group ${platform_source_groups})
		add_base_dir(platform_source_group_${source_group} PATHS ${platform_source_group_${source_group}} BASE_DIR "${BASE_DIR}/src/platform/${platform}")
		source_group(${source_group} FILES ${platform_source_group_${source_group}})
		unset(platform_source_group_${source_group})
	endforeach(source_group)

	foreach(source_group ${platform_family_source_groups})
		add_base_dir(platform_family_source_group_${source_group} PATHS ${platform_family_source_group_${source_group}} BASE_DIR "${BASE_DIR}/src/platform/${platform_family}")
		source_group(${source_group} FILES ${platform_family_source_group_${source_group}})
		unset(platform_family_source_group_${source_group})
	endforeach(source_group)


   	# add base_dir back to the paths.
    set(fullpath_header_files ${header_files})
	add_base_dir(header_files PATHS ${header_files} BASE_DIR ${BASE_DIR})
	add_base_dir(platform_headers PATHS ${platform_headers} BASE_DIR ${BASE_DIR}/platform/${platform})
	if(EXISTS ${BASE_DIR}/platform/${platform_family})
		add_base_dir(platform_family_headers PATHS ${platform_family_headers} BASE_DIR ${BASE_DIR}/platform/${platform_family})
	endif()

	add_base_dir(implementation_files PATHS ${implementation_files} BASE_DIR ${BASE_DIR})
	add_base_dir(platform_sources PATHS ${platform_sources} BASE_DIR ${BASE_DIR}/src/platform/${platform})
	if(EXISTS ${BASE_DIR}/src/platform/${platform_family})
		add_base_dir(platform_family_sources PATHS ${platform_family_sources} BASE_DIR ${BASE_DIR}/src/platform/${platform_family})
	endif()

	list(APPEND header_files ${platform_headers} ${platform_family_headers})
	list(APPEND implementation_files ${platform_sources} ${platform_family_sources})

	# return the found implementation files to the calling scope
	set(${IMPLEMENTATION_FILES} ${implementation_files} PARENT_SCOPE)
	set(${HEADER_FILES} ${header_files} PARENT_SCOPE)
    set(${INSTALL_HEADER_FILES} ${fullpath_header_files} PARENT_SCOPE)

endfunction(add_source)