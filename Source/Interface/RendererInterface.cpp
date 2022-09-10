//
// Created by Vojtěch Pröschl on 07.09.2022.
//

#include "RendererInterface.hpp"
#include "../Core/WhittedRayTracer/WhittedRayTracer.hpp"
#include "../Core/SceneComponents/Light.hpp"

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

    UT_Vector2i tileCount{camera->ImageResolution.x()/tileSize.x(),camera->ImageResolution.y()/tileSize.y()};

    auto light = new ConstantPointLight({0,2.99,0},5);

    auto areaLight1 = new ConstantRectangularAreaLight({3,4,0},{1.8,0,0},{4,4},20);
    auto areaLight2 = new ConstantRectangularAreaLight({0,4,0},{0,0,0},{4,4},20);


    renderEngine->Load(camera,{areaLight1},0);

    for(int tx = 0; tx < tileCount.x(); ++tx){
        for(int ty = 0; ty < tileCount.y(); ++ty){
            auto tx0 = tx * tileSize.x();
            auto tx1 = tx0 + tileSize.x() - 1;
            auto ty0 = ty * tileSize.y();
            auto ty1 = ty0 + tileSize.y() - 1;
            //Todo: Insert sample count
            auto tile = renderEngine->RenderTile(sampleCount,tx0,tx1,ty0,ty1);
            renderView.PushTile(tile,tx0,tx1,ty0,ty1);
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

//    settings = new oldRenderSettings(*camera, fps);
    renderEngine = new WhittedRayTracer(geometryNode);
//    renderer = new WhittedRayTracer(*settings,geometryNode);
    renderView = RenderView(camera->ImageResolution,tileSize);
}