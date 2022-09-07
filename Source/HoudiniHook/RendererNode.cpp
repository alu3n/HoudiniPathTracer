//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "RenderView.hpp"
#include "RendererNode.hpp"
#include "../Core/PathTracer/PathTracer.hpp"
#include "../Core/SceneComponents/Camera.hpp"
#include "../Core/WhittedRayTracer/WhittedRayTracer.hpp"

#include <vector>
#include <OP/OP_Director.h>
#include <OBJ/OBJ_Camera.h>
#include <OBJ/OBJ_Light.h>
#include <AU/AU_Input.h>
#include <UT/UT_BitArray.h>
#include <IMG/IMG_File.h>
#include <IMG/IMG_TileDevice.h>
#include <IMG/IMG_TileOptions.h>
#include <TIL/TIL_TileMPlay.h>
#include <UT/UT_PtrArray.h>
#include <IMG/IMG_TileRead.h>
//RendererNode * local;

//Names of the node interface elements
static PRM_Name prmNames[]{
        PRM_Name{"cameraPath", "Camera Path"},
        PRM_Name{"sampleCount","Sample Count"},
        PRM_Name{"areaLight","Area Light"},
        PRM_Name{"geometryTarget","Geometry Traget"},
        PRM_Name{"debugButton","Debug Button"}
};

//Default values of the interface elements
static PRM_Default prmDefaults[]{
        PRM_Default{0,""},
        PRM_Default{100},
        PRM_Default{0,""},
        PRM_Default{0,""},
        PRM_Default{0,""}
};

int Debug(void *data,int index, fpreal64 time, const PRM_Template *tplate) {
    auto cameraNode = OPgetDirector()->getOBJNode("/obj/Camera1")->castToOBJCamera();
    auto sopNode = OPgetDirector()->getSOPNode("/obj/geo2");

    OP_Context context(time);
    std::cout << context.getTime() << std::endl;
    Camera camera(cameraNode, context);

    RenderSettings settings(camera,24);
    WhittedRayTracer rayTracer(settings,sopNode);

//    std::cout << "LOADED" << std::endl;
//    auto image = rayTracer.RenderImage(0);
//    std::cout << "RENDERED" << std::endl;

    int rx = camera.ImageResolution.x();
    int ry = camera.ImageResolution.y();


//    std::vector<std::vector<UT_Vector4F>> imageMatrix;
//    for(int y = 0; y < 16; ++y){
//        imageMatrix.push_back({});
//        for(int x = 0; x < 16; ++x){
//            imageMatrix.back().push_back({0,1,0,0});
//        }
//    }


    auto viewer = RenderView({rx,ry},{16,16});
    viewer.Open();

    int tilesX = rx / 16;
    int tilesY = ry / 16;
    std::cout << tilesX << std::endl;
    std::cout << tilesY << std::endl;

    std::cout << "Rendering" << std::endl;

    rayTracer.LoadFrame(0);

    auto test = rayTracer.RenderTile(0,0,15,0,15);

    for(int x = 0; x < tilesX; ++x){
        for(int y = 0; y < tilesY; ++y){
            auto tile = rayTracer.RenderTile(0,x*16,x*16+15,y*16,y*16+15);
            viewer.PushTile(tile,x*16,x*16+15,y*16,y*16+15);
        }
    }


    std::cout << "Done" << std::endl;
//    viewer.PushTile(imageMatrix,32,47,32,47);
//    std::cout << "VIEW SHOULD OPEN" << std::endl;

    return 0;
}
PRM_Template
static  prmTemplates[]{
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[0],&prmDefaults[0]},
        PRM_Template{PRM_INT,1,&prmNames[1],&prmDefaults[1]},
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[2],&prmDefaults[2]},
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[3],&prmDefaults[3]},
        PRM_Template{PRM_CALLBACK,1,&prmNames[4],&prmDefaults[4],0,0,PRM_Callback(Debug)}
};

OP_Node *RendererNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new RendererNode(net, name, op);
}



PRM_Template *RendererNode::BuildPRMTemplate() {
    return &prmTemplates[0];
}


RendererNode::RendererNode(OP_Network *net, const char *name, OP_Operator *op) : ROP_Node(net, name, op) {

}

RendererNode::~RendererNode(){

}