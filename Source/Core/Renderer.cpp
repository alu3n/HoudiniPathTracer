//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#include "Renderer.hpp"

Renderer::Renderer(RenderSettings settings, SOP_Node * geo) : Settings(settings) {
    Geo = geo;
}

ImageMatrix Renderer::RenderImage(int frame) {
    ImageMatrix image;
    int pixelCount = Settings.Cam.ImageResolution.x()*Settings.Cam.ImageResolution.y();
    int pixelNow = 0;

    //Todo: Create better implementation that would support parallelism
    for(int px = 0; px < Settings.Cam.ImageResolution.x(); ++px){
        image.push_back({});
        for(int py = 0; py < Settings.Cam.ImageResolution.y(); ++py){
            std::cout << "Rendering pixel: " << pixelNow << " of " << pixelCount << std::endl;
            image[px].push_back(RenderPixel({px,py},frame));
            pixelNow++;
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

RenderSettings::RenderSettings(Camera cam, int fps) : Cam(cam) {
    FPS = fps;
}