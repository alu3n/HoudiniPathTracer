
#include "Hook.hpp"

#include <ROP/ROP_Error.h>
#include <ROP/ROP_Templates.h>
#include <SOP/SOP_Node.h>
#include <ROP/ROP_API.h>

#include <PRM/PRM_Template.h>

#include <OP/OP_Director.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <CH/CH_LocalVariable.h>

#include <UT/UT_DSOVersion.h>
#include <UT/UT_OFStream.h>

//Names of the node interface elements
static PRM_Name prmNames[]{
        PRM_Name{"cameraPath", "Camera Path"},
        PRM_Name{"sampleCount","Sample Count"},
        PRM_Name{"areaLight","Area Light"},
        PRM_Name{"geometryTarget","Geometry Traget"}
};

//Default values of the interface elements
static PRM_Default prmDefaults[]{
    PRM_Default{0,""},
    PRM_Default{100},
    PRM_Default{0,""},
    PRM_Default{0,""}
};

static PRM_Template prmTemplates[]{
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[0],&prmDefaults[0]},
    PRM_Template{PRM_INT,1,&prmNames[1],&prmDefaults[1]},
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[2],&prmDefaults[2]},
    PRM_Template{PRM_STRING,PRM_TYPE_DYNAMIC_PATH,1,&prmNames[3],&prmDefaults[3]},
    theRopTemplates[ROP_RENDER_TPLATE],
    theRopTemplates[ROP_RENDERDIALOG_TPLATE],
    theRopTemplates[ROP_TRANGE_TPLATE],
    theRopTemplates[ROP_FRAMERANGE_TPLATE],
};

OP_Node *PathTracer::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new PathTracer(net,name,op);
}



PRM_Template *PathTracer::BuildPRMTemplate() {
    return &prmTemplates[0];
}


PathTracer::PathTracer(OP_Network *net, const char *name, OP_Operator *op) : ROP_Node(net,name,op) {

}

PathTracer::~PathTracer(){
    //Todo: Delete parameters
}

void newDriverOperator(OP_OperatorTable *table){
    table->addOperator(new OP_Operator(
            "path_tracer",
            "Path Tracer",
            PathTracer::BuildOPNode,
            PathTracer::BuildPRMTemplate(),
            0,
            0,
            nullptr,
            OP_FLAG_GENERATOR
            ));
}