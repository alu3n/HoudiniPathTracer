//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_RENDERER_HPP
#define NPRG045_RENDERER_HPP

#include "../../Scene/Headers/Scene.hpp"
#include "Utility.hpp"

class Renderer{
public:
    virtual void LoadScene(const Scene & scene);
    virtual void ImproveTile(ImageTile & tile,int sampleCount);
protected:
    Scene scene;
};

#endif //NPRG045_RENDERER_HPP
