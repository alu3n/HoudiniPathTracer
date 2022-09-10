//
// Created by Vojtěch Pröschl on 08.09.2022.
//


#include "RenderEngine.hpp"


#include <GU/GU_Detail.h>
#include <GU/GU_DetailHandle.h>

RenderEngine::RenderEngine(SOP_Node *geometry) {
    GeometryNode = geometry;
}

void RenderEngine::Load(Camera * camera, const std::vector<Light*> &lights, fpreal time) {
    OP_Context context(time);

    this->camera = camera;
    this->lights = lights;

    gdh = static_cast<GU_DetailHandle *>(GeometryNode->getCookedData(context));

    LoadPointColor();
    LoadVertexNormal();
//    LoadVertexPointNum();
}

void RenderEngine::LoadPointColor(){
    gdh->gdpNC()->addFloatTuple(GA_ATTRIB_POINT,GA_SCOPE_PUBLIC,"Cd",3);
    HandlePointColor = new GA_RWHandleV3(gdh->gdpNC(),GA_ATTRIB_POINT,"Cd");
}

void RenderEngine::LoadVertexNormal(){
    gdh->gdpNC()->addFloatTuple(GA_ATTRIB_VERTEX,GA_SCOPE_PUBLIC,"N",3);
    HandleVertexNormal = new GA_RWHandleV3(gdh->gdpNC(),GA_ATTRIB_VERTEX,"N");
}

//void RenderEngine::LoadVertexPointNum() {
//    HandleVertexPointNum = new GA_RWHandleI (gdh->gdpNC(),GA_ATTRIB_VERTEX,"")
//}

UT_Vector3F RenderEngine::IntersectionPointColor(const GU_RayInfo & info) {
    UT_Vector3F color = {0,0,0};

    UT_Array<GA_Offset> vertexOffsets;
    UT_Array<float> vertexWeights;
    info.myPrim->computeInteriorPointWeights(vertexOffsets,vertexWeights,info.myU,info.myV,info.myW);

//    std::cout << "Computing color : " << vertexOffsets.size() << std::endl;

    for(int i = 0; i < vertexOffsets.size(); ++i){
        GA_Offset pointOffset = gdh->gdpNC()->vertexPoint(vertexOffsets[i]);
        auto clr = HandlePointColor->get(pointOffset);

//        std::cout << pointOffset << " : " << clr <<std::endl;
//        std::cout << clr << std::endl;
        color += vertexWeights[i] * clr;
//        std::cout << clr << std::endl;
    }

    return color;
}

UT_Vector3F RenderEngine::IntersectionVertexNormal(const GU_RayInfo & info) {
    UT_Vector3F normal;

    UT_Array<GA_Offset> vertexOffsets;
    UT_Array<float> vertexWeights;
    info.myPrim->computeInteriorPointWeights(vertexOffsets,vertexWeights,info.myU,info.myV,info.myW);

    for(int i = 0; i < vertexOffsets.size(); ++i){
        normal += vertexWeights[i] * HandleVertexNormal->get(vertexOffsets[i]);
    }

    return normal;
}


