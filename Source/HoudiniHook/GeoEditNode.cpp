//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#include "GeoEditNode.hpp"

#include <OP/OP_Director.h>

PRM_Template *GeoEditNode::BuildPRMTemplate() {
    return nullptr;
}

OP_Node *GeoEditNode::BuildOPNode(OP_Network *net, const char *name, OP_Operator *op) {
    return new GeoEditNode(net,name,op);
}

GeoEditNode::GeoEditNode(OP_Network *net, const char *name, OP_Operator *op) : SOP_Node(net,name,op) {
    mySopFlags.setManagesDataIDs(true);
}

GeoEditNode::~GeoEditNode() {
    //Todo
}

OP_ERROR GeoEditNode::cookMySop(OP_Context &context) {
    return OP_ERROR::UT_ERROR_NONE;
}