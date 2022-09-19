//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../../Mathematics/Headers/Vectors.hpp"
#include "../Headers/Camera.hpp"

Camera::Camera(OBJ_Camera *cam, OP_Context &context) {
    CameraNode = cam;
    LoadCamera(context);
    generator = Generator();
}

GU_Ray Camera::GenerateRay(UT_Vector2i PixelCoords) {
    auto sample = generator.Generate01F2();

//    std::cout << YIncrement << std::endl;

    auto sensorPos = (PixelCoords.x() + sample.x())*XIncrement + (PixelCoords.y() + sample.y())*YIncrement + CornerPosition;
    auto directionVector = sensorPos - Origin;

    UT_Vector3F dir3 = {directionVector.x(),directionVector.y(),directionVector.z()};

    UT_Vector3F org = {sensorPos.x(),sensorPos.y(),sensorPos.z()};
    UT_Vector3F dir = Normalize<2>(dir3);

    return {org,dir};
}

void Camera::LoadCamera(OP_Context &context) {
    auto time = context.getTime();

    ImageResolution = UT_Vector2i(
            CameraNode->evalInt("res", 0, time),
            CameraNode->evalInt("res", 1, time)
    );

    UT_Matrix4F worldTransform{0};// = CameraNode->getPreTransform();

    FocalLength = CameraNode->evalFloat("focal", 0, time) / 1000.0; //mm -> m
    Aperture = CameraNode->evalFloat("aperture", 0, time) / 1000.0; //mm -> m

    CameraNode->getLocalToWorldTransform(context,worldTransform);

    XIncrement = UT_Vector4F(Aperture / ImageResolution.x(), 0, 0, 0)*worldTransform;
    YIncrement = UT_Vector4F(0, Aperture / ImageResolution.x(), 0, 0)*worldTransform;
    ZIncrement = UT_Vector4F(0, 0, -FocalLength,0)*worldTransform;
    Origin = UT_Vector4F(0, 0, 0, 1)*worldTransform;

    CornerPosition = Origin - (ImageResolution.x()/2)*XIncrement - (ImageResolution.y()/2)*YIncrement + ZIncrement;
}