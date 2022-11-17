//
// Created by Vojtěch Pröschl on 12.09.2022.
//

#include "../Headers/LightNode.hpp"
#include "../../Other/Headers/Utility.hpp"

//#include <UT/UT_DSOVersion.h>
#include <OP/OP_Director.h>
#include <UT/UT_DMatrix3.h>
#include <OP/OP_OperatorTable.h>

LightNode::LightNode(OP_Network *net, const char *name, OP_Operator *op) : OBJ_Geometry(net,name,op){}

OP_Node *LightNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *entry) {
    return new LightNode(net,name,entry);
}

static PRM_Name prmNames[]{
    PRM_Name{"size","Size"},
    PRM_Name{"Intensity","Intensity"},
    PRM_Name{"translation","Translation"},
    PRM_Name{"rotation","Rotation"}
};

static PRM_Default defSize[] = {{1.0},{1.0}};
static PRM_Default defIntensity = {1};
static PRM_Default defTranslation[] = {{0},{0},{0}};
static PRM_Default defRotation[] = {{0},{0},{0}};

PRM_Template static prmTemplates[]{
    PRM_Template{PRM_FLT,2,&prmNames[0],defSize},
    PRM_Template{PRM_FLT,1,&prmNames[1],&defIntensity},
    PRM_Template{PRM_FLT,3,&prmNames[2],defTranslation},
    PRM_Template{PRM_FLT,3,&prmNames[3],defRotation},
    PRM_Template()
};

OP_TemplatePair *LightNode::buildTemplatePair() {
    auto temp = new OP_TemplatePair(prmTemplates,0);
    return new OP_TemplatePair(defaultGeoTemplate(), temp);
}

OP_ERROR LightNode::cookMyObj(OP_Context &context) {
    return OP_ERROR::UT_ERROR_NONE;
}