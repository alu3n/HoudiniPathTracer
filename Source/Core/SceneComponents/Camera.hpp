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


//TODO: This implementation does not sampling in

class Camera{
public:
    Camera(OBJ_Camera * cam, OP_Context & context);
    GU_Ray GenerateRay(UT_Vector2i, OP_Context & context); //Slower due to the parameter loading
    GU_Ray GenerateRay(UT_Vector2i);
    UT_Vector2i ImageResolution;
private:
    void LoadCamera(OP_Context & context);

    OBJ_Camera * CameraNode;
//    fpreal LastTimepoint; //Todo: Maybe add check to avoid reloading camera /w same timepoint


    fpreal FocalLength;
    fpreal Aperture;

    UT_Vector4F CornerPosition; //Negative X, positive Y, negative Z
    UT_Vector4F XIncrement; //Increment to get corner of next pixel in X direction
    UT_Vector4F YIncrement; //Increment to get corner of next pixel in Y direction
    UT_Vector4F Origin;
};



//class Camera{
//public:
////    Camera(UT_Vector2i resolution, float focalLength, float aperture);
//    Camera(OBJ_Camera * cam,fpreal32 time);
//    GU_Ray GenerateRay(UT_Vector2i pixel);
//private:
//    void LoadFromCameraNode(OBJ_Camera,fpreal32 time);
//
//    OBJ_Camera * CameraNode;
//
//    UT_Vector2i Resolution;
//    float FocalLength;
//    float Aperture;
//
//    UT_Vector3F CornerPosition; //Negative X, positive Y, negative Z
//    UT_Vector3F XIncrement; //Increment to get corner of next pixel in X direction
//    UT_Vector3F YIncrement; //Increment to get corner of next pixel in Y direction
//    UT_Vector3F Origin;
//};

#endif //NPRG045_CAMERA_HPP
