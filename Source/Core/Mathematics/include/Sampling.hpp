//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_SAMPLING_HPP
#define NPRG045_SAMPLING_HPP

#include "Coordinates.hpp"

//#include <UT/UT_Vector2.h>
//#include <UT/UT_Vector3.h>
#include <array>


//Default generator is uniform

class Generator{
public:
    static float GenerateF01();
    static float GenerateFRange(float min, float max);
    static int GenerateIRange(int min, int max);

    template<int num>
    static std::array<float,num> GenerateF01(){
        std::array<float,num> temp;
        for (int i = 0; i < num; ++i) {
            temp[i] = GenerateF01();
        }
        return temp;
    }

    template<int num>
    static std::array<float,num> GenerateFRange(float min, float max){
        std::array<float,num> temp;
        for (int i = 0; i < num; ++i) {
            temp[i] = GenerateFRange(min,max);
        }
    }

    template<int num>
    static std::array<int,num> GenerateIRange(int min, int max){
        std::array<int,num> temp;
        for (int i = 0; i < num; ++i) {
            temp[i] = GenerateIRange(min,max);
        }
        return temp;
    }
};




#endif //NPRG045_SAMPLING_HPP
