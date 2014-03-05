# Kevin Wierman <kwierman@physics.unc.edu>
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Wiers)
#----------------------------------------------------------------------------
set(SOURCE_FOLDERS Common Math Elements Components )
set(SOURCE_HEADERS)
set(SOURCE_FILES)
#set(LIBRARY_LIST)
foreach( folder ${SOURCE_FOLDERS})
	#set(GRANULAR_LIBRARY "Tri${folder}" )
	message(STATUS "Configuring Library: " ${GRANULAR_LIBRARY})
	file(GLOB sources ${PROJECT_SOURCE_DIR}/${folder}/src/*.cxx )
	file(GLOB headers ${PROJECT_SOURCE_DIR}/${folder}/inc/*.h )
	include_directories(${PROJECT_SOURCE_DIR}/${folder}/inc/)
	foreach(source ${sources})
		list(APPEND SOURCE_FILES ${source})
	endforeach()
	foreach(header ${headers})
		list(APPEND SOURCE_HEADERS ${header})
	endforeach()	
endforeach()
#----------------------------------------------------------------------------
# Build Libraries
add_library(Wiers SHARED ${SOURCE_HEADERS} ${SOURCE_FILES}  )
set_target_properties(Wiers PROPERTIES LINKER_LANGUAGE CXX )
target_link_libraries(Wiers m)
install(TARGETS Wiers DESTINATION lib)
install(FILES ${headers} DESTINATION include)
#----------------------------------------------------------------------------
# Locate Executables, and link against all libraries
file(GLOB applications ${PROJECT_SOURCE_DIR}/Applications/*.cxx)
foreach(_app ${applications})
	     get_filename_component (name_without_extension ${_app} NAME_WE)
	     add_executable(${name_without_extension} ${_app} )#${sources} ${headers})
	     target_link_libraries(${name_without_extension}  Wiers m)
	     install(TARGETS ${name_without_extension} DESTINATION bin)
endforeach()
#----------------------------------------------------------------------------
# Add in Documentation
add_subdirectory(Documentation)
#----------------------------------------------------------------------------
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake") 
