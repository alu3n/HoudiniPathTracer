//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_RENDERINTERFACE_HPP
#define NPRG045_RENDERINTERFACE_HPP

#include "../../HoudiniHook/RendererNode.hpp"
#include "RenderWindow.hpp"

//This class is the main communication point between nodes and renderer

class RenderInterface{
public:
    RenderInterface(RendererNode * node);
    void RenderFrame();
    void RenderFramerange();
private:
    RendererNode * rendererNode;
    RenderWindow renderWindow;
};

#endif //NPRG045_RENDERINTERFACE_HPP
