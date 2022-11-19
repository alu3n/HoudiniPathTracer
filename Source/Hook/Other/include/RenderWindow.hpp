//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_RENDERWINDOW_HPP
#define NPRG045_RENDERWINDOW_HPP

#include "../../../Core/Renderers/include/ImageRepresentation.hpp"

#include <UT/UT_Vector2.h>
#include <IMG/IMG_TileDevice.h>
#include <IMG/IMG_TileOptions.h>
#include <TIL/TIL_TileMPlay.h>

//This class is utility class to communicate with render window

constexpr std::string_view DeviceName = "ip";
constexpr std::string_view HostName = "host";
constexpr std::string_view Port = "port";
constexpr std::string_view Filename = "Other Output";

struct ImagePlaneDefinition {
    const char *Name;
    IMG_DataType Format;
    IMG_ColorModel ColorModel;
};

class RenderWindow{
public:
    RenderWindow() = default;
    void DisplayTile(const ImageTile & tile);
    void Open(UT_Vector2i imageResolution, UT_Vector2i tileResolution);
    IMG_TileDevice *Device;
private:
//    void WriteTile(const ImageTile & tile);
//    void SendDeviceDefinitions(IMG_TileDevice *device, const UT_String & host, const UT_String & port);
    void * ConvertTile(const ImageTile & tile);
    ImagePlaneDefinition imagePlaneDefinition = {"Color RGBA",IMG_FLOAT,IMG_RGBA};
};

#endif //NPRG045_RENDERWINDOW_HPP