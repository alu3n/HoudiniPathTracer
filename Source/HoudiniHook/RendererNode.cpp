//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "RendererNode.hpp"
#include "../Core/PathTracer/PathTracer.hpp"

#include <vector>
#include <OP/OP_Director.h>
#include <OBJ/OBJ_Camera.h>
#include <OBJ/OBJ_Light.h>
//#include <AU/AU_Input.h>
//#include <UT/UT_BitArray.h>
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
//    UT_PtrArray<PXL_Raster *> images;
//
//    IMG_File *file = IMG_File::open("/Users/vojtechproschl/Desktop/sheetmusic.png");
//    file->readImages(images);
//    images.
//    IMG_TileDevice *device = IMG_TileDevice::newMPlayDevice();
//    device->setSendPIDFlag(false);
//    device->terminateOnConnectionLost(false);

//    IMG_TileOptions *tileOpt = new IMG_TileOptions();
//    mp->open(*tileOpt, 1280, 720, 1, 3000, 2.0);

    std::cout << "IMAGE LOADED" << std::endl;
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