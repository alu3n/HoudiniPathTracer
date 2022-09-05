//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_CAMERA_HPP
#define NPRG045_CAMERA_HPP

#include <OBJ/OBJ_Camera.h>
#include <GU/GU_RayIntersect.h>
#include <GU/GU_RayPrimitive.h>


/*
 * Camera is implemented according to SideFX documentation of their camera (although it has support only for fraction of parameters atm)
 * https://www.sidefx.com/docs/houdini/nodes/obj/cam.html
 */

class Camera{
public:
    Camera(UT_Vector2i resolution, float focalLength, float aperture);
    Camera(OBJ_Camera * cam,fpreal32 time);
    GU_Ray GenerateRay(UT_Vector2i pixel);
private:
    UT_Vector2i Resolution;
    float FocalLength;
    float Aperture;

    UT_Vector3F CornerPosition; //Negative X, positive Y, negative Z
    UT_Vector3F XIncrement; //Increment to get corner of next pixel in X direction
    UT_Vector3F YIncrement; //Increment to get corner of next pixel in Y direction
    UT_Vector3F Origin;
};

#endif //NPRG045_CAMERA_HPP
