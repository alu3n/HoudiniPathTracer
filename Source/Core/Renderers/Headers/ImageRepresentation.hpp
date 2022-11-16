//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#ifndef NPRG045_IMAGEREPRESENTATION_HPP
#define NPRG045_IMAGEREPRESENTATION_HPP

#include <vector>
#include <UT/UT_Vector3.h>


struct Color{
    float r;
    float g;
    float b;
    float a;
    Color(float,float,float,float);
    Color(float,float,float);
};

Color operator+(Color A, Color B);
Color operator-(Color A, Color B);
Color operator*(float a,Color C);
Color operator/(Color C, float a);


struct ImageCoordinates{
    ImageCoordinates(int tx0, int tx1, int ty0, int ty1);
    int tx0; //(tx0,ty0) is the top left corner and (tx1,ty1) is the bottom right corner
    int tx1;
    int ty0;
    int ty1;
};



struct ImageTile{
    ImageTile(ImageCoordinates viewCoordinates, size_t tileId);
    ImageTile(ImageCoordinates viewCoordinates, ImageCoordinates renderCoordinates, size_t tileId);
    ImageCoordinates viewCoords;
    ImageCoordinates renderCoords;
    int sampleCount{0};
    std::vector<std::vector<Color>> data;
    size_t tileId;
};

struct Image{
    Image(int imageResX, int imageResY, int tileResX, int tileResY);
    std::vector<ImageTile> data{};
};

#endif //NPRG045_IMAGEREPRESENTATION_HPP
