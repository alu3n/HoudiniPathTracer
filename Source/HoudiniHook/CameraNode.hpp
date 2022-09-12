//
// Created by Vojtěch Pröschl on 12.09.2022.
//

#ifndef NPRG045_CAMERANODE_HPP
#define NPRG045_CAMERANODE_HPP

#include <OBJ/OBJ_Geometry.h>

class CameraNode : public OBJ_Geometry{
public:
    CameraNode(OP_Network *net, const char *name, OP_Operator *op);
    ~CameraNode() override = default;

    static OP_Node *BuildOPNode(OP_Network *net, const char *name, OP_Operator *entry);
    static OP_TemplatePair *buildTemplatePair();
protected:
    OP_ERROR cookMyObj(OP_Context & context) override;
};

#endif //NPRG045_CAMERANODE_HPP
