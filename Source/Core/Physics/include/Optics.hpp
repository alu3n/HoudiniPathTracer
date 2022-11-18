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

float ReflectionCoefficient(UT_Vector3F incomming, UT_Vector3F normal, float IOR1, float IOR2);


#endif //NPRG045_GEOMETRICALOPTICS_HPP
