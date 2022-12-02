//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#include <iostream>
#include "../include/PhysicallyBasedRenderer.hpp"
//#include "../../Mathematics/include/Vectors.hpp"
#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Optics.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"

constexpr int eliminationDepth = 20;

PhysicallyBasedRenderer::PhysicallyBasedRenderer(Scene myScene) : Renderer(myScene){
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
    textures.push_back(new ConstantTexture({{1,1,1},1.5,0.0,0.0}));
    DefaultTexture = std::make_unique<ConstantTexture>(ConstantTexture({{0.9,0.9,0.9},1.5,0.5,0}));
}

float PhysicallyBasedRenderer::EliminationProbability(int depth){
    return depth < eliminationDepth ? 1-1/(depth+1) : 1;
}

void PhysicallyBasedRenderer::ImproveTile(ImageTile &tile, int sampleCount) {
    float previousWeight = tile.sampleCount == 0 ? 0.0 : ((float)tile.sampleCount) / (sampleCount + tile.sampleCount);
    float currentWeight = 1 - previousWeight;
    float sampleMultiplier = 1.0/sampleCount;
    float currentMultiplier = currentWeight*sampleMultiplier;

    tile.sampleCount += sampleCount;

    int tileSizeX = tile.viewCoords.tx1 - tile.viewCoords.tx0;
    int tileSizeY = tile.viewCoords.ty1 - tile.viewCoords.ty0;

    Color tileColor = {Generator::GenerateF01(),Generator::GenerateF01(),Generator::GenerateF01()};

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
    auto energy = ComputeIllumination(ray,0,1);
    return {energy[0].amount,energy[1].amount,energy[2].amount,0};
}

RGBRadiance PhysicallyBasedRenderer::ComputeIllumination(GU_Ray observer, int depth, float IOR) {
    GU_RayInfo info{};
    int count = intersect->sendRay(observer.org,observer.dir,info);
    if(count == 0) return {0,0,0};
    auto direct = ComputeDirectIllumination(info,observer,IOR);
    auto indirect = ComputeIndirectIllumination(info,observer,depth,IOR);

    auto color = scene.geometry.IntersectionPointColor(info);

    float multiplierDirectDiffuse = get<1>(direct)/(1+get<1>(direct));
    float multiplierDirectPerfect = 1- multiplierDirectDiffuse;

    auto perfectDirect = get<0>(direct);
    perfectDirect[0].amount *= multiplierDirectPerfect;
    perfectDirect[1].amount *= multiplierDirectPerfect;
    perfectDirect[2].amount *= multiplierDirectPerfect;

    auto diffuseDirect = get<0>(direct);
    diffuseDirect[0].amount *= multiplierDirectDiffuse * color[0];
    diffuseDirect[1].amount *= multiplierDirectDiffuse * color[1];
    diffuseDirect[2].amount *= multiplierDirectDiffuse * color[2];


    float multiplierIndirectPerfect = get<1>(indirect)/(1+get<1>(indirect));
    float multiplierIndirectDiffuse = 1- multiplierIndirectPerfect;

    auto perfectIndirect = get<0>(indirect);
    perfectIndirect[0].amount *= multiplierIndirectPerfect;
    perfectIndirect[1].amount *= multiplierIndirectPerfect;
    perfectIndirect[2].amount *= multiplierIndirectPerfect;

    auto diffuseIndirect = get<0>(indirect);
    diffuseIndirect[0].amount *= multiplierIndirectDiffuse * color[0];
    diffuseIndirect[1].amount *= multiplierIndirectDiffuse * color[1];
    diffuseIndirect[2].amount *= multiplierIndirectDiffuse * color[2];

    return perfectDirect + diffuseDirect + perfectIndirect + diffuseIndirect;
}


std::tuple<RGBRadiance,float> PhysicallyBasedRenderer::ComputeIndirectIllumination(GU_RayInfo info, GU_Ray observer, int depth, float IOR) {
//    return {{0,0,0},0};
    if(Generator::GenerateF01() < EliminationProbability(depth)) return {{0,0,0},0};

    auto normal = scene.geometry.IntersectionVertexNormal(info);
    auto shader = scene.geometry.IntersectionPointShader(info);


    if(shader < 0 || shader >= textures.size()){
        bsdf.Load(DefaultTexture.get(),observer.org);
    }
    else{
        bsdf.Load(textures[shader],observer.org);
    }


    auto rnd = gen.GenerateF01();

//    if(rnd > bsdf.)

    auto nextPathCartesian = bsdf.brdf->GenerateSample(observer.dir, normal);

    auto next = GU_Ray(observer.org+observer.dir*info.myT+nextPathCartesian*0.01,nextPathCartesian);

    auto mult = bsdf.brdf->Evaluate(observer.dir,next.dir,normal);
    auto temp = ComputeIllumination(next,++depth,IOR);

    auto fresnell = ReflectionCoefficient(nextPathCartesian,-observer.dir,1.5,1);

    auto rtrval = std::tuple<RGBRadiance,float>({temp[0].amount*mult[0],temp[1].amount*mult[1],temp[2].amount*mult[2]},fresnell);
    return rtrval;

}

std::tuple<RGBRadiance,float> PhysicallyBasedRenderer::ComputeDirectIllumination(GU_RayInfo info, GU_Ray observer, float IOR) {
    auto chosenLight = Generator::GenerateIRange(0,scene.lights.size()-1);
    auto intersectionPos = info.myT*observer.dir+observer.org;
    auto lightSample = scene.lights[chosenLight]->GenerateSample(intersectionPos);

    auto normal = scene.geometry.IntersectionVertexNormal(info);
    auto lightDirNormalized = Normalize(lightSample.directionTargetToLight);

    GU_RayInfo shadowInfo{};
    int count = intersect->sendRay(intersectionPos+lightDirNormalized*0.001,lightSample.directionTargetToLight,shadowInfo);
    if(count != 0){
        if(shadowInfo.myT < 1){
            return {{0,0,0},0};
        }
    }

    auto distance = Norm(lightSample.directionTargetToLight);
    auto radiance = lightSample.amount*dot(normal,lightDirNormalized)/(distance*distance);

    auto fresnell = ReflectionCoefficient(lightDirNormalized,observer.dir,1.5,1);

    auto mult = bsdf.brdf->Evaluate(observer.dir,lightDirNormalized,normal);

    auto temp = std::tuple<RGBRadiance,float>({radiance*mult[0], radiance*mult[1], radiance*mult[2]},fresnell);
    return temp;
}




