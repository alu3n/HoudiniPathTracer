//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "PathTracer.hpp"

#include <iostream>

PathTracer::PathTracer(std::vector<const GU_Detail *> geo, std::vector<OBJ_Light *> lights, OBJ_Camera * camera, fpreal32 time) {
    LoadGeo(geo,time);
    LoadLights(lights,time);
    LoadCamera(camera,time);
}

void PathTracer::LoadGeo(std::vector<const GU_Detail *> geo, fpreal32 time) {

}

void PathTracer::LoadLights(std::vector<OBJ_Light *> lights, fpreal32 time) {

}

void PathTracer::LoadCamera(OBJ_Camera *camera, fpreal32 time) {

    auto translate = UT_Vector3F(
        camera->evalFloat("t", 0, time),
        camera->evalFloat("t", 1, time),
        camera->evalFloat("t", 2, time)
    );

    auto rotate = UT_Vector3F(
        camera->evalFloat("r", 0, time),
        camera->evalFloat("r", 1, time),
        camera->evalFloat("r", 2, time)
    );

    auto resolution = UT_Vector2i(
        camera->evalInt("res",0,time),
        camera->evalInt("res",1,time)
    );

    float focalLength = camera->evalFloat("focal",0,time);

    float aperture = camera->evalFloat("aperture",0,time);
//
    std::cout << translate << std::endl;
    std::cout << rotate << std::endl;
    std::cout << resolution << std::endl;
    std::cout << focalLength << std::endl;
    std::cout << aperture << std::endl;
//
}