//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "../include/RendererNode.hpp"
#include <thread>
//#include "../../Render/include/RenderInterface.hpp"
#include <PRM/PRM_Type.h>
#include <PRM/PRM_Include.h>
#include "../../Other/include/RenderInterface.hpp"

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
    PRM_Name{"tileSize", "Tile Size"}, //0
    PRM_Name{"cycleCount", "Cycle Count"}, //1
    PRM_Name{"samplesPerCycle", "Samples Per Cycle"}, //2

    PRM_Name{"geometry","Geometry"}, //3
    PRM_Name{"camera","Camera"}, //4
    PRM_Name{"light", "Light"}, //5
    PRM_Name{"renderCurrentFrame", "Render Current Frame"}, //6
    PRM_Name{"multiTest","Multi Test"},
    PRM_Name{"s","s"}
};


void foo(void *data){
    RenderInterface anInterface((RendererNode *)data);
    anInterface.RenderFrame();
}

int RenderFrame(void *data, int index, fpreal64 time, const PRM_Template *tplate){
    try{
        std::thread th1(foo,data);
        th1.detach();
    }
    catch(...){

    }
}

//int RenderFrameRange(void *data, int index, fpreal64 time, const PRM_Template *tplate){
//    std::cout << "Not implemented yet!" << std::endl;
//
//}

static auto callBack = {PRM_Callback(RenderFrame)};


static PRM_Default defLight = {0,""};

static PRM_Default defTileSize[] = {32,32};
static PRM_Default defCycleCount = {4};
static PRM_Default defSamplesPerCycle = {10};

static PRM_Default defCamera = {0,""};
static PRM_Default defGeometry = {0,""};

static PRM_Default defGeneral {0,""};


static PRM_Template testTemplates[] = {
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,0,&prmNames[5],&defLight}
};

static PRM_Name names[] = {
        PRM_Name("lights",  "Number of Lights"),
};


static PRM_Template thePointTemplates[] =
        {
                PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[5],&defLight},
                PRM_Template()
        };


PRM_Template static prmTemplates[]{
    PRM_Template{PRM_INT,2,&prmNames[0],defTileSize},
    PRM_Template{PRM_INT,1,&prmNames[1],&defCycleCount},
    PRM_Template{PRM_INT,1,&prmNames[2],&defSamplesPerCycle},

    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[3],&defCamera},
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[4],&defGeometry},
    PRM_Template(PRM_MULTITYPE_LIST, thePointTemplates, 1, &names[0]),
    PRM_Template{PRM_CALLBACK,1,&prmNames[6],&defGeneral,0,0,PRM_Callback(RenderFrame)},
    PRM_Template()
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