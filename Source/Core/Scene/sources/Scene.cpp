//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Scene.hpp"

Scene::Scene(Lights myLights, Camera myCamera, Geometry myGeometry) : lights(myLights), geometry(myGeometry), camera(myCamera){}