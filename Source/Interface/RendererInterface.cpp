//
// Created by Vojtěch Pröschl on 07.09.2022.
//

#include "RendererInterface.hpp"
#include "../Core/WhittedRayTracer/WhittedRayTracer.hpp"

//#include <UT_Vector2>
#include <OP/OP_Director.h>

RendererInterface::RendererInterface(RendererNode *rendererNode) {
    this->rendererNode = rendererNode;
}

void RendererInterface::RenderFramerange() {
    //Todo: Render frame range
}

void RendererInterface::RenderFrame() {
    renderView.Open();

    UT_Vector2i tileCount{camera->ImageResolution.x()/16,camera->ImageResolution.y()/16};

    renderer->LoadFrame(0);

    for(int tx = 0; tx < tileCount.x(); ++tx){
        for(int ty = 0; ty < tileCount.y(); ++ty){
            auto tile = renderer->RenderTile(0,tx * 16, tx * 16 + 15, ty * 16, ty * 16 + 15);
            renderView.PushTile(tile,tx*16,tx*16+15,ty*16,ty*16+15);
//            std::cout << tile.size() << std::endl;
        }
    }
}

void RendererInterface::LoadData() {
    //Todo: Load data from RenderNode interface
    //Todo: Add check whether the camera exist and in negative case output error


    sampleCount = rendererNode->evalInt("sampleCount",0,0);
    tileSize = {(int)rendererNode->evalInt("tileSize",0,0),(int)rendererNode->evalInt("tileSize",1,0)};
    fps = rendererNode->evalInt("fps",0,0);
    frameRange = {(int)rendererNode->evalInt("frameRange",0,0),(int)rendererNode->evalInt("frameRange",1,0)};

    UT_StringHolder cameraPath;
    UT_StringHolder geometryPath;

    rendererNode->evalString(cameraPath,"camera",0,0);
    rendererNode->evalString(geometryPath,"geometry",0,0);

    auto cameraNode = OPgetDirector()->getOBJNode(cameraPath)->castToOBJCamera();
    auto geometryNode = OPgetDirector()->getSOPNode(geometryPath);

//    OPgetDirector()->getTime();

    OP_Context context(OPgetDirector()->getTime());

    camera = new Camera(cameraNode,context);

    settings = new RenderSettings(*camera,fps);

    renderer = new WhittedRayTracer(*settings,geometryNode);
    renderView = RenderView(camera->ImageResolution,tileSize);
}