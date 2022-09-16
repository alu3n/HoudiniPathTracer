//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_BXDF_HPP
#define NPRG045_BXDF_HPP

#include <UT/UT_Vector3.h>

/* Notation:
 * ALL VECTORS ARE POINTING AWAY FROM THE INTERSECTION AND ARE NORMALIZED
 * L ... Vector pointing to the light
 * V ... Observation vector
 * N ... Surface normal
 * H ... Halfway vector
 * R ... Ideal reflection vector
 * T ... Tangent vector perpendicular to surface normal
 * P ... Intersection point
 * ThetaI ... Angle between N and L vector
 * ThetaV angle between N and V vector
 */

struct Sample{
    float Multiplier;
    UT_Vector3F Direction;
};

class BRDF{
public:
    virtual float Evaluate() = 0; //Evaluates brdf
    virtual Sample RaySample() = 0; //Generates ray and multiplier (pdf)
    virtual Sample EvaluateIndirect() = 0; //Generates ray and multiplier (pdf,brdf)
    virtual float PDF() = 0; //Generates pdf multiplier
    void LoadData(UT_Vector3F L, UT_Vector3F V, UT_Vector3F N, UT_Vector3F H, UT_Vector3F R, UT_Vector3F T, UT_Vector3F P);
protected:
    UT_Vector3F L;
    UT_Vector3F V;
    UT_Vector3F N;
    UT_Vector3F H;
    UT_Vector3F R;
    UT_Vector3F T;
    UT_Vector3F P;
};

class BTDF{

};

class BSDF{

};

#endif //NPRG045_BXDF_HPP
