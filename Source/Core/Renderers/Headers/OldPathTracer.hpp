//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_OLDPATHTRACER_HPP
#define NPRG045_OLDPATHTRACER_HPP

#include "OldRenderer.hpp"

#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>

constexpr int maxRecursionDepth = 20;

class OldPathTracer : public OldRenderer {
public:
    OldPathTracer(Scene myScene);
    void ImproveTile(ImageTile & tile, int sampleCount) override;
private:


    float EliminationProbability(int depth);

    GU_RayIntersect * intersect;
    Color RenderPixel(UT_Vector2i coordinates);
    Color ComputeIllumination(const GU_Ray & ray, const GU_RayInfo & info, int depth);
};

#endif //NPRG045_OLDPATHTRACER_HPP
