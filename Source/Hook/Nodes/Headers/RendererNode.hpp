//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#ifndef NPRG045_RENDERERNODE_HPP
#define NPRG045_RENDERERNODE_HPP

#include <ROP/ROP_Node.h>
#include <UT/UT_StringHolder.h>
#include <PRM/PRM_Include.h>

class RendererNode : public ROP_Node{
public:
    static PRM_Template *BuildPRMTemplate();
    static OP_Node *BuildOPNode(OP_Network *net, const char *name, OP_Operator *op);
    static const UT_StringHolder NodeName; //Name of the rop node when created
protected:
    RendererNode(OP_Network *net, const char *name, OP_Operator *op);
    ~RendererNode() override;
};

#endif //NPRG045_RENDERERNODE_HPP
