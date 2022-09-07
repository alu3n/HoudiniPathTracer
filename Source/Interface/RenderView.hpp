//
// Created by Vojtěch Pröschl on 06.09.2022.
//

#ifndef NPRG045_RENDERVIEW_HPP
#define NPRG045_RENDERVIEW_HPP

// This class is a wrapper around Houdini's tiledevice

#include <UT/UT_Vector2.h>
#include <IMG/IMG_TileDevice.h>
#include <IMG/IMG_TileOptions.h>
#include <TIL/TIL_TileMPlay.h>
#include <vector>
//UT_String PORT_ = "1337";
//UT_String HOST_ = "DEUTSCHLAND";

struct ImagePlaneDef {
    const char *Name;
    IMG_DataType Format;
    IMG_ColorModel ColorModel;
};


class RenderView{
    using ImageMatrix = std::vector<std::vector<UT_Vector4F>>;
public:
    RenderView() = default;
    RenderView(UT_Vector2i ImageRes, UT_Vector2i TileRes);
    //Todo: Directly use SideFX format for increased efficiency
    void PushTile(const ImageMatrix & tile, int tx0, int tx1, int ty0, int ty1);
    void Open();
    int TileResX;
    int TileResY;
    int ImageResX;
    int ImageResY;
private:
    IMG_TileDevice *Device;
    void sendPlaneDefinitions(IMG_TileDevice * dev, const UT_String & host, const UT_String & port);
    void writeTile(IMG_TileDevice * dev, void * tdata, int tx0, int tx1, int ty0, int ty1);
    void * makeTile();
    void * makeTile(const ImageMatrix &img);

    ImagePlaneDef imagePlane = {"Color RGBA", IMG_FLOAT, IMG_RGBA};
};

#endif //NPRG045_RENDERVIEW_HPP
