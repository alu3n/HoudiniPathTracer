//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_WHITTEDRAYTRACER_HPP
#define NPRG045_WHITTEDRAYTRACER_HPP

#include "../Renderer.hpp"

#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>

class WhittedRayTracer : public Renderer{
public:
    WhittedRayTracer(RenderSettings settings, SOP_Node * geo);
    ImageMatrix RenderImage(int frame) override;
protected:
    UT_Vector3F RenderPixel(UT_Vector2i pixelCoords, int frame) override;
    GU_RayIntersect * intersect;
    UT_Vector3F Shade(GU_RayInfo & info, GU_Ray & ray);
    UT_Vector3F PointLightPosition = {10,5,3};
};

#endif //NPRG045_WHITTEDRAYTRACER_HPP
