//
// Created by Vojtěch Pröschl on 18.11.2022.
//

#include "../../Physics/include/Optics.hpp"
#include "../include/PB_BxDF.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"





//float max(float a, float b){
//    return a < b ? b : a;
//}
//
//float min(float a, float b){
//    return a < b ? a : b;
//}
//
//float D_PHONG(UT_Vector3F normal, UT_Vector3F halfway,float phongExp){
//    auto dt = dot(normal,halfway);
//    return max(0,dt)*((phongExp+2)/(2*M_PI))*pow(dt,phongExp);
//}
//
//float G_CookTorrance(UT_Vector3F light, UT_Vector3F view, UT_Vector3F halfway, UT_Vector3F normal){
//    auto dtvh = dot(view,halfway);
//    auto dtnh = dot(normal,halfway);
//    auto dtnv = dot(normal,view);
//    auto dtnl = dot(normal,light);
//
//    auto A = 2*(dtnh*dtnv)/(dtvh);
//    auto B = 2*(dtnh*dtnl)/(dtvh);
//
//    return min(1,min(A,B));
//}
//
////float D_GGX(UT_Vector3F normal, UT_Vector3F halfway,float roughness){
////    auto dt = dot(normal,halfway);
////    auto roughness2 = roughness*roughness;
////    return (max(0.0,dt)*roughness2)/
////    (M_PI*pow(dt,4)*(roughness2+pow(tan())))
////}
//
//UT_Vector3F PerfectReflection(UT_Vector3F incomming, UT_Vector3F normal){
//    return incomming - (dot(normal,incomming)*normal)*2;
//}
//
//float phongExp = 20;
//
//std::array<float, 3> PB_BRDF::Evaluate(UT_Vector3F VectorPointingToObserver, UT_Vector3F VectorPointingToLightSource, UT_Vector3F normal) {
//    return {1,1,1};
//    UT_Vector3F halfway = Norm(VectorPointingToObserver+VectorPointingToLightSource)*(VectorPointingToObserver+VectorPointingToLightSource);
//
//    auto dtnl = dot(normal,VectorPointingToLightSource);
//    auto dtnv = dot(normal,VectorPointingToObserver);
//
//
//    auto fresnell = ReflectionCoefficient(VectorPointingToLightSource,normal,1.5,1);
//    auto D = D_PHONG(normal,halfway,phongExp);
//    auto G = G_CookTorrance(VectorPointingToLightSource,VectorPointingToObserver,halfway,normal);
//
//    auto val = (fresnell/4)*((D*G)/(dtnv*dtnl));
//
//    return {val,val,val};
//}
//
//
//UT_Vector3F PB_BRDF::GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) {
//    auto normalInSpherical = CartesianToSpherical(normal);
//    auto azimuth = Generator::GenerateF01()*2*M_PI;
//    auto zenith = Generator::GenerateF01()*M_PI-0.5*M_PI;
//    auto nextPath = SphericalCoords(azimuth,zenith);
//    nextPath.zenith += normalInSpherical.zenith;
//    nextPath.azimuth += normalInSpherical.azimuth;
//    auto randomPath = SphericalToCartesian(nextPath);
//
////    return Normalize(data.Roughness * randomPath + (1-data.Roughness) * PerfectReflection(incomming,normal));
//    return randomPath;
////    return PerfectReflection(incomming,normal);
//}
//
////std::array<float, 3> PB_BTDF::Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing, UT_Vector3F normal) {
////
////
////    return {1,1,1};
////}
////
////UT_Vector3F PB_BTDF::GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) {
////    return {0,1,0};
////}
////
////PB_BSDF::PB_BSDF() {
////    this->brdf = new PB_BRDF();
////    this->btdf = new PB_BTDF();
////}
//
//
