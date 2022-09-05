//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "DebugNode.hpp"

PRM_Template *DebugNode::BuildPRMTemplate() {
    return nullptr;
}

OP_Node *DebugNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new DebugNode(net, name, op);
}

DebugNode::DebugNode(OP_Network *net, const char *name, OP_Operator *op) : SOP_Node(net, name, op) {
    mySopFlags.setManagesDataIDs(true);
}

DebugNode::~DebugNode() {

}

OP_ERROR DebugNode::cookMySop(OP_Context &context) {

    /*
     * Debug code here...
     */

    return OP_ERROR::UT_ERROR_NONE;
}