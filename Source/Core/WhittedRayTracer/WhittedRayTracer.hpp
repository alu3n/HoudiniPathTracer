//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_WHITTEDRAYTRACER_HPP
#define NPRG045_WHITTEDRAYTRACER_HPP

//#include "../oldRenderer.hpp"

#include "../RenderEngine.hpp"

#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>




class WhittedRayTracer : public RenderEngine{
public:
    WhittedRayTracer(SOP_Node * geo);
    ImageMatrix RenderTile(int sampleCount, int tx0, int tx1, int ty0, int ty1) override;
    void Load(Camera * camera, const std::vector<Light*> & lights, fpreal time) override;
protected:
    UT_Vector4F RenderPixel(UT_Vector2i pixelCoords);
//    UT_Vector4F Shade(GU_RayInfo & info, GU_Ray & ray, int recursionDepth);
    UT_Vector4F Shade(const GU_Ray & ray, const GU_RayInfo & info,UT_Vector3F N,UT_Vector3F Cd, int recursionDepth);
//    UT_Vector4F Shade(const UT_Vector3F & dir, const UT_Vector3F & N, const UT_Vector3F & intPos, int Recursion);
    UT_Vector3F PointLightPosition[3] = {{10,5,3},{0,5,0},{0,5,0}};
    GU_RayIntersect * intersect;
//    GA_ROHandleV3 color;
//    GA_ROHandleV3 normal;
//    const GU_Detail * gdp;
//    UT_Vector3F ComputeNormal(const GU_RayInfo & rayInfo);
//    UT_Vector3F ComputeColor()
};

#endif //NPRG045_WHITTEDRAYTRACER_HPP
