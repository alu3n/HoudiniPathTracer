//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Optics.hpp"

float SchlickApproximation(UT_Vector3F vectorToSource, UT_Vector3F normal, float travelingFromIOR, float travelingToIOR){
    auto R0 = pow(((travelingFromIOR-travelingToIOR)/(travelingFromIOR+travelingToIOR)),2);
    return R0 + (1-R0)*pow(1-dot(vectorToSource,normal),5);
}

UT_Vector3F PerfectReflection(UT_Vector3F observationDir, UT_Vector3F normalDir){
    return observationDir - (dot(normalDir,observationDir)*normalDir)*2;
}

UT_Vector3F PerfectRefraction(UT_Vector3F observationDir, UT_Vector3F normalDir, float IOR1, float IOR2){
    auto n12 = IOR1/IOR2;
    float dt = dot(observationDir,normalDir);

    auto c1 = 1 - dt*dt;
    c1 = n12*n12*c1;
    c1 = 1 - c1;
    c1 = sqrt(c1);
    c1 = n12*dt-c1;
    auto A = c1*normalDir;
    auto B = n12*observationDir;
    auto perfect = A - B;
    return perfect;
}