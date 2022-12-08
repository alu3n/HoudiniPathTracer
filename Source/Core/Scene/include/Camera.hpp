//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_CAMERA_HPP
#define NPRG045_CAMERA_HPP

#include <OBJ/OBJ_Camera.h>
#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>

#include "../../Mathematics/include/Sampling.hpp"

class Camera{
public:
    Camera(OBJ_Camera * cam, OP_Context & context);
    GU_Ray GenerateRay(UT_Vector2i);
    UT_Vector2i ImageResolution{0,0};
private:
    void LoadCamera(OP_Context & context);

    OBJ_Camera * CameraNode;

    float FocalLength{0};
    float Aperture{0};
    float fstop{0};
    float focus{0};

    UT_Vector4F CornerPosition{0,0,0,0}; //Negative X, positive Y, negative Z
    UT_Vector4F XIncrement{0,0,0,0}; //Increment to get corner of next pixel in X direction
    UT_Vector4F YIncrement{0,0,0,0}; //Increment to get corner of next pixel in Y direction
    UT_Vector4F ZIncrement{0,0,0,0};
    UT_Vector4F Origin{0,0,0,0};
};

#endif //NPRG045_CAMERA_HPP
