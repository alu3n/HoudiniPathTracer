//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_BXDF_HPP
#define NPRG045_BXDF_HPP

#include <array>
#include "Texture.hpp"
#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Units.hpp"

/*
 * This class is representing BSDF, which is combination of BRDF and BTDF
 * It houses methods for both evaluating BRDF adn generating samples
 */

class BSDF{
public:
    static RGBEnergy EvaluateBRDF(const TextureData &, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    static RGBEnergy EvaluateSpecularBRDF(const TextureData &, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    static RGBEnergy EvaluateDiffuseBRDF(const TextureData &, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir);

    static RGBEnergy EvaluateBTDF(const TextureData &);

    static UT_Vector3F GenerateReflection(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir);
    static UT_Vector3F GenerateRefraction(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir, float IOR1, float IOR2);
};

#endif //NPRG045_BXDF_HPP
