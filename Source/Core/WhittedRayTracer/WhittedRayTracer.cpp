//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "WhittedRayTracer.hpp"
#include "../Utility/Math.hpp"
#include "../Utility/SampleGenerators.hpp"

//#include "../BRDF/RoughDielectric.hpp"
#include "../BRDF/old_PrincipledShader.hpp"
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

//float reflectivity = 0.4;
//float phongCoeff = 100;
//float ks = 100;
//float kd = 0.7;




float kd = 0.1;
float ks = 0.9;
float n = 1000;


constexpr float pi = 3.14159265359;

//float PhongDiffuse(){
//    return kd * (1 / M_PI);
//}

static UniformGenerator gen(100.2);

static float pDiff = kd * (1 / M_PI);

static float PhongSpecular(float alpha){
//    return ks * ((n+2)/(M_PI*2))*(pow(alpha,n));
//    return ks * pow(alpha,n);
    return pow(alpha,n);
}

static UT_Vector3F IdealReflection(UT_Vector3F wi, UT_Vector3F N){
    return wi - 2 * dot(wi,N)*N;
}

static float PhongBRDF(float alpha){
//    auto reflection = IdealReflection(wi,N);
//    float alpha = dot(wo,reflection);
//    return PhongSpecular(alpha);
    return pDiff + PhongSpecular(alpha);
}

static UT_Vector2F PhongDiffuseRay(){
    float u1 = gen.Generate01D1();
    float u2 = gen.Generate01D1();
    float theta = acos(sqrt(u1));
    float phi = 2.0 * M_PI * u2;
    return {theta,phi};
}

static UT_Vector2F PhongSpecularRay(){
    float u1 = gen.Generate01D1();
    float u2 = gen.Generate01D1();
//    std::cout << u2 << std::endl;
    float theta = acos(pow(u1,1.0/(n+1.0)));
//    std::cout << theta << std::endl;
    float phi = 2 * M_PI * u2;
//    float phi = acos(pow(u2,1.0/(n+1.0)));
    return {theta,phi};
}

static UT_Vector3F ToCartesian(UT_Vector2F spherical){
    return {
        cos(spherical.x()) * sin(spherical.y()),
        sin(spherical.x()) * sin(spherical.y()),
        cos(spherical.y())
    };
}

static auto shader = old_PrincipledShader();

UT_Vector4F WhittedRayTracer::Shade(const GU_Ray &ray, const GU_RayInfo &info,UT_Vector3F N,UT_Vector3F Cd, int recursionDepth){
    float totalLight = 0;
    auto ideal = IdealReflection(ray.dir,N);

    UT_Vector4F rtrvec(0,0,0,0);
//    return rtrvec;

    auto intPos = ray.org + info.myT * ray.dir;

    for(auto && light : lights){
        auto sample = light->GenerateSample();
        auto L = sample.myPosition - intPos;
        auto Ln = myNormalize(L);

        GU_RayInfo shadowInfo;
        shadowInfo.init();

        if(intersect->sendRay(intPos+0.001*Ln,Ln,shadowInfo) > 0){
            if(shadowInfo.myT < 1) continue;
        }

//        auto idealLight = IdealReflection(Ln,N);
//        auto angle = dot(idealLight,ray.dir);
//
        auto distance = myNorm(L);
//        auto coeff = PhongBRDF(angle > 0 ? angle : 0);
        auto coeff = shader.DielectricBRDF(Ln,ray.dir,N);

//        auto coeff = angle;
//        auto coeff = PhongSpecular(dot(idealLight,ray.dir));
//        auto coeff = ((n+2)/(M_PI*2))*dot(idealLight,ray.dir);
//        auto coeff = PhongSpecular(dot(ideal,(-1)*ray.dir));
//        auto coeff = dot(idealLight,ray.dir);
        auto mult = dot(Ln,N);

        totalLight += coeff * ( 1 / (distance * distance) ) * sample.myIntensity * (mult > 0 ? mult : 0);
    }

    UT_Vector4F rtrval {totalLight * Cd.x(),totalLight * Cd.y(),totalLight * Cd.z(),0};

//    return rtrval;

    if(recursionDepth == 0) return rtrval;

    auto reflection = shader.DielectricReflection(ray.dir,N);
    UT_Vector3F recursionDirection = get<0>(reflection);

    GU_RayInfo reflectionInfo;
    reflectionInfo.init();
    if(intersect->sendRay(0.0001*recursionDirection + intPos,recursionDirection,reflectionInfo)){
        auto refNormal = IntersectionVertexNormal(info);
        auto refCd = IntersectionPointColor(info);
        GU_Ray refRay = {intPos,recursionDirection};

        auto idealRef = IdealReflection(ray.dir,N);
        auto angle = dot(idealRef,refRay.dir);

        auto mult = dot(recursionDirection,N);
        rtrval += shader.DielectricBRDF(recursionDirection,ray.dir,N)*Shade(refRay,reflectionInfo,refNormal,refCd,recursionDepth-1)*(mult > 0 ? mult : 0);
//        rtrval += shader.DielectricBRDF(recursionDirection,ray.dir,N)*Shade(refRay,reflectionInfo,refNormal,refCd,recursionDepth-1)*(mult > 0 ? mult : 0);
    }

    return rtrval;


}

WhittedRayTracer::WhittedRayTracer(SOP_Node *geo) : RenderEngine(geo) {

}
