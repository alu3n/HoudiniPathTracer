//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#ifndef NPRG045_PATHTRACERNODE_HPP
#define NPRG045_PATHTRACERNODE_HPP

#include <ROP/ROP_Node.h>

#include <ROP/ROP_Node.h>
#include <UT/UT_StringHolder.h>
#include <PRM/PRM_Include.h>

class PathTracerNode : public ROP_Node{
public:
    static PRM_Template *BuildPRMTemplate();
    static OP_Node *BuildOPNode(OP_Network *net, const char *name, OP_Operator *op);
    static const UT_StringHolder NodeName; //Name of the rop node when created
protected:
    PathTracerNode(OP_Network *net, const char *name, OP_Operator *op);
    ~PathTracerNode() override;
};

#endif //NPRG045_PATHTRACERNODE_HPP
