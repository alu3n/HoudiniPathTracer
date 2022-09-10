//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "DebugNode.hpp"
#include "../Core/SceneComponents/Camera.hpp"

//#include "../Core/oldRenderer.hpp"
#include "../Core/WhittedRayTracer/WhittedRayTracer.hpp"

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

//    OP_AutoLockInputs inputs(this);
//    if (inputs.lock(context) >= UT_ERROR_ABORT)
//        return error();
//
////    duplicateSource(0, context);
//
//    auto cameraNode = OPgetDirector()->getOBJNode("/obj/Camera1")->castToOBJCamera();
//    auto sopNode = OPgetDirector()->getSOPNode("/obj/geo2");
//
//
//    Camera camera(cameraNode,context);
//
//    oldRenderSettings settings(camera,24);
//
//    WhittedRayTracer rayTracer(settings,sopNode);
//
//    std::cout << "LOADED" << std::endl;
////    auto image = rayTracer.RenderImage(0);
//    std::cout << "RENDERED" << std::endl;
//
//    int rx = camera.ImageResolution.x();
//    int ry = camera.ImageResolution.y();
//
//
//    gdp->addFloatTuple(GA_ATTRIB_POINT,"Cd",3);
////
//    auto colorHandle = GA_RWHandleV3(gdp,GA_ATTRIB_POINT,"Cd");
//    auto positionHandle = GA_RWHandleV3(gdp,GA_ATTRIB_POINT,"P");
//
//    int x = cameraNode->evalInt("res",0,context.getTime());
//    int y = cameraNode->evalInt("res",1,context.getTime());
//
//    for (int px = 0; px < rx; ++px) {
//        for (int py = 0; py < ry; ++py) {
//            auto pt = gdp->appendPointOffset();
////            auto ray = camera.GenerateRay({px,py});
////            colorHandle.set(pt,image[px][py]);
//            UT_Vector3F pos(0.1*px,0,0.1*py);
//            positionHandle.set(pt,pos);
//        }
//    }

    return OP_ERROR::UT_ERROR_NONE;
}