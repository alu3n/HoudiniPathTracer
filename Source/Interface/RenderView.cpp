//
// Created by Vojtěch Pröschl on 06.09.2022.
//


#include "RenderView.hpp"
#include <iostream>
//#include <UT_Vector4>
#include <UT/UT_Vector4.h>


RenderView::RenderView(UT_Vector2i ImageRes, UT_Vector2i TileRes) {
    TileResX = TileRes.x();
    TileResY = TileRes.y();
    ImageResX = ImageRes.x();
    ImageResY = ImageRes.y();
}

void *RenderView::makeTile() {
    int pixels = TileResX * TileResY;
    int words = pixels * IMGvectorSize(imagePlane.ColorModel);
    int bytes = words * IMGbyteSize(imagePlane.Format);

    void *tileData = malloc(bytes);

    float*ptr = (float *)tileData;

    for(int c = 0; c < words; ++c){
        *ptr++ = 1.0 / (c+1);
        *ptr++ = 0;
        *ptr++ = 0;
        *ptr++ = 0;

        c++;
        c++;
        c++;
    }

    *((char *)ptr) += words * IMGbyteSize(imagePlane.Format);

    return tileData;
}




void RenderView::sendPlaneDefinitions(IMG_TileDevice *dev, const UT_String &host, const UT_String &port) {
//    IMG_TileOptionList oplist;
    auto finfo = new IMG_TileOptions(); //Todo: memory leaking ... remove this when window is destroyed
    finfo->setPlaneInfo("Render View", imagePlane.Name, 0, imagePlane.Format, imagePlane.ColorModel);
//    finfo->setFormatOption("sockethost",host);
//    finfo->setFormatOption("socketport",port);
//    oplist.append(std::move(finfo));
    if(!dev->open(*finfo,ImageResX,ImageResY,TileResX,TileResX,1)){
        std::cout << "ERROR OPENING DEVICE" << std::endl;
    }
}

void RenderView::Open() {
    Device = IMG_TileDevice::newDevice("ip");

//    std::cout << "Opening..." << std::endl;
    sendPlaneDefinitions(Device,"host","port");
//    std::cout << "Opened..." << std::endl;

    //Todo: Write this a bit more cleanly

    void *tileData = makeTile();
    for (int ty = 0; ty < ImageResY; ty+=TileResY) {
        for (int tx = 0; tx < ImageResX; tx+=TileResX) {
//            std::cout << SYSmin(tx+TileResX, ImageResX)-1 << std::endl;
            writeTile(Device,tileData,tx, SYSmin(tx+TileResX, ImageResX)-1,ty,SYSmin(ty+TileResY,ImageResY)-1);
//            break;
        }
//        break;
    }
//    std::cout << "Finished writing" << std::endl;
//    Device->flush();

//    free(tileData); //Todo: What does this do?

//    return 0;
}

void RenderView::writeTile(IMG_TileDevice *dev, void *tdata, int tx0, int tx1, int ty0, int ty1) {
    dev->writeTile(tdata,tx0,tx1,ty0,ty1);
    dev->flush();
}

void RenderView::PushTile(const ImageMatrix &tile, int tx0, int tx1, int ty0, int ty1) {
    writeTile(Device,makeTile(tile),tx0,tx1,ty0,ty1);
}

void *RenderView::makeTile(const ImageMatrix &img) {
    int pixels = TileResX * TileResY;
    int words = pixels * IMGvectorSize(imagePlane.ColorModel);
    int bytes = words * IMGbyteSize(imagePlane.Format);

    void *tileData = malloc(bytes);

//    std::cout << img[0][0].x() << std::endl;


    float*ptr = (float *)tileData;
    for(int y = 0; y < TileResY; ++y){
        for(int x = 0; x < TileResX; ++x){
            *ptr++ = img[y][x].x();
            *ptr++ = img[y][x].y();
            *ptr++ = img[y][x].z();
            *ptr++ = img[y][x].w();
//            *ptr++ = 0;
//            *ptr++ = 0;
//            *ptr++ = 0;
//            *ptr++ = 0;
        }
    }
//
    *((char *)ptr) += words * IMGbyteSize(imagePlane.Format);
    return tileData;
}