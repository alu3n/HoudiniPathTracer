//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "WhittedRayTracer.hpp"

#include <SOP/SOP_Node.h>
#include <GU/GU_Detail.h>
#include <GA/GA_Handle.h>
#include <GU/GU_PrimPart.h>
#include <GA/GA_Handle.h>
#include <GA/GA_Types.h>
#include <PRM/PRM_Include.h>


//void WhittedRayTracer::LoadFrame(fpreal time) {
//    OP_Context context(time);
//    GU_DetailHandle * temp = static_cast<GU_DetailHandle *>(Geo->getCookedData(context));
//    intersect = new GU_RayIntersect(temp->gdp());
//    color = GA_ROHandleV3(temp->gdp(),GA_ATTRIB_PRIMITIVE,"Cd");
//    normal = GA_ROHandleV3(temp->gdp(),GA_ATTRIB_VERTEX,"N");
//    gdp = temp->gdp();
//}

//int sampleCount = 5;

void WhittedRayTracer::Load(Camera *camera, const std::vector<Light> &lights, fpreal time) {
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

float reflectivity = 0.5;


UT_Vector4F WhittedRayTracer::Shade(const GU_Ray &ray, const GU_RayInfo &info,UT_Vector3F N,UT_Vector3F Cd, int recursionDepth){
    float lambert = 0;

    UT_Vector4F rtrvec(0,0,0,0);
    auto intPos = ray.org + info.myT * ray.dir;
//    auto N = IntersectionVertexNormal(info);

//    std::cout << N << std::endl;

//    auto N = info.myNml;

    for(int i = 0; i < 3; ++i){
        auto lightNonNormalized = PointLightPosition[i] - intPos;
        auto illuminationDirection = normalize(lightNonNormalized);
        auto val = dot(N, illuminationDirection);
        lambert += (val < 0) ? 0 : val;
    }

//    auto Cd = IntersectionPointColor(info);
//    rtrvec = {lambert,lambert,lambert,0};
    rtrvec = {Cd.x()*lambert,Cd.y()*lambert,Cd.z()*lambert,0};
//    return rtrvec;

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

//UT_Vector4F WhittedRayTracer::Shade(GU_RayInfo &info, GU_Ray & ray, int recursionDepth) {
////    if(!info.myTValid){
////        return {0,0,0,1};
////    }
//
//
//
////    auto t = (*info.myHitList)(0).t;//->array();
//
//
//
//    return {0,0,0,0};
//
//    auto first = (*info.myHitList)(0);//[0]
//
////    if(!info.myTValid) return {0,0,0,1};
//
//    UT_Vector3F normal;
//    first.prim->evaluateNormalVector(normal,first.u,first.v,first.w);
//    std::cout << normal << info.myNml << std::endl;
//    //    info.myPrim->evalua
//
//    auto intPos = ray.org + info.myTmax*ray.dir;
//
////    info.myPrim.offset();
////    info.myPrim->evaluateNormalVector()
//
//    float lambert = 0;
//
//    for(int i = 0; i < 3; ++i){
//        auto lightNonNormalized = PointLightPosition[i] - intPos;
//        auto illuminationDirection = normalize(lightNonNormalized);
//        lambert += dot(normal, illuminationDirection);
//    }
//
//
//
//    UT_Vector3F geoColor = color.get(info.myPrim.offset());
////    UT_Vector3F geoColor = {1,1,1};
//
//
//    UT_Vector4F illumination = {lambert*geoColor.x(),lambert*geoColor.y(),lambert*geoColor.z(),0};
//
////    if(info.myTValid && recursionDepth > 0){
//////        ray.dir *= (-1);
////        UT_Vector3F recursiveDir = ray.dir - 2*dot(ray.dir,info.myNml)*info.myNml;
////        GU_RayInfo recursiveInfo;
////        GU_Ray recursiveRay{intPos+recursiveDir*0.0001,recursiveDir};
////
////        intersect->sendRay(recursiveRay.org,recursiveDir,recursiveInfo);
////
//////        return Shade(recursiveInfo,recursiveRay,recursionDepth-1);
////        illumination *= 0.5 + (reflectivity * 0.5);
////        illumination += (0.5 * reflectivity) * Shade(recursiveInfo,recursiveRay,recursionDepth-1);
////    }
//
//    return illumination;
//}


//WhittedRayTracer::WhittedRayTracer(oldRenderSettings settings, SOP_Node *geo) : oldRenderer(settings, geo) {
//
//}