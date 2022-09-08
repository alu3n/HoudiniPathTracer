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

//ImageMatrix Renderer::RenderTile(fpreal time, int tx0, int tx1, int ty0, int ty1) {
//    ImageMatrix image;
////    LoadFrame(time);
////    std::cout << ty0 << ":" << ty1 << std::endl;
//    for(int y = ty0; y <= ty1; ++y){
//        image.push_back({});
////        std::cout << y << std::endl;
//        for(int x = tx0; x <= tx1; ++x){
//            image.back().push_back(RenderPixel({x,y}));
//        }
//    }
//
////    std::cout << image.size() << std::endl;
//
//    return image;
//}

//void Renderer::LoadFrame(fpreal time) {
//    OP_Context context(time);
//    GU_DetailHandle * temp = static_cast<GU_DetailHandle *>(Geo->getCookedData(context));
//    intersect = new GU_RayIntersect(temp->gdp());
//}


void WhittedRayTracer::LoadFrame(fpreal time) {
    OP_Context context(time);
    GU_DetailHandle * temp = static_cast<GU_DetailHandle *>(Geo->getCookedData(context));
    intersect = new GU_RayIntersect(temp->gdp());
    color = GA_ROHandleV3(temp->gdp(),GA_ATTRIB_PRIMITIVE,"Cd");
    normal = GA_ROHandleV3(temp->gdp(),GA_ATTRIB_VERTEX,"N");
    gdp = temp->gdp();
}

int sampleCount = 5;

ImageMatrix WhittedRayTracer::RenderTile(fpreal time, int tx0, int tx1, int ty0, int ty1) {
    ImageMatrix image;

    for(int y = ty0; y <= ty1; ++y){
        image.push_back({});
        for(int x = tx0; x <= tx1; ++x){
            UT_Vector4F color{0,0,0,0};
            for(int i = 0; i < sampleCount; ++i){
                color += 0.1*RenderPixel({x,y});
            }
//            image.back().push_back(0.1*color);
            image.back().push_back(color);
        }
    }

    return image;
}


UT_Vector3F WhittedRayTracer::ComputeNormal(const GU_RayInfo &rayInfo) {
    UT_Vector3F rtrval = {0,0,0};
    UT_Array<GA_Offset> vtxOffsets;
    UT_Array<float> weights;
    rayInfo.myPrim->computeInteriorPointWeights(vtxOffsets,weights,rayInfo.myU,rayInfo.myV,rayInfo.myW);

    for(int i = 0; i < vtxOffsets.size(); ++i){
        rtrval += weights[i] * normal.get(vtxOffsets[i]);
    }

    return rtrval;
}

UT_Vector4F WhittedRayTracer::RenderPixel(UT_Vector2i pixelCoords) {
    GU_RayInfo info;
    info.init();
    auto ray = Settings.Cam.GenerateRay(pixelCoords);
    int count = intersect->sendRay(ray.org,ray.dir,info);
    if(count == 0){
        return {0,0,0,1};
    }

    auto nrml = ComputeNormal(info);

    return Shade(ray.dir, nrml,ray.org+info.myT*ray.dir,5);
}

//Todo: Place this function outside the camera class... I wasn't able to find norm function
UT_Vector3F normalize(UT_Vector3F vec){
    float scale = sqrt(vec.x()*vec.x()+vec.y()*vec.y()+vec.z()*vec.z());
    return (1/scale)*vec;
}

float reflectivity = 1;

UT_Vector4F WhittedRayTracer::Shade(const UT_Vector3F &dir, const UT_Vector3F &N, const UT_Vector3F &intPos,
                                    int Recursion) {
    float lambert;
    UT_Vector4F rtrvec;

    for(int i = 0; i < 3; ++i){
        auto lightNonNormalized = PointLightPosition[i] - intPos;
        auto illuminationDirection = normalize(lightNonNormalized);
        auto val = dot(N, illuminationDirection);
        lambert += (val < 0) ? 0 : val;
    }

    rtrvec = {lambert,lambert,lambert,0};

    if(Recursion > 1){
//        std::cout
        auto reflectionDirection = dir - 2*dot(dir,N)*N;
        GU_RayInfo info;
        info.init();
        int count = intersect->sendRay(intPos+0.00001*reflectionDirection,reflectionDirection,info);
        if(count != 0){
            auto refNormal = ComputeNormal(info);
            rtrvec = (0.5 + 0.5*(1-reflectivity))*rtrvec + (0.5*reflectivity)* Shade(reflectionDirection,refNormal,intPos+info.myT*reflectionDirection,Recursion-1);
        }
    }


//    auto lambert = dot(dir,N);
//    std::cout << lambert << std::endl;

    return rtrvec;
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


WhittedRayTracer::WhittedRayTracer(RenderSettings settings, SOP_Node *geo) : Renderer(settings, geo) {

}