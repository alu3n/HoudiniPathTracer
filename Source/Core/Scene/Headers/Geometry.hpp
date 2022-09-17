//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#ifndef NPRG045_GEOMETRY_HPP
#define NPRG045_GEOMETRY_HPP

#include <SOP/SOP_Node.h>
#include <GU/GU_RayIntersect.h>

class Geometry{
public:
    Geometry(SOP_Node * geometryNode, OP_Context & context);

    GU_DetailHandle * gdh;

    virtual UT_Vector3F IntersectionPointColor(const GU_RayInfo & info);
    virtual UT_Vector3F IntersectionVertexNormal(const GU_RayInfo & info);
private:
    GA_RWHandleV3 * HandlePointColor;
    GA_RWHandleV3 * HandleVertexNormal;

    void LoadPointColor();
    void LoadVertexNormal();
    void LoadVertexPointNum();
};

#endif //NPRG045_GEOMETRY_HPP
