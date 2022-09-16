//
// Created by Vojtěch Pröschl on 06.09.2022.
//

#include "SampleGenerators.hpp"

fpreal SampleGenerator::Generate01D1() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

UT_Vector2F SampleGenerator::Generate01D2() {
    //Todo: Create better solution
    return {
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX)
    };
}

UT_Vector3F SampleGenerator::Generate01D3() {
    return {
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX)
    };
}

UniformGenerator::UniformGenerator(float seed) {

}

//Todo: Use better library for random generation

fpreal UniformGenerator::Generate01D1() {
    float x = ((float)(rand()))/RAND_MAX;
    return x;
}

UT_Vector2F UniformGenerator::Generate01D2() {
    float x = ((float)(rand()))/RAND_MAX;
    float y = ((float(rand())))/RAND_MAX;
    return {x,y};
}

UT_Vector3F UniformGenerator::Generate01D3() {
    float x = ((float)(rand()))/RAND_MAX;
    float y = ((float(rand())))/RAND_MAX;
    float z = ((float(rand())))/RAND_MAX;
    return {x,y,z};
}
