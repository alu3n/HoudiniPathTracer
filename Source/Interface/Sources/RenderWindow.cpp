//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../Headers/RenderWindow.hpp"

#include <iostream>

void RenderWindow::DisplayTile(const ImageTile &tile) {
    Device->writeTile(ConvertTile(tile),tile.viewCoords.tx0,tile.viewCoords.tx1,tile.viewCoords.ty0,tile.viewCoords.ty1);
}

void RenderWindow::Open(UT_Vector2i imageResolution, UT_Vector2i tileResolution) {
    std::cout << "COSYK" << std::endl;

    Device = IMG_TileDevice::newDevice(DeviceName.data());

    auto info = new IMG_TileOptions;

    info->setPlaneInfo(Filename.data(),imagePlaneDefinition.Name,0,imagePlaneDefinition.Format,imagePlaneDefinition.ColorModel);

    if(!Device->open(*info,imageResolution.x(),imageResolution.y(),tileResolution.x(),tileResolution.y(),1)){
        std::cout << "There was a problem with opening render view!" << std::endl;
    }
}

//void RenderWindow::WriteTile(const ImageTile &tile) {
//    Device->writeTile(ConvertTile(tile),tile.coords.tx0,tile.coords.tx1,tile.coords.ty0,tile.coords.ty1);
//}

void *RenderWindow::ConvertTile(const ImageTile &tile) {
    int rx = tile.viewCoords.tx1 - tile.viewCoords.tx0;
    int ry = tile.viewCoords.ty1 - tile.viewCoords.ty0;

    int pixelCount = rx * ry;
    int wordCount = pixelCount * IMGvectorSize(imagePlaneDefinition.ColorModel);
    int byteCount = wordCount * IMGbyteSize(imagePlaneDefinition.Format);

    void *tileData = malloc(byteCount);

    float *ptr = (float *)tileData;

    for(int y = 0; y <= ry; ++y){
        for(int x = 0; x <= rx; ++x){
            auto pixel = tile.data[x][y];
            *ptr++ = pixel.R.amount;
            *ptr++ = pixel.G.amount;
            *ptr++ = pixel.B.amount;
            *ptr++ = pixel.alpha;
        }
    }

    *((char *)ptr) += wordCount * IMGbyteSize(imagePlaneDefinition.Format);

    return tileData;
}