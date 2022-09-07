//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "WhittedRayTracer.hpp"

#include <SOP/SOP_Node.h>
#include <GU/GU_Detail.h>

void WhittedRayTracer::LoadFrame(int frame) {
    OP_Context context(1.0/frame);
    GU_DetailHandle * temp = static_cast<GU_DetailHandle *>(Geo->getCookedData(context));
    intersect = new GU_RayIntersect(temp->gdp());
}

ImageMatrix WhittedRayTracer::RenderImage(int frame){
    LoadFrame(frame);

    ImageMatrix image;
    int pixelCount = Settings.Cam.ImageResolution.x()*Settings.Cam.ImageResolution.y();
    int pixelNow = 0;



    //Todo: Create better implementation that would support parallelism
    for(int px = 0; px < Settings.Cam.ImageResolution.x(); ++px){
        image.push_back({});
        for(int py = 0; py < Settings.Cam.ImageResolution.y(); ++py){
//            std::cout << "Rendering pixel: " << pixelNow << " of " << pixelCount << std::endl;
            image[px].push_back(RenderPixel({px,py},frame));
            pixelNow++;
        }
    }
    return image;
}

UT_Vector3F WhittedRayTracer::RenderPixel(UT_Vector2i pixelCoords, int frame) {
    UT_Vector3F colorBuffer{0,0,0};

    int sampleCount = 1;

    for(int i = 0; i < sampleCount; ++i){
        GU_RayInfo info;
        auto ray = Settings.Cam.GenerateRay(pixelCoords);
        intersect->sendRay(ray.org,ray.dir,info);
        colorBuffer += Shade(info,ray);
    }
//    return colorBuffer;
    float multiplier = 1.0/sampleCount;
    return multiplier*colorBuffer;
//    UT_Vector3F rtrColor(0.1*colorBuffer.x(),0.1*colorBuffer.x(),0.1*colorBuffer.x());

//    return rtrColor;
//    return Shade(info,ray);
}

//Todo: Place this function outside the camera class... I wasn't able to find norm function
UT_Vector3F normalize(UT_Vector3F vec){
    float scale = sqrt(vec.x()*vec.x()+vec.y()*vec.y()+vec.z()*vec.z());
    return (1/scale)*vec;
}

UT_Vector3F WhittedRayTracer::Shade(GU_RayInfo &info, GU_Ray & ray) {
    if(!info.myTValid) return {0,0,0};

    auto intPos = ray.org + info.myTmax*ray.dir;
    auto illuminationDirection = normalize(PointLightPosition - intPos);
    auto lambert = dot(info.myNml,illuminationDirection);
    return {lambert,lambert,lambert};
//    info.myNml;
}


WhittedRayTracer::WhittedRayTracer(RenderSettings settings, SOP_Node *geo) : Renderer(settings, geo) {

}