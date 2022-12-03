//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_GEOMETRICALOPTICS_HPP
#define NPRG045_GEOMETRICALOPTICS_HPP

/* TODO:
 * - [ ] Ideal specular reflection
 * - [ ] Ideal refraction
 */

#include <UT/UT_Vector.h>

//This tells us how much light is reflected
float ReflectionCoefficient(UT_Vector3F vectorToSource, UT_Vector3F normal, float travelingFromIOR, float travelingToIOR);


#endif //NPRG045_GEOMETRICALOPTICS_HPP
