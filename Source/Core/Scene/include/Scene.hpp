//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_SCENE_HPP
#define NPRG045_SCENE_HPP

#include "Light.hpp"
#include "Camera.hpp"
#include "Geometry.hpp"

#include <vector>

using Lights = std::vector<Light *>;

struct Scene{
    Scene(Lights,Camera,Geometry);
    Lights lights;
    Camera camera;
    Geometry geometry;
};

#endif //NPRG045_SCENE_HPP
