//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_RENDERER_HPP
#define NPRG045_RENDERER_HPP

#include "../../Scene/Headers/Scene.hpp"
#include "Utility.hpp"
#include <map>

class Renderer{
public:
    Renderer(Scene myScene) : scene(myScene){}
    virtual void ImproveTile(ImageTile & tile,int sampleCount) = 0;
protected:
    Scene scene;
};

#endif //NPRG045_RENDERER_HPP
