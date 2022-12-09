cmake_minimum_required( VERSION 3.6 )

project( NPRG045 )


# IDE might not be able to load the CMake project without those variables set!
set(HFS /Applications/Houdini/Houdini19.5.353/Frameworks/Houdini.framework/Versions/Current/Resources)
set(CMAKE_PREFIX_PATH /Applications/Houdini/Houdini19.5.353/Frameworks/Houdini.framework/Versions/Current/Resources/toolkit/cmake)

list( APPEND CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" )

find_package( Houdini REQUIRED )

set( library_name HoudiniPathTracer )


add_library( ${library_name} SHARED
    Core/Mathematics/sources/Sampling.cpp
    Core/Mathematics/sources/Coordinates.cpp
    Core/Mathematics/sources/LinearAlgebra.cpp

    Core/Physics/sources/Optics.cpp
    Core/Physics/sources/Units.cpp

    Core/Renderers/sources/ImageRepresentation.cpp
    Core/Renderers/sources/PhysicallyBasedRenderer.cpp

    Hook/Other/sources/RenderInterface.cpp
    Hook/Other/sources/RenderWindow.cpp

    Core/Materials/sources/BxDF.cpp
    Core/Materials/sources/MaterialLibrary.cpp
    Core/Materials/sources/Material.cpp

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

set_property(TARGET HoudiniPathTracer PROPERTY CXX_STANDARD 17)

houdini_configure_target( ${library_name} )
