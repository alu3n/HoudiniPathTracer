//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "DebugNode.hpp"
#include "../Core/SceneComponents/Camera.hpp"
#include <OBJ/OBJ_Camera.h>
#include <OP/OP_Director.h>
#include <OP/OP_AutoLockInputs.h>

PRM_Template *DebugNode::BuildPRMTemplate() {
    return nullptr;
}

OP_Node *DebugNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new DebugNode(net, name, op);
}

DebugNode::DebugNode(OP_Network *net, const char *name, OP_Operator *op) : SOP_Node(net, name, op) {
    mySopFlags.setManagesDataIDs(true);
}

DebugNode::~DebugNode() {

}

OP_ERROR DebugNode::cookMySop(OP_Context &context) {

    /*
     * Debug code here...
     */

    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
        return error();

//    duplicateSource(0, context);

    auto cameraNode = OPgetDirector()->getOBJNode("/obj/Camera1")->castToOBJCamera();
    Camera camera(cameraNode,context);

    gdp->addFloatTuple(GA_ATTRIB_POINT,"N",3);

    auto normalHandle = GA_RWHandleV3(gdp,GA_ATTRIB_POINT,"N");
    auto positionHandle = GA_RWHandleV3(gdp,GA_ATTRIB_POINT,"P");

    int x = cameraNode->evalInt("res",0,context.getTime());
    int y = cameraNode->evalInt("res",1,context.getTime());

    for (int px = 0; px < x; ++px) {
        for (int py = 0; py < y; ++py) {
            auto pt = gdp->appendPointOffset();
            auto ray = camera.GenerateRay({px,py});
            normalHandle.set(pt,ray.dir);
            positionHandle.set(pt,ray.org);
        }
    }

    return OP_ERROR::UT_ERROR_NONE;
}