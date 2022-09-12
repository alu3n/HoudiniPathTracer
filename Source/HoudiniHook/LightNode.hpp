//
// Created by Vojtěch Pröschl on 12.09.2022.
//

#ifndef NPRG045_LIGHTNODE_HPP
#define NPRG045_LIGHTNODE_HPP

#include <OBJ/OBJ_Geometry.h>

class LightNode : public OBJ_Geometry{
public:
    LightNode(OP_Network *net, const char *name, OP_Operator *op);
    ~LightNode() override = default;
    static OP_Node *BuildOPNode(OP_Network *net, const char *name, OP_Operator *entry);
    static OP_TemplatePair *buildTemplatePair();
protected:
    OP_ERROR cookMyObj(OP_Context & context) override;
};

#endif //NPRG045_LIGHTNODE_HPP
