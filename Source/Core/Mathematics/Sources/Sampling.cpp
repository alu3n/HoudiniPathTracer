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

//Todo: Maybe chose different random generator

float SampleGenerator::Uniform01() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

UT_Vector2F SampleGenerator::Uniform01V2() {
    return {Uniform01(), Uniform01()};
}

UT_Vector3F SampleGenerator::Uniform01V3() {
    return {Uniform01(), Uniform01(), Uniform01()};
}

PolarCoordinates SampleGenerator::UniformDisk(float diskRadius) {
    return {diskRadius * sqrt(Uniform01()),static_cast<float>(2.0*M_PI*Uniform01())};
}

UT_Vector3F SampleGenerator::CosineWeightedHemisphereSample() {
    auto u = Uniform01V2();
    return {
        static_cast<float>(sqrt(u.x()) * cos(2*M_PI*u.y())),
        static_cast<float>(sqrt(u.x()) * sin(2*M_PI*u.y())),
        sqrt(1-u.x())
    };
}

UT_Vector3F SampleGenerator::PhongSample() {

}

UT_Vector3F SampleGenerator::GXXSample() {

}
