//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_RENDERINTERFACE_HPP
#define NPRG045_RENDERINTERFACE_HPP

//#include <string>
#include <OP/OP_Context.h>
#include "RenderWindow.hpp"
#include "../../Nodes/include/RendererNode.hpp"
#include "../../../Core/Scene/include/Scene.hpp"

//This class is the main communication point between nodes and renderer

class RenderInterface{
public:
    RenderInterface(RendererNode * node);
    void RenderFrame(fpreal time);
//    void RenderFramerange();
private:
    RendererNode * rendererNode;
    RenderWindow renderWindow;
    bool LoadFailed{false}; //Set to true if the parameters are incorrect
    //Render should display error message when started with failed load


    Lights LoadLights(OP_Context context);
    Light* LoadLight(UT_String lightName, OP_Context context);
    Camera LoadCamera(UT_String cameraName, OP_Context context);
    Geometry LoadGeometry(UT_String geometryName, OP_Context context);

    void LoadData(OP_Context context);
    void Render();

    std::unique_ptr<Scene> scene;

    SOP_Node * geoNode;
    bool geoExist{false};

    int ImageResX;
    int ImageResY;
    int TileResX;
    int TileResY;
    int CycleCount;
    int SamplesPerCycle;
};

#endif //NPRG045_RENDERINTERFACE_HPP
