
#include "Hook.hpp"

#include <ROP/ROP_Error.h>
#include <ROP/ROP_Templates.h>
#include <SOP/SOP_Node.h>

#include <OP/OP_Director.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <CH/CH_LocalVariable.h>

#include <UT/UT_DSOVersion.h>
#include <UT/UT_OFStream.h>

OP_Node *PathTracer::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new PathTracer(net,name,op);
}

PRM_Template *PathTracer::BuildPRMTemplate() {
    return nullptr;
}

PathTracer::PathTracer(OP_Network *net, const char *name, OP_Operator *op) : ROP_Node(net,name,op) {

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