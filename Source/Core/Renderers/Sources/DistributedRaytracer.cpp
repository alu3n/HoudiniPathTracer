//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../../Mathematics/Headers/Sampling.hpp"
#include "../Headers/DistributedRaytracer.hpp"
#include "../../Mathematics/Headers/Vectors.hpp"

DistributedRaytracer::DistributedRaytracer(Scene myScene) : Renderer(myScene) {
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
}

void DistributedRaytracer::ImproveTile(ImageTile &tile, int sampleCount) {
    Generator gen{};

    float previousWeight = tile.sampleCount == 0 ? 0.0 : ((float)tile.sampleCount) / (sampleCount + tile.sampleCount);
    float currentWeight = 1 - previousWeight;
    float sampleMultiplier = 1.0/sampleCount;
    float currentMultiplier = currentWeight*sampleMultiplier;

    tile.sampleCount += sampleCount;

    int tileSizeX = tile.viewCoords.tx1 - tile.viewCoords.tx0;
    int tileSizeY = tile.viewCoords.ty1 - tile.viewCoords.ty0;

    for(int x = 0; x < tileSizeX; ++x){
        for(int y = 0; y <= tileSizeY; ++y){
            Color buffer{};
            for(int i = 0; i < sampleCount; ++i){
                buffer = buffer + RenderPixel({tile.viewCoords.tx0 + x,tile.viewCoords.ty0 + y});
            }
            tile.data[x][y] = previousWeight * tile.data[x][y] + currentMultiplier * buffer;
        }
    }
}

constexpr size_t recursionDepth = 10;

Color DistributedRaytracer::RenderPixel(UT_Vector2i coordinates) {
//    return {{0},{1},{0},0};
    auto ray = scene.camera.GenerateRay(coordinates);

    GU_RayInfo info;
    info.init();

    int count = intersect->sendRay(ray.org,ray.dir,info);
    if(count == 0){
        return {{0},{0},{0},1};
    }
    else{
        return ComputeColor(ray,info,recursionDepth);
    }

}

Color DistributedRaytracer::ComputeColor(const GU_Ray & ray, const GU_RayInfo & info, int depth){
    auto P = ray.org + info.myT * ray.dir;
    auto N = info.myNml;

    //Direct illumination

    float totalLight{0};

    for(auto && light : scene.lights){
        auto sample = light->GenerateSample();
        auto L = Normalize<2>(sample.myPosition - P);

        GU_RayInfo shadowInfo;
        shadowInfo.init();

        if(intersect->sendRay(P+0.001*L,L,shadowInfo) > 0){
            if(shadowInfo.myT < 1) continue;
        }

        auto d = Norm<2>(sample.myPosition - P);
        auto mult = dot(L,N);

        totalLight += (1.0/(d*d)) * sample.myIntensity * (mult > 0 ? mult : 0);
    }

    return {{totalLight},{totalLight},{totalLight},0};
}
