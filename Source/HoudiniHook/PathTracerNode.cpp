//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "PathTracerNode.hpp"

#include <OP/OP_Director.h>

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

int DebugInfo(void *data,int index, fpreal32 time, const PRM_Template *tplate){
    std::cout << "Current frame: " << OPgetDirector()->getChannelManager()->getFrame(time) << std::endl;

}

static PRM_Template prmTemplates[]{
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[0],&prmDefaults[0]},
        PRM_Template{PRM_INT,1,&prmNames[1],&prmDefaults[1]},
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[2],&prmDefaults[2]},
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[3],&prmDefaults[3]},
        PRM_Template{PRM_CALLBACK,1,&prmNames[4],&prmDefaults[4],0,0,PRM_Callback(DebugInfo)}
};

OP_Node *PathTracerNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new PathTracerNode(net, name, op);
}



PRM_Template *PathTracerNode::BuildPRMTemplate() {
    return &prmTemplates[0];
}


PathTracerNode::PathTracerNode(OP_Network *net, const char *name, OP_Operator *op) : ROP_Node(net, name, op) {

}

PathTracerNode::~PathTracerNode(){
    //Todo: Delete parameters
}