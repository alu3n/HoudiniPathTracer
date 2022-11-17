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
        Core/Mathematics/source/Sampling.cpp
        Core/Mathematics/source/Coordinates.cpp
    Core/Physics/Sources/GeometricalOptics.cpp
    Core/Physics/Sources

        #    Core/Physics/source/OldQuantities.cpp

#    Core/Renderers/source/OldDistributedRaytracer.cpp
#    Core/Renderers/source/OldPathTracer.cpp
#    Core/Renderers/source/OldRenderer.cpp
    Core/Renderers/Sources/ImageRepresentation.cpp
    Core/Renderers/Sources/PhysicallyBasedRenderer.cpp

    Interface/Sources/RenderInterface.cpp
    Interface/Sources/RenderWindow.cpp

#    Core/Materials/source/LambertBRDF.cpp

    Core/Materials/Sources/BRDF.cpp
        Core/Materials/Sources/Texture.cpp

    Core/Scene/Sources/Camera.cpp
    Core/Scene/Sources/Geometry.cpp
    Core/Scene/Sources/Light.cpp
    Core/Scene/Sources/Scene.cpp

        Hook/Other/Sources/Utility.cpp
        Hook/Nodes/Sources/LightNode.cpp
        Hook/Nodes/Sources/CameraNode.cpp
        Hook/Nodes/Sources/DebugNode.cpp
        Hook/Other/Sources/Hook.cpp
        Hook/Nodes/Sources/RendererNode.cpp
)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

houdini_configure_target( ${library_name} )
