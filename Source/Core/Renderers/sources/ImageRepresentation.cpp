//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#include <iostream>
#include <algorithm>
#include <random>
#include <stdexcept>
#include "../include/ImageRepresentation.hpp"

Color operator+(Color A, Color B){
    return {A.r+B.r,A.g+B.g,A.b+B.b,A.a+B.a};
}

Color operator-(Color A, Color B){
    return {A.r-B.r,A.g-B.g,A.b-B.b,A.a-B.a};
}

Color operator*(float a,Color C){
    return {C.r*a,C.g*a,C.b*a,C.a};
}

Color operator/(Color C, float a){
    if(a == 0){
        throw std::invalid_argument( "zero division error" );
    }
    return {C.r/a,C.g/a,C.b/a,C.a};
}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 0;
}

Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}




ImageTile::ImageTile(ImageCoordinates coordinates, size_t id) : viewCoords(coordinates) {
    int sx = coordinates.tx1 - coordinates.tx0;
    int sy = coordinates.ty1 - coordinates.ty0;

    for(int x = 0; x <= sx; ++x){
        data.push_back({});
        for(int y = 0; y <= sy; ++y){
            data.back().push_back(Color(0,0,0,0));
        }
    }
}

ImageTile::ImageTile(ImageCoordinates viewCoordinates, ImageCoordinates renderCoordinates, size_t id) : viewCoords(viewCoordinates){
    int sx = viewCoordinates.tx1 - viewCoordinates.tx0;
    int sy = viewCoordinates.ty1 - viewCoordinates.ty0;

    for(int x = 0; x <= sx; ++x){
        data.push_back({});
        for(int y = 0; y <= sy; ++y){
            data.back().push_back(Color{0,0,0,0});
        }
    }
}

Image::Image(int imageResX, int imageResY, int tileResX, int tileResY) {
    int fullTilesX = imageResX / tileResX;
    int fullTilesY = imageResY / tileResY;

    size_t id = 0;

    for(int x = 0; x < fullTilesX; ++x){
        for(int y = 0; y < fullTilesY; ++y){
            data.push_back(ImageTile{{x * tileResX, (x + 1) * tileResX-1, y * tileResY, (y + 1) * tileResY-1},id});
            ++id;
        }
    }

    if(imageResX % tileResX != 0 && imageResY % tileResY != 0){
        int cx0 = fullTilesX*tileResX;
        int cx1 = cx0+tileResX-1;
        int cy0 = fullTilesY*tileResY;
        int cy1 = cy0+tileResY-1;

        int rx1 = tileResX - 1;
        int ry1 = tileResY - 1;

        data.push_back({{cx0,cx1,cy0,cy1},{cx0,rx1,cy0,ry1},id});
        ++id;
    }
    if(imageResX % tileResX != 0){
        int cx0 = fullTilesX*tileResX;
        int cx1 = cx0+tileResX-1;

        int rx1 = tileResX - 1;

        for(int y = 0; y < fullTilesY; ++y){
            int cy0 = y*tileResY;
            int cy1 = cy0 + tileResY - 1;
            data.push_back({{cx0,cx1,cy0,cy1},{cx0,rx1,cy0,cy1},id});
            ++id;
        }
    }
    if(imageResY % tileResY != 0){
        int cy0 = fullTilesY*tileResY;
        int cy1 = cy0+tileResY-1;

        int ry1 = tileResY - 1;

        for(int x = 0; x < fullTilesX; ++x){
            int cx0 = x*tileResX;
            int cx1 = cx0 + tileResX - 1;
            data.push_back({{cx0,cx1,cy0,cy1},{cx0+1,cx1,cy0,ry1},id});
            ++id;
        }
    }
    //This might require complete rework of the tile rendering system though
    auto rng = std::default_random_engine {};
    std::shuffle(data.begin(),data.end(),rng);
}