//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "Renderer.hpp"

Renderer::Renderer(RenderSettings settings) : Settings(settings) {}

ImageMatrix Renderer::RenderImage(int frame) {
    ImageMatrix image;
    //Todo: Create better implementation that would support parallelism
    for(int px = 0; px < Settings.Cam.ImageResolution.x(); ++px){
        image.push_back({});
        for(int py = 0; py < Settings.Cam.ImageResolution.y(); ++py){
            image[px].push_back(RenderPixel({px,py}));
        }
    }
    return image;
}

std::vector<ImageMatrix> Renderer::RenderAnimation(UT_Vector2i framerange) {
    std::vector<ImageMatrix> animation;
    for(int i = framerange.x(); i < framerange.y(); ++i){
        animation.push_back(RenderImage(i));
    }
}