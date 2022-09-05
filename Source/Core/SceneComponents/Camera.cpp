//
// Created by Vojtěch Pröschl on 05.09.2022.
//


#include "Camera.hpp"

#include <exception>
#include <OBJ/OBJ_Node.h>
#include <OBJ/OBJ_Camera.h>

//Camera::Camera(UT_Vector2i resolution, float focalLenght, float aperture) {
//    Resolution = resolution;
//    FocalLength = focalLenght/1000.0;
//    Aperture = aperture/1000.0;
//
//    XIncrement = UT_Vector3F(Aperture/resolution.x(),0,0);
//    YIncrement = UT_Vector3F(0,-XIncrement.x(),0);
//    CornerPosition = UT_Vector3F(-Aperture/2,XIncrement.x()*resolution.y()/2,FocalLength);
//    Origin = UT_Vector3F(0,0,0);
//}

Camera::Camera(OBJ_Camera *camera, fpreal32 time) {
    CameraNode = camera;

    Resolution = UT_Vector2i(
            camera->evalInt("res",0,time),
            camera->evalInt("res",1,time)
    );
    FocalLength = camera->evalFloat("focal",0,time)/1000.0;
    Aperture = camera->evalFloat("aperture",0,time)/1000.0;

    XIncrement = UT_Vector3F(Aperture/Resolution.x(),0,0);
    YIncrement = UT_Vector3F(0,-XIncrement.x(),0);
    CornerPosition = UT_Vector3F(-Aperture/2,XIncrement.x()*Resolution.y()/2,FocalLength);
    Origin = UT_Vector3F(0,0,0);

    UT_DMatrix4 world_xform;
    OP_Context context(time);
    camera->getInverseLocalToWorldTransform(context,world_xform);
    Origin = Origin*world_xform;
}


GU_Ray Camera::GenerateRay(UT_Vector2i pixel) {
    //Todo: Generate rays with respect to certain distribution, cook, improve speed

    if (pixel.x() < 0 || pixel.x() >= Resolution.x() || pixel.y() < 0 || pixel.y() >= Resolution.y()) {
        throw std::invalid_argument("Pixel must be in a range supported by the camera!");
    }

    auto projectionPlaneIntersection = CornerPosition + (0.5+pixel.x()) * XIncrement + (0.5+pixel.y()) * YIncrement;
    auto position = projectionPlaneIntersection - Origin;

    float scale = sqrt(position.x()*position.x() + position.y()*position.y()+ position.z()*position.z());

    return {position,(1/scale)*position};
    //Todo: normalize the vector
}
