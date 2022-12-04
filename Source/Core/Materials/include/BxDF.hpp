//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_BXDF_HPP
#define NPRG045_BXDF_HPP

#include <array>
//#include "../../Mathematics/include/Vectors.hpp"
#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Radiometry.hpp"
#include "Texture.hpp"

//Maybe move those functions elsewhere
std::array<float,3> operator*(const std::array<float,3> &,const std::array<float,3> &);
RGBRadiance operator*(const std::array<float,3> &, const RGBRadiance &);
//RGBRadiance operator*(float , const RGBRadiance &);

class BSDF{
public:
//    void LoadTextureData();
    std::array<float,3> EvaluateBRDF(const TextureData &, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    std::array<float,3> EvaluateBSDF(const TextureData &);
    UT_Vector3F GenerateReflection(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    UT_Vector3F GenerateRefraction(const TextureData &);
private:
    std::array<float,3> EvaluateDiffuseBRDF();
    std::array<float,3> EvaluateSpecularBRDF();

    float n1; //IOR of medium from which the ray is traveling
    float n2; //IOR of medium to which the ray is traveling
};



//class BRDF{
//public:
//    void Load(Texture * texture, UT_Vector3F position);
//    virtual std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing, UT_Vector3F normal) = 0;
//    virtual UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) = 0;
//    TextureData data{{0,0,0},0,0,0};
//};
//
//class BTDF{
//public:
//    void Load(Texture * texture, UT_Vector3F position);
//    virtual std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing, UT_Vector3F normal) = 0;
//    virtual UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) = 0;
//    TextureData data{{0,0,0},0,0,0};
//};
//
//class BSDF{
//public:
//    void Load(Texture * texture, UT_Vector3F position);
//    BRDF * brdf;
//    BTDF * btdf;
//};

#endif //NPRG045_BXDF_HPP
