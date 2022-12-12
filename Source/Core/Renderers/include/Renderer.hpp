//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_RENDERER_HPP
#define NPRG045_RENDERER_HPP

#include "ImageRepresentation.hpp"
#include "../../Scene/include/Scene.hpp"

/*
 * This is predecessor for all render engines. If you want to implement new render engine you should
 * base it on this class.
 */

class Renderer{
public:
    Renderer(Scene myScene) : scene(myScene){}
    virtual void ImproveTile(ImageTile & tile,int sampleCount) = 0;
protected:
    Scene scene;
};

#endif //NPRG045_RENDERER_HPP
