//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_UTILITY_HPP
#define NPRG045_UTILITY_HPP


#include "../../Physics/Headers/Quantities.hpp"

#include <vector>

struct ImageCoordinates{
    ImageCoordinates(int tx0, int tx1, int ty0, int ty1);
    int tx0; //(tx0,ty0) is the top left corner and (tx1,ty1) is the bottom right corner
    int tx1;
    int ty0;
    int ty1;
};

struct ImageTile{
    ImageTile(ImageCoordinates viewCoordinates);
    ImageTile(ImageCoordinates viewCoordinates, ImageCoordinates renderCoordinates);
    ImageCoordinates viewCoords;
    ImageCoordinates renderCoords;
    int sampleCount{0};
    std::vector<std::vector<Color>> data;
};

struct Image{
    Image(int imageResX, int imageResY, int tileResX, int tileResY);
    std::vector<ImageTile> data{};
};


#endif //NPRG045_UTILITY_HPP
