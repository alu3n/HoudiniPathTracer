//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_RENDERER_HPP
#define NPRG045_RENDERER_HPP

#include "SceneComponents/Camera.hpp"

#include <OBJ/OBJ_Light.h>
#include <vector>
#include <array>


using ImageMatrix = std::vector<std::vector<UT_Vector4F>>;

struct RenderSettings{
    RenderSettings() = default;
    RenderSettings(Camera cam, int fps);
    Camera Cam; //Todo: Put info such as shutterspeed etc. into camera
    int FPS;
};

//Todo: Change image matrix to RGBA

class Renderer{
public:
    Renderer(RenderSettings settings, SOP_Node * geo); //Todo: Change input
//    virtual ImageMatrix RenderImage(int frame);
    virtual ImageMatrix RenderTile(fpreal time, int tx0, int tx1, int ty0, int ty1);
//    virtual std::vector<ImageMatrix> RenderAnimation(UT_Vector2i framerange);
    virtual void LoadFrame(fpreal time);
protected:
    virtual UT_Vector4F RenderPixel(UT_Vector2i pixelCoords) = 0;
    GU_RayIntersect * intersect;
    RenderSettings Settings;
    SOP_Node * Geo;

};

#endif //NPRG045_RENDERER_HPP
