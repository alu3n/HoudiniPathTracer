//
// Created by Vojtěch Pröschl on 04.09.2022.
//

#ifndef NPRG045_GEOEDITNODE_HPP
#define NPRG045_GEOEDITNODE_HPP

#include <SOP/SOP_Node.h>

class GeoEditNode : public SOP_Node{
public:
    static PRM_Template *BuildPRMTemplate();
    static OP_Node *BuildOPNode(OP_Network *net, const char *name, OP_Operator * op);
    static const UT_StringHolder NodeName;
protected:
    GeoEditNode(OP_Network *net, const char *name, OP_Operator *op);
    ~GeoEditNode() override;
    OP_ERROR cookMySop(OP_Context &context) override;
};

#endif //NPRG045_GEOEDITNODE_HPP
