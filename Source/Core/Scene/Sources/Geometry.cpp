//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../Headers/Geometry.hpp"

#include <GU/GU_Detail.h>
#include <GU/GU_DetailHandle.h>

Geometry::Geometry(SOP_Node *geometryNode, OP_Context & context){
    gdh = static_cast<GU_DetailHandle *>(geometryNode->getCookedData(context));
}

UT_Vector3F Geometry::IntersectionPointColor(const GU_RayInfo &info) {
    //Todo
}

UT_Vector3F Geometry::IntersectionVertexNormal(const GU_RayInfo &info) {
    //Todo
}

void Geometry::LoadPointColor() {
    //Todo
}

void Geometry::LoadVertexNormal() {
    //Todo
}

void Geometry::LoadVertexPointNum() {
    //Todo
}