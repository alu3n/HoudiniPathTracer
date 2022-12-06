//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../../Physics/include/Optics.hpp"
#include "../include/BxDF.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"

std::array<float,3> operator*(const std::array<float,3> & A,const std::array<float,3> & B){
    return {A[0]*B[0],A[1]*B[1],A[2]*B[2]};
}

RGBRadiance operator*(const std::array<float,3> & A, const RGBRadiance & B){
    return {A[0]*B[0].amount,A[1]*B[1].amount,A[2]*B[2].amount};
}

//RGBRadiance operator*(float a, const RGBRadiance & B){
//    return {a*B[0].amount,a*B[1].amount,a*B[2].amount};
//}

constexpr float incIOR = 1;
constexpr float outIOR = 1.5;
constexpr int phongEXP = 10;

UT_Vector3F PerfectReflection(UT_Vector3F incomming, UT_Vector3F normal){
    return incomming - (dot(normal,incomming)*normal)*2;
}

std::array<float, 3>
BSDF::EvaluateBRDF(const TextureData & textureData, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir) {
    auto normal = normalDir;

    auto fresnell = ReflectionCoefficient(incommingDir,normal,incIOR,outIOR); //reflected:refracted
    auto refractedCoeff = 1/(fresnell+1);
    auto reflectedCoeff = 1-refractedCoeff;
    auto perfectDir = PerfectReflection(incommingDir,normal);

    auto diffuse = dot(incommingDir,normal) * (1-textureData.Transparency);
    auto specular = pow(dot(perfectDir,outgoingDir),phongEXP);
    auto C = textureData.DiffuseColor;

    float R = C[0]*diffuse*refractedCoeff+reflectedCoeff*specular;
    float G = C[1]*diffuse*refractedCoeff+reflectedCoeff*specular;
    float B = C[2]*diffuse*refractedCoeff+reflectedCoeff*specular;

    return {R,G,B};
}

UT_Vector3F BSDF::GenerateReflection(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir) {
    auto normal = normalDir;

    auto normalInSpherical = CartesianToSpherical(normal);
    auto azimuth = Generator::GenerateF01()*2*M_PI;
    auto zenith = Generator::GenerateF01()*M_PI-0.5*M_PI;
    auto nextPath = SphericalCoords(azimuth,zenith);
    nextPath.zenith += normalInSpherical.zenith;
    nextPath.azimuth += normalInSpherical.azimuth;
    auto randomPath = SphericalToCartesian(nextPath);
    auto temp = textureData.ReflectionRoughness * randomPath + (1-textureData.ReflectionRoughness) * PerfectReflection(incommingDir,normal);
    if(Norm(temp) == 0){
        std::cout << "ACHTUNG BxDF" << std::endl;
    }

    return Normalize(temp);
//    return{0,1,0};
}

//constexpr float ratioIOR = 0.75;

std::array<float, 3> BSDF::EvaluateBSDF(const TextureData & textureData) {
    return {1,1,1};
}


UT_Vector3F BSDF::GenerateRefraction(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir, float IOR1, float IOR2) {
//    UT_Vector3F normal;
//    float IOR1 = 1;
//    float IOR2 = 1.5;

//    if(dot(normalDir,incommingDir) > 0){
//        IOR1 = 1;
//        IOR2 = textureData.IOR;
//        normal = normalDir;
//    }
//    else{
//        IOR1 = textureData.IOR;
//        IOR2 = 1;
//        normal = -normalDir;
//    }

//    auto ratioIOR = ReflectionCoefficient(incommingDir,normal,IOR1,IOR2);
//    auto ratioIOR = IOR1/IOR2;
//    auto normal = dot(normalDir,incommingDir) > 0 ? normalDir : (-1)*normalDir; //Flip normal if inside object :)
//    return -normal;
//    return normal;
    auto l = incommingDir;
    auto n = normalDir;

    auto n12 = IOR1/IOR2;
    float dt = dot(l,n);

    auto c1 = 1 - dt*dt;
    c1 = n12*n12*c1;
    c1 = 1 - c1;
    c1 = sqrt(c1);
    c1 = n12*dt-c1;
    auto A = c1*n;
    auto B = n12*l;
    return A - B;


//    auto d = incommingDir;
//    auto n = normalDir;
//
//    auto dt = dot(d,n);
//    auto r = IOR1/IOR2;
//
//    auto A = dt * n;
//    A = d - A;
//    A = r * A;
//
//    auto b = dt*dt;
//    b = 1 - b;
//    b = (r*r)*b;
//    b = 1 - b;
//    b = sqrt(b);
//
//    auto B = b*n;
//    B = (-1)*B;
//
//    std::cout << "A: " << A << std::endl;
//    std::cout << "B: " << B << std::endl;

//    UT_Vector3F rtrval = A + B;

//    std::cout << "R: " << rtrval << std::endl;

//    return rtrval;



//    auto internalPath = (ratioIOR*dot(normal,incommingDir)-sqrt(1-pow(ratioIOR,2)*(1-dot(normal,incommingDir))))*normal - ratioIOR * (incommingDir);
//    return internalPath;
}