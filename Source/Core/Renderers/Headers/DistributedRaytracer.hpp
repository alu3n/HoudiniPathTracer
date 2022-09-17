//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_DISTRIBUTEDRAYTRACER_HPP
#define NPRG045_DISTRIBUTEDRAYTRACER_HPP

#include "Renderer.hpp"

#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>

class DistributedRaytracer : public Renderer{
public:
    DistributedRaytracer(Scene myScene);// : Renderer(myScene)
    void ImproveTile(ImageTile & tile, int sampleCount) override;
private:
    GU_RayIntersect * intersect;
    Color RenderPixel(UT_Vector2i coordinates);
    Color ComputeColor(const GU_Ray & ray, const GU_RayInfo & info, int depth);
};

#endif //NPRG045_DISTRIBUTEDRAYTRACER_HPP
