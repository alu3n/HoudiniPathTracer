//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../Headers/Sampling.hpp"

float Generator::Generate01F1() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

UT_Vector2F Generator::Generate01F2() {
    return {Generate01F1(),Generate01F1()};
}

UT_Vector3F Generator::Generate01F3() {
    return {Generate01F1(),Generate01F1(),Generate01F1()};
}