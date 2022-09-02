//
// Created by Vojtěch Pröschl on 02.09.2022.
//

#ifndef NPRG045_HOOK_HPP
#define NPRG045_HOOK_HPP

#include <ROP/ROP_Node.h>
#include <UT/UT_StringHolder.h>



class PathTracer : public ROP_Node{
public:
    static PRM_Template *BuildPRMTemplate();
    static OP_Node *BuildOPNode(OP_Network *net, const char *name, OP_Operator *op);
    static const UT_StringHolder NodeName; //Name of the rop node when created
protected:
    PathTracer(OP_Network *net, const char *name, OP_Operator *op);
    ~PathTracer() override{};
};



#endif //NPRG045_HOOK_HPP
