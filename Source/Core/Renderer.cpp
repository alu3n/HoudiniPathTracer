//
// Created by Vojtěch Pröschl on 05.09.2022.
//
#include "Renderer.hpp"

#include <SOP/SOP_Node.h>
#include <GU/GU_Detail.h>

Renderer::Renderer(RenderSettings settings, SOP_Node * geo) : Settings(settings) {
    Geo = geo;
}

RenderSettings::RenderSettings(Camera cam, int fps) : Cam(cam) {
    FPS = fps;
}

//ImageMatrix Renderer::RenderTile(fpreal time, int tx0, int tx1, int ty0, int ty1) {
//    ImageMatrix image;
////    LoadFrame(time);
////    std::cout << ty0 << ":" << ty1 << std::endl;
//    for(int y = ty0; y <= ty1; ++y){
//        image.push_back({});
////        std::cout << y << std::endl;
//        for(int x = tx0; x <= tx1; ++x){
//            image.back().push_back(RenderPixel({x,y}));
//        }
//    }
//
////    std::cout << image.size() << std::endl;
//
//    return image;
//}

//void Renderer::LoadFrame(fpreal time) {
//    OP_Context context(time);
//    GU_DetailHandle * temp = static_cast<GU_DetailHandle *>(Geo->getCookedData(context));
//    intersect = new GU_RayIntersect(temp->gdp());
//}