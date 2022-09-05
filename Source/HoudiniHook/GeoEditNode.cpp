//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "GeoEditNode.hpp"

#include <SOP/SOP_Node.h>
#include <OP/OP_Operator.h>
#include <OP/OP_Director.h>
#include <OP/OP_AutoLockInputs.h>

//#include <SOP/SOP_Guide.h>
//#include <GU/GU_Detail.h>
//#include <GA/GA_Iterator.h>
#include <GA/GA_AttributeRefMap.h>
#include <GA/GA_AttributeRefMapDestHandle.h>
#include <GA/GA_Handle.h>
//#include <GA/GA_Types.h>
//
//#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
//#include <UT/UT_Interrupt.h>
//#include <UT/UT_Matrix3.h>
//#include <UT/UT_Matrix4.h>
#include <UT/UT_Vector3.h>
#include <chrono>
//#include <GEO/GEO_Point.h>
//#include <SYS/SYS_Math.h>
//#include <stddef.h>

#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>

PRM_Template *GeoEditNode::BuildPRMTemplate() {
    return nullptr;
}

OP_Node *GeoEditNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new GeoEditNode(net,name,op);
}

GeoEditNode::GeoEditNode(OP_Network *net, const char *name, OP_Operator *op) : SOP_Node(net,name,op) {
    mySopFlags.setManagesDataIDs(true);
}

GeoEditNode::~GeoEditNode() {
    //Todo
}

OP_ERROR GeoEditNode::cookMySop(OP_Context &context) {
    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
        return error();

    duplicateSource(0, context);

//    UT_Vector3 origin = {10,0,0};
//    UT_Vector3 direction = {-1,0,0};
//
//    GU_Ray ray = {origin,direction};
//    GU_RayIntersect rayIntersect = {gdp};
//    GU_RayInfo hitInfo;
//
//    int rx = 5;
//    int ry = 5;

//    for(int x = 0; x < rx; x++){
//        for(int y = 0; y < ry; y++){
//            rayIntersect.clear();
//            UT_Vector3 dir = {static_cast<float>((1.0/rx)*x-0.5),static_cast<float>((1.0/ry)*y-0.5),-1};
////            UT_Vector3 dir = {-1,0,0};
//            UT_Vector3 org = {0,0,-1};
//            rayIntersect.sendRay(org,dir,hitInfo);
//            std::cout << "T max: " << hitInfo.myTmax << std::endl;
//        }
//    }



    return OP_ERROR::UT_ERROR_NONE;
}