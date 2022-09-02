cmake_minimum_required( VERSION 3.6 )

project( NPRG045 )

# TODO: Set env variables locally, give user instructions to do the same

set( HFS /Applications/Houdini/Houdini19.5.353/Frameworks/Houdini.framework/Versions/Current/Resources)
set( CMAKE_PREFIX_PATH /Applications/Houdini/Houdini19.5.353/Frameworks/Houdini.framework/Versions/Current/Resources/toolkit/cmake)

list( APPEND CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" )

find_package( Houdini REQUIRED )

set( library_name HoudiniPathTracer )

add_library( ${library_name} SHARED
    HoudiniHook/Hook.cpp
    HoudiniHook/Hook.hpp
)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

houdini_configure_target( ${library_name} )
