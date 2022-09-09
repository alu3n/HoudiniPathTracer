//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_OLDRENDERER_HPP
#define NPRG045_OLDRENDERER_HPP

#include "SceneComponents/Camera.hpp"

#include <OBJ/OBJ_Light.h>
#include <vector>
#include <array>


using ImageMatrix = std::vector<std::vector<UT_Vector4F>>;

struct oldRenderSettings{
    oldRenderSettings() = default;
    oldRenderSettings(Camera cam, int fps);
    Camera Cam; //Todo: Put info such as shutterspeed etc. into camera
    int FPS;
};

//Todo: Change image matrix to RGBA

class oldRenderer{
public:
    oldRenderer(oldRenderSettings settings, SOP_Node * geo);
    virtual ImageMatrix RenderTile(fpreal time, int tx0, int tx1, int ty0, int ty1) = 0;
    virtual void LoadFrame(fpreal time) = 0;
protected:
    virtual UT_Vector4F RenderPixel(UT_Vector2i pixelCoords) = 0;
    oldRenderSettings Settings;
    SOP_Node * Geo;

};

#endif //NPRG045_OLDRENDERER_HPP
