//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_CAMERA_HPP
#define NPRG045_CAMERA_HPP

#include "../../Mathematics/Headers/Sampling.hpp"

#include <OBJ/OBJ_Camera.h>
#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>

class Camera{
public:
    Camera(OBJ_Camera * cam, OP_Context & context);
    GU_Ray GenerateRay(UT_Vector2i);
    UT_Vector2i ImageResolution;
private:
    void LoadCamera(OP_Context & context);

    OBJ_Camera * CameraNode;

    float FocalLength;
    float Aperture;

    Generator generator;

    UT_Vector4F CornerPosition; //Negative X, positive Y, negative Z
    UT_Vector4F XIncrement; //Increment to get corner of next pixel in X direction
    UT_Vector4F YIncrement; //Increment to get corner of next pixel in Y direction
    UT_Vector4F ZIncrement;
    UT_Vector4F Origin;
};

#endif //NPRG045_CAMERA_HPP
