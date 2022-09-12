//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "WhittedRayTracer.hpp"
#include "../Utility/Math.hpp"

#include <SOP/SOP_Node.h>
#include <GU/GU_Detail.h>
#include <GA/GA_Handle.h>
#include <GU/GU_PrimPart.h>
#include <GA/GA_Handle.h>
#include <GA/GA_Types.h>
#include <PRM/PRM_Include.h>


void WhittedRayTracer::Load(Camera *camera, const std::vector<Light*> &lights, fpreal time) {
    RenderEngine::Load(camera,lights,time);
    intersect = new GU_RayIntersect(gdh->gdp());
}

ImageMatrix WhittedRayTracer::RenderTile(int sampleCount, int tx0, int tx1, int ty0, int ty1) {
    ImageMatrix image;

    float coeff = 1.0/sampleCount;

    for(int y = ty0; y <= ty1; ++y){
        image.push_back({});
        for(int x = tx0; x <= tx1; ++x){
            UT_Vector4F color{0,0,0,0};
            for(int i = 0; i < sampleCount; ++i){
                color += RenderPixel({x,y});
            }
            image.back().push_back(coeff*color);
        }
    }

    return image;
}


UT_Vector4F WhittedRayTracer::RenderPixel(UT_Vector2i pixelCoords) {
    GU_RayInfo info;
    info.init();

    auto ray = camera->GenerateRay(pixelCoords);
    int count = intersect->sendRay(ray.org,ray.dir,info);
    if(count == 0){
        return {0,0,0,1};
    }

    auto N = IntersectionVertexNormal(info);
    auto Cd = IntersectionPointColor(info);

    return Shade(ray,info,N,Cd,5);
}

//Todo: Place this function outside the camera class... I wasn't able to find norm function
UT_Vector3F normalize(UT_Vector3F vec){
    float scale = sqrt(vec.x()*vec.x()+vec.y()*vec.y()+vec.z()*vec.z());
    return (1/scale)*vec;
}

float reflectivity = 0.4;
float phongCoeff = 100;
float ks = 100;
float kd = 0.7;

UT_Vector4F WhittedRayTracer::Shade(const GU_Ray &ray, const GU_RayInfo &info,UT_Vector3F N,UT_Vector3F Cd, int recursionDepth){
    float lambert = 0;
    float phng = 0;

    UT_Vector4F rtrvec(0,0,0,0);
    auto intPos = ray.org + info.myT * ray.dir;

    for(auto && light : lights){
        auto sample = light->GenerateSample();
        auto L = sample.myPosition - intPos;
        auto illuminationDirection = normalize(L);

        GU_RayInfo shadowInfo;
        shadowInfo.init();

        if(intersect->sendRay(intPos+0.001*illuminationDirection,illuminationDirection,shadowInfo) > 0){
            if(shadowInfo.myT < 1){
                continue;
            }
        }

        auto lightDistance = myNorm(L);
        auto coeff = 1/(lightDistance*lightDistance);

        auto h = (1.0/myNorm(illuminationDirection+ray.dir))*(illuminationDirection+ray.dir);

        auto phong = coeff * sample.myIntensity * pow(myMax(0,dot(N,h)),phongCoeff);


        auto val = coeff*sample.myIntensity*myMax(dot(N, illuminationDirection),0);
        lambert += kd*val;
        phng = ks*phong;
    }

    rtrvec = {Cd.x()*lambert+phng,Cd.y()*lambert+phng,Cd.z()*lambert+phng,0};

    if(recursionDepth > 1){
        auto reflectionDirection = ray.dir - 2*dot(ray.dir,N)*N;
        GU_RayInfo reflectionInfo;
        reflectionInfo.init();
        int count = intersect->sendRay(intPos+0.001*reflectionDirection,reflectionDirection,reflectionInfo);
        if(count != 0){
            auto refNormal = IntersectionVertexNormal(info);
            auto refCd = IntersectionPointColor(info);
            GU_Ray refRay = {intPos,reflectionDirection};
            rtrvec = (0.5 + 0.5*(1-reflectivity))*rtrvec + (0.5*reflectivity)* Shade(refRay,reflectionInfo,refNormal,refCd,recursionDepth-1);
        }
    }

    return rtrvec;
}

WhittedRayTracer::WhittedRayTracer(SOP_Node *geo) : RenderEngine(geo) {

}
