//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_RENDERER_HPP
#define NPRG045_RENDERER_HPP

#include "SceneComponents/Camera.hpp"

#include <OBJ/OBJ_Light.h>
#include <vector>
#include <array>


using ImageMatrix = std::vector<std::vector<UT_Vector3F>>;

struct RenderSettings{
    RenderSettings(Camera cam, int fps);
    Camera Cam; //Todo: Put info such as shutterspeed etc. into camera
//    UT_Vector2i Framerange;
    int FPS;
};

class Renderer{
public:
    Renderer(RenderSettings settings, SOP_Node * geo); //Todo: Change input
    virtual ImageMatrix RenderImage(int frame);
    virtual std::vector<ImageMatrix> RenderAnimation(UT_Vector2i framerange);
protected:
    virtual UT_Vector3F RenderPixel(UT_Vector2i pixelCoords, int frame) = 0;

    RenderSettings Settings;
    SOP_Node * Geo;
};

#endif //NPRG045_RENDERER_HPP
