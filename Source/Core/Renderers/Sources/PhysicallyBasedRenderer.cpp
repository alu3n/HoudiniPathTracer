//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#include <iostream>
#include "../Headers/PhysicallyBasedRenderer.hpp"
#include "../../Mathematics/Headers/Vectors.hpp"
#include "../../Mathematics/Headers/Sampling.hpp"

constexpr int eliminationDepth = 20;

PhysicallyBasedRenderer::PhysicallyBasedRenderer(Scene myScene) : Renderer(myScene){
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
//    textures.push_back(new ConstantTexture({{1,1,1},0,0,0}));
//    textures.push_back(new ConstantTexture({{1,1,1},0.2,0,0}));
//    textures.push_back(new ConstantTexture({{1,1,1},0.4,0,0}));
//    textures.push_back(new ConstantTexture({{1,1,1},0.6,0,0}));
//    textures.push_back(new ConstantTexture({{1,1,1},0.8,0,0}));
//    textures.push_back(new ConstantTexture({{1,1,1},1,0,0}));
    std::cout << "1/3" << std::endl;
}

float PhysicallyBasedRenderer::EliminationProbability(int depth){
    return depth < eliminationDepth ? 1-1/(depth+1) : 1;
}

void PhysicallyBasedRenderer::ImproveTile(ImageTile &tile, int sampleCount) {
    std::cout << "Improving tile" << std::endl;

    float previousWeight = tile.sampleCount == 0 ? 0.0 : ((float)tile.sampleCount) / (sampleCount + tile.sampleCount);
    float currentWeight = 1 - previousWeight;
    float sampleMultiplier = 1.0/sampleCount;
    float currentMultiplier = currentWeight*sampleMultiplier;

    tile.sampleCount += sampleCount;

    int tileSizeX = tile.viewCoords.tx1 - tile.viewCoords.tx0;
    int tileSizeY = tile.viewCoords.ty1 - tile.viewCoords.ty0;

    Color tileColor = {gen.Generate01F1(),gen.Generate01F1(),gen.Generate01F1()};

    for(int x = 0; x <= tileSizeX; ++x){
        for(int y = 0; y <= tileSizeY; ++y){
            Color buffer{0,0,0,0};
            for(int i = 0; i < sampleCount; ++i){
                buffer = buffer + ComputePixel({tile.viewCoords.tx0 + x,tile.viewCoords.ty0 + y});
            }
            tile.data[x][y] = previousWeight * tile.data[x][y] + currentMultiplier * buffer;
        }
    }


}

Color PhysicallyBasedRenderer::ComputePixel(UT_Vector2i coordinates) {
    auto ray = scene.camera.GenerateRay(coordinates);
    auto energy = ComputeIllumination(ray,0);
    return {energy[0].amount,energy[1].amount,energy[2].amount,0};
}

RGBRadiance PhysicallyBasedRenderer::ComputeIllumination(GU_Ray observer, int depth) {
    GU_RayInfo info{};
    int count = intersect->sendRay(observer.org,observer.dir,info);
    if(count == 0) return {0,0,0};
    auto direct = ComputeDirectIllumination(info,observer);
    auto indirect = ComputeIndirectIllumination(info,observer,depth);

    auto total = direct;
    total[0].amount += indirect[0].amount;
    total[1].amount += indirect[1].amount;
    total[2].amount += indirect[2].amount;

    auto color = scene.geometry.IntersectionPointColor(info);
    total[0].amount *= color.x();
    total[1].amount *= color.y();
    total[2].amount *= color.z();
    return total;
}

constexpr float idealReflectionProb = 0.6;
constexpr float interpolationCoeff = 0.05;

RGBRadiance PhysicallyBasedRenderer::ComputeIndirectIllumination(GU_RayInfo info, GU_Ray observer, int depth) {
    if(gen.Generate01F1() < EliminationProbability(depth)) return {0,0,0};

    auto normal = scene.geometry.IntersectionVertexNormal(info);
//    auto normalInSpherical = CartesianToSpherical(normal);
//    auto azimuth = gen.Generate01F1()*2*M_PI;
//    auto zenith = gen.Generate01F1()*M_PI-0.5*M_PI;
//    auto nextPath = SphericalCoords(azimuth,zenith);
//    nextPath.zenith += normalInSpherical.zenith;
//    nextPath.azimuth += normalInSpherical.azimuth;
//    auto randomPath = SphericalToCartesian(nextPath);
//
//    auto perfectPath = observer.dir - (dot(normal,observer.dir)*normal)*2;
//    auto nextPathCartesian = Normalize<2>(interpolationCoeff*randomPath + (1-interpolationCoeff)*perfectPath);
//
//    TODO: Use BRDF here to modify amount of light reflected in the viewers direction
//
    std::cout << "1/3" << std::endl;
    brdf.Load(textures[0],observer.org);
    std::cout << "2/3" << std::endl;
    auto nextPathCartesian = brdf.GenerateSample(observer.dir, normal);
    std::cout << "3/3" << std::endl;
    auto next = GU_Ray(observer.org+observer.dir*info.myT+nextPathCartesian*0.01,nextPathCartesian);


    return ComputeIllumination(next,depth++);
}

RGBRadiance PhysicallyBasedRenderer::ComputeDirectIllumination(GU_RayInfo info, GU_Ray observer) {
    auto chosenLight = gen.GenerateInRange(0,scene.lights.size()-1);
    auto intersectionPos = info.myT*observer.dir+observer.org;
    auto lightSample = scene.lights[chosenLight]->GenerateSample(intersectionPos);

    auto normal = scene.geometry.IntersectionVertexNormal(info);
    auto lightDirNormalized = Normalize<2>(lightSample.directionTargetToLight);

    GU_RayInfo shadowInfo{};
    int count = intersect->sendRay(intersectionPos+lightDirNormalized*0.001,lightSample.directionTargetToLight,shadowInfo);
    if(count != 0){
        if(shadowInfo.myT < 1){
            return {0,0,0};
        }
    }

    auto distance = Norm<2>(lightSample.directionTargetToLight);
    //TODO: Use BRDF here to modify amount of light reflected in the viewers direction
    auto radiance = lightSample.amount*dot(normal,lightDirNormalized)/(distance*distance);
    //Todo: add colored lights in future
    return {radiance, radiance, radiance};
}




