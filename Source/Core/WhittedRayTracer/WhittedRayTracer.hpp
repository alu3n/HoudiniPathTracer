//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_WHITTEDRAYTRACER_HPP
#define NPRG045_WHITTEDRAYTRACER_HPP

#include "../Renderer.hpp"

class WhittedRayTracer : public Renderer{
public:
    WhittedRayTracer(RenderSettings settings, SOP_Node * geo);
protected:
    UT_Vector3F RenderPixel(UT_Vector2i pixelCoords, int frame) override;
};

#endif //NPRG045_WHITTEDRAYTRACER_HPP
