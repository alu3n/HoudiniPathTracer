//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Geometry.hpp"

#include <GU/GU_Detail.h>
#include <GU/GU_DetailHandle.h>

#include <iostream>

Geometry::Geometry(SOP_Node *geometryNode, OP_Context & context){
    gdh = static_cast<GU_DetailHandle *>(geometryNode->getCookedData(context));

    LoadPointColor();
    LoadVertexNormal();
    LoadShader();
}

UT_Vector3F Geometry::IntersectionPointColor(const GU_RayInfo &info) {
    UT_Vector3F color = {0,0,0};

    UT_Array<GA_Offset> vertexOffsets;
    UT_Array<float> vertexWeights;
    info.myPrim->computeInteriorPointWeights(vertexOffsets,vertexWeights,info.myU,info.myV,info.myW);

    for(int i = 0; i < vertexOffsets.size(); ++i){
        GA_Offset pointOffset = gdh->gdpNC()->vertexPoint(vertexOffsets[i]);
        auto clr = HandlePointColor->get(pointOffset);
//        std::cout << vertexWeights[i] << std::endl;
        color += vertexWeights[i] * clr;
    }

    return color;
}

int Geometry::IntersectionPointShader(const GU_RayInfo &info) {
    UT_Array<GA_Offset> vertexOffsets;
    UT_Array<float> vertexWeights;
    info.myPrim->computeInteriorPointWeights(vertexOffsets,vertexWeights,info.myU,info.myV,info.myW);
    return (int)HandlePointShader->get(gdh->gdpNC()->vertexPoint(vertexOffsets[0]));
}


UT_Vector3F Geometry::IntersectionVertexNormal(const GU_RayInfo &info) {
    UT_Vector3F normal{0,0,0};

    UT_Array<GA_Offset> vertexOffsets;
    UT_Array<float> vertexWeights;
    info.myPrim->computeInteriorPointWeights(vertexOffsets,vertexWeights,info.myU,info.myV,info.myW);

    for(int i = 0; i < vertexOffsets.size(); ++i){
        auto nrml = HandleVertexNormal->get(vertexOffsets[i]);
        normal += vertexWeights[i]*nrml;
    }
//    std::cout << normal << std::endl;
    return normal;
}

void Geometry::LoadPointColor() {
    gdh->gdpNC()->addFloatTuple(GA_ATTRIB_POINT,GA_SCOPE_PUBLIC,"Cd",3);
    HandlePointColor = new GA_RWHandleV3(gdh->gdpNC(),GA_ATTRIB_POINT,"Cd");
}

void Geometry::LoadVertexNormal() {
    gdh->gdpNC()->addFloatTuple(GA_ATTRIB_VERTEX,GA_SCOPE_PUBLIC,"N",3);
    HandleVertexNormal = new GA_RWHandleV3(gdh->gdpNC(),GA_ATTRIB_VERTEX,"N");
}

void Geometry::LoadShader() {
    gdh->gdpNC()->addFloatTuple(GA_ATTRIB_POINT,GA_SCOPE_PUBLIC,"shader",1);
    HandlePointShader = new GA_RWHandleF(gdh->gdpNC(),GA_ATTRIB_POINT,"shader");
}

//void Geometry::LoadVertexPointNum() {
//    //Todo
//}