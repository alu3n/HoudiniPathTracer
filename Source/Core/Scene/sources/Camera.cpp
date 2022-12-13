//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Camera.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"


Camera::Camera(OBJ_Camera *cam, OP_Context &context, int resX, int resY, float focalLength, float aperature, float fStop, float focusDistance) {
    CameraNode = cam;
    LoadCamera(context,resX,resY,focalLength,aperature,fStop,focusDistance);
}


GU_Ray Camera::GenerateRay(UT_Vector2i PixelCoords) {
    auto sample = Generator::GenerateF01<2>();


    auto sensorPos = (PixelCoords.x() + sample[0])*XIncrement + (PixelCoords.y() + sample[1])*YIncrement + CornerPosition;
    auto directionVector = sensorPos - Origin;

    UT_Vector3F dir3 = {directionVector.x(),directionVector.y(),directionVector.z()};

    UT_Vector3F org = {sensorPos.x(),sensorPos.y(),sensorPos.z()};
    UT_Vector3F dir = Normalize(dir3);

    UT_Vector3F planeNormal = {ZIncrement.x(),ZIncrement.y(),ZIncrement.z()};
    planeNormal = Normalize(planeNormal);
    auto pointOnFocusPlane = org + focus*planeNormal;
    float d = -dot(pointOnFocusPlane,planeNormal);

    auto t = -(dot(org,planeNormal)+d)/dot(dir,planeNormal);
    auto P = org + t*dir;

    UT_Vector3F XIncr = {XIncrement.x(),XIncrement.y(),XIncrement.z()};
    XIncr = Normalize(XIncr);

    UT_Vector3F YIncr = {YIncrement.x(),YIncrement.y(),YIncrement.z()};
    YIncr = Normalize(YIncr);

    UT_Vector3F Orig = {Origin.x(),Origin.y(),Origin.z()};

    auto aperaturePos = Orig + Generator::GenerateF01()*fstop*XIncr + Generator::GenerateF01()*fstop*YIncr;
    auto newDir = P - aperaturePos;
    newDir = Normalize(newDir);

    return {aperaturePos,newDir};
}

void Camera::LoadCamera(OP_Context & context, int resX, int resY, float focalLength, float aperature, float fStop, float focusDistance) {
    ImageResolution = {resX,resY};

    UT_Matrix4F worldTransform{0};

    FocalLength = focalLength / 1000.0; //mm -> m
    Aperture = aperature / 1000.0; //mm -> m
    fstop = 1/fStop;
    focus = focusDistance;

    CameraNode->getLocalToWorldTransform(context,worldTransform);

    XIncrement = UT_Vector4F(Aperture / ImageResolution.x(), 0, 0, 0)*worldTransform;
    YIncrement = UT_Vector4F(0, Aperture / ImageResolution.x(), 0, 0)*worldTransform;
    ZIncrement = UT_Vector4F(0, 0, -FocalLength,0)*worldTransform;
    Origin = UT_Vector4F(0, 0, 0, 1)*worldTransform;

    CornerPosition = Origin - (ImageResolution.x()/2)*XIncrement - (ImageResolution.y()/2)*YIncrement + ZIncrement;
}