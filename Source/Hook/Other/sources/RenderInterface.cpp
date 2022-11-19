//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../include/RenderInterface.hpp"
#include "../../../Core/Renderers/include/PhysicallyBasedRenderer.hpp"
//#include "../../Core/Renderers/include/PhysicallyBasedRenderer.hpp"
//#include "../../Core/Renderers/include/OldDistributedRaytracer.hpp"
//#include "../../Core/Renderers/include/OldPathTracer.hpp"

//#include "../../oldCore/Utility/SampleGenerators.hpp"

#include <OBJ/OBJ_Camera.h>
#include <OP/OP_Context.h>
#include <OP/OP_Director.h>

#include <chrono>
#include <thread>

RenderInterface::RenderInterface(RendererNode *node) {
    rendererNode = node;
}

void RenderInterface::RenderFrame() {
    UT_StringHolder cameraPath;
    UT_StringHolder geometryPath;

    rendererNode->evalString(cameraPath,"camera",0,0);
    rendererNode->evalString(geometryPath,"geometry",0,0);

    auto cameraNode = OPgetDirector()->getOBJNode(cameraPath)->castToOBJCamera();
    auto geometryNode = OPgetDirector()->getSOPNode(geometryPath);

    OP_Context context(0);

    int ImageResX = cameraNode->evalInt("res",0,context.getTime());
    int ImageResY = cameraNode->evalInt("res",1,context.getTime());
    int TileResX = rendererNode->evalInt("tileSize",0,context.getTime());
    int TileResY = rendererNode->evalInt("tileSize",1,context.getTime());

    int CycleCount = rendererNode->evalInt("cycleCount",0,0);
    int SamplesPerCycle = rendererNode->evalInt("samplesPerCycle",0,0);

    std::cout << "Opening window" << std::endl;
    renderWindow.Open({ImageResX,ImageResY},{TileResX,TileResY});
    std::cout << "Opening done" << std::endl;

    Camera cam(cameraNode,context);
    Geometry geo(geometryNode,context);

    float L1PX = rendererNode->evalFloat("l1Position",0,0);
    float L1PY = rendererNode->evalFloat("l1Position",1,0);
    float L1PZ = rendererNode->evalFloat("l1Position",2,0);

    float L1RX = rendererNode->evalFloat("l1Rotation",0,0);
    float L1RY = rendererNode->evalFloat("l1Rotation",1,0);
    float L1RZ = rendererNode->evalFloat("l1Rotation",2,0);

    float L1SX = rendererNode->evalFloat("l1Size",0,0);
    float L1SY = rendererNode->evalFloat("l1Size",1,0);

    float L1I = rendererNode->evalFloat("l1Intensity",0,0);

    ConstantRectangularLight * light1 = new ConstantRectangularLight({L1PX,L1PY,L1PZ},{L1RX,L1RY,L1RZ},{L1SX,L1SY},{L1I});

    float L2PX = rendererNode->evalFloat("l2Position",0,0);
    float L2PY = rendererNode->evalFloat("l2Position",1,0);
    float L2PZ = rendererNode->evalFloat("l2Position",2,0);

    float L2RX = rendererNode->evalFloat("l2Rotation",0,0);
    float L2RY = rendererNode->evalFloat("l2Rotation",1,0);
    float L2RZ = rendererNode->evalFloat("l2Rotation",2,0);

    float L2SX = rendererNode->evalFloat("l2Size",0,0);
    float L2SY = rendererNode->evalFloat("l2Size",1,0);

    float L2I = rendererNode->evalFloat("l2Intensity",0,0);

    ConstantRectangularLight * light2 = new ConstantRectangularLight({L2PX,L2PY,L2PZ},{L2RX,L2RY,L2RZ},{L2SX,L2SY},{L2I});

    float L3PX = rendererNode->evalFloat("l3Position",0,0);
    float L3PY = rendererNode->evalFloat("l3Position",1,0);
    float L3PZ = rendererNode->evalFloat("l3Position",2,0);

    float L3RX = rendererNode->evalFloat("l3Rotation",0,0);
    float L3RY = rendererNode->evalFloat("l3Rotation",1,0);
    float L3RZ = rendererNode->evalFloat("l3Rotation",2,0);

    float L3SX = rendererNode->evalFloat("l3Size",0,0);
    float L3SY = rendererNode->evalFloat("l3Size",1,0);

    float L3I = rendererNode->evalFloat("l3Intensity",0,0);

    ConstantRectangularLight * light3 = new ConstantRectangularLight({L3PX,L3PY,L3PZ},{L3RX,L3RY,L3RZ},{L3SX,L3SY},{L3I});

    Scene scene({light1,light2,light3},cam,geo);
    PhysicallyBasedRenderer Renderer = PhysicallyBasedRenderer(scene);
    Image img(ImageResX,ImageResY,TileResX,TileResY);

    renderWindow.Device->terminateOnConnectionLost(false);
    for(int i = 0; i < CycleCount; ++i){
        for(auto && tile : img.data){
            Renderer.ImproveTile(tile,SamplesPerCycle);
            renderWindow.DisplayTile(tile);
//            std::this_thread::sleep_for(std::chrono::nanoseconds(20));
        }
    }
    renderWindow.Device->close();


}

void RenderInterface::RenderFramerange() {
    renderWindow.Open({640,640},{64,64});
}