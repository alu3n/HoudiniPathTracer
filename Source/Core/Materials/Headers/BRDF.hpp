//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_BRDF_HPP
#define NPRG045_BRDF_HPP

#include <array>
#include "../../Mathematics/Headers/Vectors.hpp"
#include "../../Physics/Headers/Radiometry.hpp"
#include "../../Textures/Headers/Texture.hpp"

class BRDF{
public:
    virtual void Load(Texture * texture, UT_Vector3F position);
    virtual std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing) = 0;
    virtual UT_Vector3F GenerateSample() = 0;
private:

};

class PBBRDF : public BRDF{

};

#endif //NPRG045_BRDF_HPP
