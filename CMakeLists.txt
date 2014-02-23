# Kevin Wierman <kwierman@physics.unc.edu>
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Wiers)
#----------------------------------------------------------------------------
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cxx)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.h)
#----------------------------------------------------------------------------
# Build Libraries
include_directories(${PROJECT_SOURCE_DIR}/inc)
add_library(Wiers SHARED ${sources} ${headers} )
set_target_properties(Wiers PROPERTIES LINKER_LANGUAGE CXX )
target_link_libraries(Wiers)
install(TARGETS Wiers DESTINATION lib)
install(FILES ${headers} DESTINATION include)
#----------------------------------------------------------------------------
# Locate Executables, and link against all libraries
file(GLOB applications ${PROJECT_SOURCE_DIR}/Applications/*.cxx)
foreach(_app ${applications})
	     get_filename_component (name_without_extension ${_app} NAME_WE)
	     add_executable(${name_without_extension} ${_app} )#${sources} ${headers})
	     target_link_libraries(${name_without_extension}  Wiers)
	     install(TARGETS ${name_without_extension} DESTINATION bin)
endforeach()
#----------------------------------------------------------------------------
# Add in Documentation
add_subdirectory(Documentation)
#----------------------------------------------------------------------------
