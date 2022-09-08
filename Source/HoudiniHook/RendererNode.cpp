//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "../Interface/RenderView.hpp"
#include "RendererNode.hpp"
#include "../Core/PathTracer/PathTracer.hpp"
#include "../Core/SceneComponents/Camera.hpp"
#include "../Core/WhittedRayTracer/WhittedRayTracer.hpp"
#include "../Interface/RendererInterface.hpp"
#include "../Core/Utility/SampleGenerators.hpp"

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
    PRM_Name{"sampleCount", "Sample Count"},
    PRM_Name{"tileSize", "Tile Size"},
    PRM_Name{"fps", "FPS"},
    PRM_Name{"frameRange", "Frame Range"},
    PRM_Name{"renderEngine", "Render Engine"},
    PRM_Name{"camera","Camera"},
    PRM_Name{"light","Light"},
    PRM_Name{"geometry","Geometry"},
    PRM_Name{"renderFrameRange", "Render Frame Range"},
    PRM_Name{"renderCurrentFrame", "Render Current Frame"}
};

static PRM_Default defSampleCount = {0};
static PRM_Default defTileSize[] = {16,16};
static PRM_Default defFps = {24};
static PRM_Default defFrameRange[] = {{0},{240}};
static PRM_Default defRenderEngine = {0}; //Temp solution... 0->Whitted, 1->PathTracing...
static PRM_Default defCamera = {0,""};
static PRM_Default defLight = {0,""};
static PRM_Default defGeometry = {0,""};
static PRM_Default defGeneral {0,""};

int RenderFrame(void *data, int index, fpreal64 time, const PRM_Template *tplate){
    RendererInterface rendererInterface((RendererNode *)data);
    rendererInterface.LoadData();
    rendererInterface.RenderFrame();
}

int RenderFrameRange(void *data, int index, fpreal64 time, const PRM_Template *tplate){
    std::cout << "Not implemented yet!" << std::endl;
    SampleGenerator gen = UniformGenerator(10);
    std::cout << gen.Generate01D2() << std::endl;
    std::cout << gen.Generate01D2() << std::endl;

}

static auto callBack = {PRM_Callback(RenderFrame),PRM_Callback(RenderFrameRange)};


PRM_Template static prmTemplates[]{
    PRM_Template{PRM_INT,1,&prmNames[0],&defSampleCount},
    PRM_Template{PRM_INT,2,&prmNames[1],defTileSize},
    PRM_Template{PRM_INT,1,&prmNames[2],&defFps},
    PRM_Template{PRM_INT,2,&prmNames[3],defFrameRange},
    PRM_Template{PRM_INT,1,&prmNames[4],&defRenderEngine},
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[5],&defCamera},
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[6],&defLight},
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[7],&defGeometry},
    PRM_Template{PRM_CALLBACK,1,&prmNames[8],&defGeneral,0,0,PRM_Callback(RenderFrameRange)},
    PRM_Template{PRM_CALLBACK,1,&prmNames[9],&defGeneral,0,0,PRM_Callback(RenderFrame)}
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