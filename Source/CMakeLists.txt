cmake_minimum_required( VERSION 3.6 )

project( NPRG045 )

set( HFS $ENV{HFS} )
set( CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH} )

list( APPEND CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" )

find_package( Houdini REQUIRED )

set( library_name HoudiniPathTracer )

#Todo: Break the project into multiple libraries to avoid linking problems

add_library( ${library_name} SHARED
        oldCore/SceneComponents/Camera.cpp
#    oldCore/oldRenderer.cpp
        oldCore/RenderEngine.cpp
        oldCore/SceneComponents/Light.cpp
        oldCore/BRDF/old_PrincipledShader.cpp
        oldCore/WhittedRayTracer/WhittedRayTracer.cpp
        oldCore/Utility/SampleGenerators.cpp
        oldCore/Utility/Math.cpp
    Interface/RenderView.cpp
    Interface/RendererInterface.cpp
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
