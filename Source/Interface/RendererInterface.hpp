//
// Created by Vojtěch Pröschl on 07.09.2022.
//

#ifndef NPRG045_RENDERERINTERFACE_HPP
#define NPRG045_RENDERERINTERFACE_HPP

//should be initialized when the node is created

//Comunication between render node and renderers

#include "../HoudiniHook/RendererNode.hpp"
#include "RenderView.hpp"
//#include "../Core/oldRenderer.hpp"
#include "../Core/RenderEngine.hpp"
#include "../Core/SceneComponents/Camera.hpp"
#include <SOP/SOP_Node.h>

class RendererInterface{
public:
    RendererInterface(RendererNode * rendererNode);
    void LoadData();
    void RenderFrame();
    void RenderFramerange();
private:
    RenderView renderView;
    RendererNode * rendererNode;
    RenderEngine * renderEngine;
    Camera * camera;
//    oldRenderSettings * settings;
    SOP_Node * geometry;

    //render properties
    int sampleCount;
    UT_Vector2i tileSize;
    UT_Vector2i frameRange;
    int fps;
    int renderEngineSelection;
};


#endif //NPRG045_RENDERERINTERFACE_HPP
