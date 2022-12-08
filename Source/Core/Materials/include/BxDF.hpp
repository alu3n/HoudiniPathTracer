//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_BXDF_HPP
#define NPRG045_BXDF_HPP

#include <array>
#include "Texture.hpp"
#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Radiometry.hpp"


//Todo: Move those functions to separate header!
std::array<float,3> operator*(const std::array<float,3> &,const std::array<float,3> &);
RGBRadiance operator*(const std::array<float,3> &, const RGBRadiance &);

//Todo: Maybe make the BRDF static

class BSDF{
public:
    static std::array<float,3> EvaluateBRDF(const TextureData &, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    static std::array<float,3> EvaluateSpecularBRDF(const TextureData &, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    static std::array<float,3> EvaluateDiffuseBRDF(const TextureData &, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir);

    static std::array<float,3> EvaluateBTDF(const TextureData &);

    static UT_Vector3F GenerateReflection(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    static UT_Vector3F GenerateRefraction(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir, float IOR1, float IOR2);
};

#endif //NPRG045_BXDF_HPP
