//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#ifndef NPRG045_DEBUGNODE_HPP
#define NPRG045_DEBUGNODE_HPP

#include <SOP/SOP_Node.h>

class DebugNode : public SOP_Node{
public:
    static PRM_Template *BuildPRMTemplate();
    static OP_Node *BuildOPNode(OP_Network *net, const char *name, OP_Operator * op);
    static const UT_StringHolder NodeName;
protected:
    DebugNode(OP_Network *net, const char *name, OP_Operator *op);
    ~DebugNode() override;
    OP_ERROR cookMySop(OP_Context &context) override;
};

#endif //NPRG045_DEBUGNODE_HPP
