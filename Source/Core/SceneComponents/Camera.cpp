//
// Created by Vojtěch Pröschl on 05.09.2022.
//


#include "Camera.hpp"
#include "../Utility/Math.hpp"

#include <iostream>
#include <exception>
#include <OBJ/OBJ_Node.h>
#include <OBJ/OBJ_Camera.h>

//Todo: Place this function outside the camera class... I wasn't able to find norm function
UT_Vector4F normalize(UT_Vector4F vec){
    float scale = sqrt(vec.x()*vec.x()+vec.y()*vec.y()+vec.z()*vec.z());
    return (1/scale)*vec;
}

Camera::Camera(OBJ_Camera *cam,OP_Context & context) {
    CameraNode = cam;
    LoadCamera(context);
    generator = UniformGenerator(123.0);
}

GU_Ray Camera::GenerateRay(UT_Vector2i PixelCoords) {
//    if (PixelCoords.x() < 0 || PixelCoords.x() >= ImageResolution.x() || PixelCoords.y() < 0 || PixelCoords.y() >= ImageResolution.y()) {
//        throw std::invalid_argument("Pixel must be in a range supported by the camera!");
//    }
//
    PixelCoords.y() = ImageResolution.y() - PixelCoords.y();
//
//    auto sample = generator.Generate01D2();
//
//    auto positionOnSensor = CornerPosition + (sample.x()+PixelCoords.x()) * XIncrement + (sample.y()+PixelCoords.y()) * YIncrement;
//    auto directionVector = Origin - CornerPosition;
//
//    UT_Vector3F dir3 = {directionVector.x(),directionVector.y(),directionVector.z()};
//
//    UT_Vector3F dir = myNormalize(dir3);
//    UT_Vector3F org = UT_Vector3F(positionOnSensor.x(),positionOnSensor.y(),positionOnSensor.z());
//    return {org,dir};

    auto sample = generator.Generate01D2();

    auto sensorPos = (PixelCoords.x() + sample.x())*XIncrement + (PixelCoords.y() + sample.y())*YIncrement + CornerPosition;
    auto directionVector = sensorPos - Origin;

    UT_Vector3F dir3 = {directionVector.x(),directionVector.y(),directionVector.z()};

    UT_Vector3F org = {sensorPos.x(),sensorPos.y(),sensorPos.z()};
    UT_Vector3F dir = myNormalize(dir3);

//    std::cout << dir << std::endl;

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

    auto worldTransform = CameraNode->getPreTransform();
//    auto transform = CameraNode->

    FocalLength = CameraNode->evalFloat("focal", 0, time) / 1000.0; //mm -> m
    Aperture = CameraNode->evalFloat("aperture", 0, time) / 1000.0; //mm -> m

//    UT_Matrix4D worldTransform;

    CameraNode->getLocalToWorldTransform(context,worldTransform);

    XIncrement = UT_Vector4F(Aperture / ImageResolution.x(), 0, 0, 0)*worldTransform;
    YIncrement = UT_Vector4F(0, -XIncrement.x(), 0, 0)*worldTransform;
    ZIncrement = UT_Vector4F(0, 0, -FocalLength,0)*worldTransform;
    Origin = UT_Vector4F(0, 0, 0, 1)*worldTransform;

    CornerPosition = Origin - (ImageResolution.x()/2)*XIncrement - (ImageResolution.y()/2)*YIncrement + ZIncrement;
    std::cout << "Corner position: "<< CornerPosition << std::endl;
    std::cout << "Origin: "<< Origin << std::endl;
    std::cout << "X: " << XIncrement << " : " << myNorm({XIncrement.x(),XIncrement.y(),XIncrement.z()})<< std::endl;
    std::cout << "Y: " << YIncrement << " : " << myNorm({YIncrement.x(),YIncrement.y(),YIncrement.z()})<< std::endl;
    std::cout << "Z: " << ZIncrement << " : " << myNorm({ZIncrement.x(),ZIncrement.y(),ZIncrement.z()})<< std::endl;
}

