//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_RAYTRACER_HPP
#define NPRG045_RAYTRACER_HPP

#include "../Renderer.hpp"

class RayTracer : public Renderer{
public:
    RayTracer(RenderSettings);
protected:
    UT_Vector3F RenderPixel(UT_Vector2i pixelCoords) override;
};

#endif //NPRG045_RAYTRACER_HPP
