//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../Headers/Utility.hpp"


ImageCoorinates::ImageCoorinates(int tx0, int tx1, int ty0, int ty1) {
    this->tx0 = tx0;
    this->tx1 = tx1;
    this->ty0 = ty0;
    this->ty1 = ty1;
}

ImageTile::ImageTile(ImageCoorinates coordinates) : coords(coordinates) {
    int sx = coordinates.tx1 - coordinates.tx0;
    int sy = coordinates.ty1 - coordinates.ty0;

    for(int x = 0; x <= sx; ++x){
        data.push_back({});
        for(int y = 0; y <= sy; ++y){
            data.back().push_back(Color());
        }
    }
}