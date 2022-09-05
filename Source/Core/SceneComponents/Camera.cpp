//
// Created by Vojtěch Pröschl on 05.09.2022.
//


#include "Camera.hpp"

#include <iostream>
#include <exception>
#include <OBJ/OBJ_Node.h>
#include <OBJ/OBJ_Camera.h>

//Todo: Place this function outside the camera class... I wasn't able to find norm function
UT_Vector4F normalize(UT_Vector4F vec){
    float scale = sqrt(vec.x()*vec.x()+vec.y()*vec.y()+vec.z()*vec.z());
    return (1/scale)*vec;
}

Camera::Camera(OBJ_Camera *cam, OP_Context & context) {
    CameraNode = cam;
    LoadCamera(context);
}

GU_Ray Camera::GenerateRay(UT_Vector2i PixelCoords) {
    if (PixelCoords.x() < 0 || PixelCoords.x() >= ImageResolution.x() || PixelCoords.y() < 0 || PixelCoords.y() >= ImageResolution.y()) {
        throw std::invalid_argument("Pixel must be in a range supported by the camera!");
    }

    //Todo: Add other sampling methods ... this is just generating ray in the center of the pixel
    auto positionOnSensor = CornerPosition + (0.5+PixelCoords.x()) * XIncrement + (0.5+PixelCoords.y()) * YIncrement;
    auto directionVector = positionOnSensor - Origin;

    auto dir4 = normalize(directionVector);


    UT_Vector3F dir = UT_Vector3F(dir4.x(),dir4.y(),dir4.z());
    UT_Vector3F org = UT_Vector3F(positionOnSensor.x(),positionOnSensor.y(),positionOnSensor.z());
    return {org,dir};
}

GU_Ray Camera::GenerateRay(UT_Vector2i PixelCoords, OP_Context & context) {
    LoadCamera(context);
    return GenerateRay(PixelCoords);
}

void Camera::LoadCamera(OP_Context &context) {
    auto time = context.getTime();

    ImageResolution = UT_Vector2i(
            CameraNode->evalInt("res", 0, time),
            CameraNode->evalInt("res", 1, time)
    );

    FocalLength = CameraNode->evalFloat("focal", 0, time) / 1000.0; //mm -> m
    Aperture = CameraNode->evalFloat("aperture", 0, time) / 1000.0; //mm -> m

    UT_Matrix4D worldTransform;
    CameraNode->getLocalToWorldTransform(context,worldTransform);

    std::cout << worldTransform << std::endl;

    XIncrement = UT_Vector4F(Aperture / ImageResolution.x(), 0, 0, 0)*worldTransform;
    YIncrement = UT_Vector4F(0, -XIncrement.x(), 0, 0)*worldTransform;
    CornerPosition = UT_Vector4F(-Aperture / 2, XIncrement.x() * ImageResolution.y() / 2, -FocalLength, 1)*worldTransform;
    Origin = UT_Vector4F(0, 0, 0, 1)*worldTransform;
}

