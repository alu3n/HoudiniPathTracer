//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Sampling.hpp"

float Generator::GenerateF01() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int Generator::GenerateIRange(int min, int max) {
    auto rand = Generator::GenerateF01();
    rand*=(max-min+1);
    return ((int)rand)+min;
}

float Generator::GenerateFRange(float min, float max) {
    auto dist = max - min;
    return min + GenerateF01()*dist;
}
