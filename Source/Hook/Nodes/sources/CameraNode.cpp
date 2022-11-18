//
// Created by Vojtěch Pröschl on 12.09.2022.
//

#include "../include/CameraNode.hpp"
#include "../../Other/include/Utility.hpp"
#include <math.h>
//#include <UT/UT_DSOVersion.h>
#include <UT/UT_DMatrix3.h>
#include <OP/OP_OperatorTable.h>

CameraNode::CameraNode(OP_Network *net, const char *name, OP_Operator *op) : OBJ_Geometry(net,name,op){}
//CameraNode::~CameraNode() {}

OP_Node *CameraNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *entry) {
    return new CameraNode(net,name,entry);
}



static PRM_Name prmNames[]{
        PRM_Name{"resolution","Resolution"},
        PRM_Name{"aperature","Aperature"},
        PRM_Name{"focalLength","Focal Length"},
        PRM_Name{"translation","Translation"},
        PRM_Name{"rotation","Rotation"}
};

static PRM_Default defResolution[] = {{1920},{800}};
static PRM_Default defAperature = {50};
static PRM_Default defFocalLength = {42};
static PRM_Default defTranslation[] = {{0},{0},{0}};
static PRM_Default defRotation[] = {{0},{0},{0}};

PRM_Template static prmTemplates[]{
        PRM_Template{PRM_INT,2,&prmNames[0],defResolution},
        PRM_Template{PRM_FLT,1,&prmNames[1],&defAperature},
        PRM_Template{PRM_FLT,1,&prmNames[2],&defFocalLength},
        PRM_Template{PRM_FLT,3,&prmNames[3],defTranslation},
        PRM_Template{PRM_FLT,3,&prmNames[4],defRotation},
        PRM_Template()
};



OP_TemplatePair *CameraNode::buildTemplatePair() {
    auto temp = new OP_TemplatePair(prmTemplates,0);
    return new OP_TemplatePair(defaultGeoTemplate(), temp);
}

constexpr float conversionMultiplier = M_PI/180.0;

OP_ERROR CameraNode::cookMyObj(OP_Context &context) {
    auto Tx = this->evalFloat("translation",0,0);
    auto Ty = this->evalFloat("translation",1,0);
    auto Tz = this->evalFloat("translation",2,0);

    auto Rx = conversionMultiplier*this->evalFloat("rotation",0,0);
    auto Ry = conversionMultiplier*this->evalFloat("rotation",1,0);
    auto Rz = conversionMultiplier*this->evalFloat("rotation",2,0);

    UT_Matrix4T<fpreal64> mtx{1};
    mtx.rotate<1>(Rx,Ry,Rz);
    mtx.translate(Tx,Ty,Tz);

    setWorldXform(mtx);

    return OP_ERROR::UT_ERROR_NONE;
}