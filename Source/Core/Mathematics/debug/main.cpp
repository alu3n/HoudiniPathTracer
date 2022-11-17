//
// Created by Vojtěch Pröschl on 17.11.2022.
//

#include <iostream>
#include "../include/LinearAlgebra.hpp"

int main(){
    auto test = Matrix<3,3>({{1,2,3},{4,5,6},{7,8,9}});
    std::array<std::array<float,2>,2> test = {{1,2}};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << test[i][j] << std::endl;
        }
    }
    std::cout << "Test" << std::endl;
}