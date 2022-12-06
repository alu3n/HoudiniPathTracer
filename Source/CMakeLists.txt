cmake_minimum_required( VERSION 3.6 )

project( NPRG045 )


set(HFS /Applications/Houdini/Houdini19.5.353/Frameworks/Houdini.framework/Versions/Current/Resources)
set(CMAKE_PREFIX_PATH /Applications/Houdini/Houdini19.5.353/Frameworks/Houdini.framework/Versions/Current/Resources/toolkit/cmake)
#set( HFS $ENV{HFS} )
#set( CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH} )

list( APPEND CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" )

find_package( Houdini REQUIRED )

set( library_name HoudiniPathTracer )

#Todo: Break the project into multiple libraries to avoid linking problems

add_library( ${library_name} SHARED
    Core/Mathematics/sources/Sampling.cpp
    Core/Mathematics/sources/Coordinates.cpp
    Core/Mathematics/sources/LinearAlgebra.cpp

    Core/Physics/sources/Optics.cpp
    Core/Physics/sources/Radiometry.cpp

    Core/Materials/sources/PB_BxDF.cpp

    Core/Renderers/sources/ImageRepresentation.cpp
    Core/Renderers/sources/PhysicallyBasedRenderer.cpp

    Hook/Other/sources/RenderInterface.cpp
    Hook/Other/sources/RenderWindow.cpp

    Core/Materials/sources/BxDF.cpp
    Core/Materials/sources/Texture.cpp

    Core/Scene/sources/Camera.cpp
    Core/Scene/sources/Geometry.cpp
    Core/Scene/sources/Light.cpp
    Core/Scene/sources/Scene.cpp

    Hook/Other/sources/Utility.cpp
    Hook/Other/sources/Hook.cpp
    Hook/Nodes/sources/RendererNode.cpp
)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

houdini_configure_target( ${library_name} )
