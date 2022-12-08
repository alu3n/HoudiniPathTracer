//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_GEOMETRICALOPTICS_HPP
#define NPRG045_GEOMETRICALOPTICS_HPP

#include <UT/UT_Vector.h>


UT_Vector3F PerfectReflection(UT_Vector3F observationDir, UT_Vector3F normalDir);
UT_Vector3F PerfectRefraction(UT_Vector3F observationDir, UT_Vector3F normalDir, float IOR1, float IOR2);
float SchlickApproximation(UT_Vector3F vectorToSource, UT_Vector3F normal, float travelingFromIOR, float travelingToIOR);


#endif //NPRG045_GEOMETRICALOPTICS_HPP
