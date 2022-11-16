//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../Headers/RenderInterface.hpp"
#include "../../Core/Renderers/Headers/PhysicallyBasedRenderer.hpp"
#include "../../Core/Renderers/Headers/OldDistributedRaytracer.hpp"
//#include "../../Core/Renderers/Headers/OldPathTracer.hpp"

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

    std::cout << "TESTING" << std::endl;

    renderWindow.Open({ImageResX,ImageResY},{TileResX,TileResY});


    Camera cam(cameraNode,context);
    Geometry geo(geometryNode,context);
//


    ConstantRectangularLight * light0 = new ConstantRectangularLight({0,2.99,0},{0,0,0},{1,1},{5});

//    ConstantRectangularAreaLight * light0 = new ConstantRectangularAreaLight({0,2.99,0},{0,0,0},{1,1},5);
//    ConstantRectangularLight * light1 = new ConstantRectangularLight({10,5,0},{0,0,0},{1,1},{30});
//    ConstantRectangularLight * light2 = new ConstantRectangularLight({-10,5,0},{0,0,0},{1,1},{30});
//
//    std::cout << "TESTING" << std::endl;
//
    Scene scene({light0},cam,geo);
//
    PhysicallyBasedRenderer Renderer = PhysicallyBasedRenderer(scene);
//
    Image img(ImageResX,ImageResY,TileResX,TileResY);
//
//    //Todo: Prevent crashing due to overload of image buffer
//
//
    for(int i = 0; i < 50; ++i){
        for(auto && tile : img.data){
            Renderer.ImproveTile(tile,5);
            renderWindow.DisplayTile(tile);
//            std::this_thread::sleep_for(std::chrono::nanoseconds(25));
        }
    }

}

void RenderInterface::RenderFramerange() {
    renderWindow.Open({640,640},{64,64});
}