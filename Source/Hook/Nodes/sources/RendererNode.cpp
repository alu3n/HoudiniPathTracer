//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "../include/RendererNode.hpp"
#include <thread>
//#include "../../Render/include/RenderInterface.hpp"
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

    PRM_Name{"l1Position","Light 1 Position"}, //5
    PRM_Name{"l1Rotation","Light 1 Rotation"}, //6
    PRM_Name{"l1Size","Light 1 Size"}, //7
    PRM_Name{"l1Intensity","Light 1 Intensity"}, //8

    PRM_Name{"l2Position","Light 2 Position"}, //9
    PRM_Name{"l2Rotation","Light 2 Rotation"}, //10
    PRM_Name{"l2Size","Light 2 Size"}, //11
    PRM_Name{"l2Intensity","Light 2 Intensity"}, //12

    PRM_Name{"l3Position","Light 3 Position"}, //13
    PRM_Name{"l3Rotation","Light 3 Rotation"}, //14
    PRM_Name{"l3Size","Light 3 Size"}, //15
    PRM_Name{"l3Intensity","Light 3 Intensity"}, //16

    PRM_Name{"renderCurrentFrame", "Render Current Frame"}, //17
    PRM_Name{"light", "Light"} //18
};


void foo(void *data){
    RenderInterface anInterface((RendererNode *)data);
    anInterface.RenderFrame();
}

int RenderFrame(void *data, int index, fpreal64 time, const PRM_Template *tplate){
//    RenderInterface anInterface((RendererNode *)data);
    try{
//        anInterface.RenderFrame();

        std::thread th1(foo,data);
        th1.detach();

        std::cout << "cosyk" << std::endl;
    }
    catch(...){

    }
}

int RenderFrameRange(void *data, int index, fpreal64 time, const PRM_Template *tplate){
    std::cout << "Not implemented yet!" << std::endl;

}

static auto callBack = {PRM_Callback(RenderFrame),PRM_Callback(RenderFrameRange)};

static PRM_Default defTileSize[] = {32,32};
static PRM_Default defCycleCount = {4};
static PRM_Default defSamplesPerCycle = {10};

static PRM_Default defCamera = {0,""};
static PRM_Default defGeometry = {0,""};

static PRM_Default defLight1Position[] = {0,0,0};
static PRM_Default defLight1Rotation[] = {0,0,0};
static PRM_Default defLight1Size[] = {1,1};
static PRM_Default defLight1Intensity = {10};

static PRM_Default defLight2Position[] = {0,0,0};
static PRM_Default defLight2Rotation[] = {0,0,0};
static PRM_Default defLight2Size[] = {1,1};
static PRM_Default defLight2Intensity = {10};

static PRM_Default defLight3Position[] = {0,0,0};
static PRM_Default defLight3Rotation[] = {0,0,0};
static PRM_Default defLight3Size[] = {1,1};
static PRM_Default defLight3Intensity = {10};

static PRM_Default defGeneral {0,""};

static PRM_Default defLight = {0,""};

PRM_Template static prmTemplates[]{
    PRM_Template{PRM_INT,2,&prmNames[0],defTileSize},
    PRM_Template{PRM_INT,1,&prmNames[1],&defCycleCount},
    PRM_Template{PRM_INT,1,&prmNames[2],&defSamplesPerCycle},

    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[3],&defCamera},
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[4],&defGeometry},

    PRM_Template{PRM_FLT,3,&prmNames[5],defLight1Position},
    PRM_Template{PRM_FLT,3,&prmNames[6],defLight1Rotation},
    PRM_Template{PRM_FLT,2,&prmNames[7],defLight1Size},
    PRM_Template{PRM_FLT,1,&prmNames[8],&defLight1Intensity},

    PRM_Template{PRM_FLT,3,&prmNames[9],defLight2Position},
    PRM_Template{PRM_FLT,3,&prmNames[10],defLight2Rotation},
    PRM_Template{PRM_FLT,2,&prmNames[11],defLight2Size},
    PRM_Template{PRM_FLT,1,&prmNames[12],&defLight2Intensity},

    PRM_Template{PRM_FLT,3,&prmNames[13],defLight3Position},
    PRM_Template{PRM_FLT,3,&prmNames[14],defLight3Rotation},
    PRM_Template{PRM_FLT,2,&prmNames[15],defLight3Size},
    PRM_Template{PRM_FLT,1,&prmNames[16],&defLight3Intensity},

    PRM_Template{PRM_CALLBACK,1,&prmNames[17],&defGeneral,0,0,PRM_Callback(RenderFrame)},

    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[18],&defLight}
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