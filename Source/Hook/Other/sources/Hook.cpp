#include "../../Nodes/include/RendererNode.hpp"

#include <SOP/SOP_Node.h>
#include <OP/OP_OperatorTable.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_OFStream.h>


void newDriverOperator(OP_OperatorTable *table){
    table->addOperator(new OP_Operator(
            "nprg045_renderer",
            "NPRG045 OldRenderer",
            RendererNode::BuildOPNode,
            RendererNode::BuildPRMTemplate(),
            0,
            0,
            nullptr,
            OP_FLAG_GENERATOR
    ));
}