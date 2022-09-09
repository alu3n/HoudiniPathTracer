//
// Created by Vojtěch Pröschl on 08.09.2022.
//

#ifndef NPRG045_RENDERENGINE_HPP
#define NPRG045_RENDERENGINE_HPP

#include "SceneComponents/Camera.hpp"
#include "SceneComponents/Light.hpp"

#include <SOP/SOP_Node.h>
#include <GU/GU_RayIntersect.h>
#include <array>



constexpr UT_Vector3T DefaultVertexNormal = {0,1,0};
constexpr UT_Vector3T DefaultPointColor = {1,1,1};

using ImageMatrix = std::vector<std::vector<UT_Vector4F>>;

class RenderEngine{
public:
    RenderEngine(SOP_Node * geometry);
    virtual void Load(Camera * camera, const std::vector<Light> & lights, fpreal time);
    virtual ImageMatrix RenderTile(int sampleCount, int tx0, int tx1, int ty0, int ty1) = 0;
protected:
    //region Created during initialization

    SOP_Node * GeometryNode;

    //endregion

    //region Created during load

    GU_DetailHandle * gdh;

    GA_RWHandleV3 * HandlePointColor;
//    GA_RWHandleI * HandleVertexPointNum;
    GA_RWHandleV3 * HandleVertexNormal;

    Camera * camera;

    void LoadPointColor();
    void LoadVertexNormal();
    void LoadVertexPointNum();

    //endregion

    //region Utility functions

    virtual UT_Vector3F IntersectionPointColor(const GU_RayInfo & info);
    virtual UT_Vector3F IntersectionVertexNormal(const GU_RayInfo & info);

    //endregion
};

#endif //NPRG045_RENDERENGINE_HPP
