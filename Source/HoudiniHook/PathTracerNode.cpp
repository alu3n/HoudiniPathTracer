//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "PathTracerNode.hpp"
#include "../Core/PathTracer.hpp"

#include <vector>
#include <OP/OP_Director.h>
#include <OBJ/OBJ_Camera.h>
#include <OBJ/OBJ_Light.h>

//PathTracerNode * local;

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
//    std::cout << "Current frame: " << OPgetDirector()->getChannelManager()->getFrame(time) << std::endl;
    PathTracerNode * nodePtr = static_cast<PathTracerNode *>(data);
    UT_String cameraPath;
    UT_String geoPath;
    UT_String lightPath;
//
    nodePtr->evalString(cameraPath,"cameraPath",0,time);
    nodePtr->evalString(geoPath,"geometryTarget",0,time);
    nodePtr->evalString(lightPath,"areaLight",0,time);

    auto cameraNode = OPgetDirector()->findOBJNode(cameraPath)->castToOBJCamera();
    auto lightNode = OPgetDirector()->findOBJNode(lightPath)->castToOBJLight();
    auto geometryNode = OPgetDirector()->findOBJNode(geoPath);

    std::cout << cameraPath << std::endl;
    std::cout << lightPath << std::endl;
    std::cout << geoPath << std::endl;

//    GU_Detail * geometry;

    auto cameraOBJNode = OPgetDirector()->findOBJNode(cameraPath)->castToOBJCamera();

//    cameraNode = OBJ_Camera::castToOBJCamera(OPgetDirector()->findNode(cameraPath))

    cameraNode->findNode(cameraPath);
    lightNode->findNode(lightPath);
    geometryNode->findNode(geoPath);

    //Todo: Make this dependent on somethink else
    OP_Context context(0);

    auto geometry = geometryNode->getRenderGeometry(context);

    auto geometryVector = std::vector<const GU_Detail *>();
    auto lightVector = std::vector<OBJ_Light *>();

    geometryVector.push_back(geometry);
    lightVector.push_back(lightNode);


    PathTracer(geometryVector,lightVector,cameraNode,time);
    return 0;
}

static PRM_Template prmTemplates[]{
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[0],&prmDefaults[0]},
        PRM_Template{PRM_INT,1,&prmNames[1],&prmDefaults[1]},
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[2],&prmDefaults[2]},
        PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[3],&prmDefaults[3]},
        PRM_Template{PRM_CALLBACK,1,&prmNames[4],&prmDefaults[4],0,0,PRM_Callback(Debug)}
};

OP_Node *PathTracerNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
//    local = new PathTracerNode(net, name, op);
    return new PathTracerNode(net,name,op);
}



PRM_Template *PathTracerNode::BuildPRMTemplate() {
    return &prmTemplates[0];
}


PathTracerNode::PathTracerNode(OP_Network *net, const char *name, OP_Operator *op) : ROP_Node(net, name, op) {

}

PathTracerNode::~PathTracerNode(){
    //Todo: Delete parameters
}