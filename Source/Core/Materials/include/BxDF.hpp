//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_BXDF_HPP
#define NPRG045_BXDF_HPP

#include <array>
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
    UT_Vector3F GenerateRefraction(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir, float IOR1, float IOR2);
private:
    std::array<float,3> EvaluateDiffuseBRDF();
    std::array<float,3> EvaluateSpecularBRDF();

    float n1; //IOR of medium from which the ray is traveling
    float n2; //IOR of medium to which the ray is traveling
};

#endif //NPRG045_BXDF_HPP
