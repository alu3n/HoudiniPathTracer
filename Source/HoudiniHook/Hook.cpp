#include "PathTracerNode.hpp"
#include "GeoEditNode.hpp"

#include <SOP/SOP_Node.h>
#include <OP/OP_OperatorTable.h>
#include <CH/CH_LocalVariable.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_OFStream.h>



void newDriverOperator(OP_OperatorTable *table){
    table->addOperator(new OP_Operator(
    "path_tracer",
    "Path Tracer",
    PathTracerNode::BuildOPNode,
    PathTracerNode::BuildPRMTemplate(),
    0,
    0,
    nullptr,
    OP_FLAG_GENERATOR
    ));
}

void newSopOperator(OP_OperatorTable *table){
    table->addOperator(new OP_Operator(
    "geo_edit",
    "Geo Edit",
    GeoEditNode::BuildOPNode,
    GeoEditNode::BuildPRMTemplate(),
    1,
    1,
    NULL
    ));
}