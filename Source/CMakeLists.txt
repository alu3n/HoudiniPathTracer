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
    Core/Mathematics/Sources/Sampling.cpp
    Core/Mathematics/Sources/Coordinates.cpp
    Core/Physics/Sources/GeometricalOptics.cpp
    Core/Physics/Sources

        #    Core/Physics/Sources/OldQuantities.cpp

#    Core/Renderers/Sources/OldDistributedRaytracer.cpp
#    Core/Renderers/Sources/OldPathTracer.cpp
#    Core/Renderers/Sources/OldRenderer.cpp
    Core/Renderers/Sources/ImageRepresentation.cpp
    Core/Renderers/Sources/PhysicallyBasedRenderer.cpp


    Core/Scene/Sources/Camera.cpp
    Core/Scene/Sources/Geometry.cpp
    Core/Scene/Sources/Light.cpp
    Core/Scene/Sources/Scene.cpp
#    Core/Materials/Sources/LambertBRDF.cpp

    Interface/Sources/RenderInterface.cpp
    Interface/Sources/RenderWindow.cpp

    HoudiniHook/Utility.cpp
    HoudiniHook/LightNode.cpp
    HoudiniHook/CameraNode.cpp
    HoudiniHook/DebugNode.cpp
    HoudiniHook/Hook.cpp
    HoudiniHook/RendererNode.cpp
)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

houdini_configure_target( ${library_name} )
