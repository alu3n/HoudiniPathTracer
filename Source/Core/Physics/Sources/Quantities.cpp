//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../Headers/Quantities.hpp"

Color operator+(const Color & C1, const Color & C2){
    Color temp = C1;
    temp.R.amount += C2.R.amount;
    temp.G.amount += C2.G.amount;
    temp.B.amount += C2.B.amount;
    temp.alpha += C2.alpha;
    return temp;
}

Color operator*(float a,const Color & C){
    Color temp = C;
    temp.R.amount *= a;
    temp.G.amount *= a;
    temp.B.amount *= a;
    temp.alpha *= a;
    return temp;
}