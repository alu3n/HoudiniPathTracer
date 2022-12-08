//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#include <iostream>
#include "../include/PhysicallyBasedRenderer.hpp"
#include "../../Physics/include/Optics.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"
#include "../../Materials/include/MaterialLibrary.hpp"

constexpr int eliminationDepth = 20;
constexpr float epsilon = 0.0001;


//If you want to introduce new shader to the scene just push it to the Textures vector. It will be accessible
//via corresponding index. E.g. object will be assigned MaterialRubber when it has integer point attribute
//"shader" set to 1.

PhysicallyBasedRenderer::PhysicallyBasedRenderer(Scene myScene) : Renderer(myScene){
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
    Materials.push_back(new MaterialMarble());
    Materials.push_back(new MaterialRubber());
    Materials.push_back(new MaterialPorcelain());
    Materials.push_back(new MaterialGlass());
    Materials.push_back(new MaterialPianoBlack());
    Materials.push_back(new MaterialRock());
    Materials.push_back(new MaterialPlastic());
    Materials.push_back(new ProceduralTiles());
    DefaultMaterial = std::make_unique<ConstantMaterial>(MaterialDefault());
}


float PhysicallyBasedRenderer::EliminationProbability(int depth){
    return depth < eliminationDepth ? 1-1/(depth+1) : 1;
}

bool PhysicallyBasedRenderer::ShouldEliminate(int depth) {
    return gen.GenerateF01() < EliminationProbability(depth);
}


//Access shader index and assign appropriate material based on that
TextureData PhysicallyBasedRenderer::GetTextureData(GU_RayInfo info, UT_Vector3F position) {
    auto shader = scene.geometry.IntersectionPointShader(info);
    if(shader < 0 || shader >= Materials.size()){
        return DefaultMaterial->Evaluate(position);
    }
    else{
        return Materials[shader]->Evaluate(position);
    }
}

void PhysicallyBasedRenderer::ImproveTile(ImageTile &tile, int sampleCount) {
    float previousWeight = tile.sampleCount == 0 ? 0.0 : ((float)tile.sampleCount) / (sampleCount + tile.sampleCount);
    float currentWeight = 1 - previousWeight;
    float sampleMultiplier = 1.0/sampleCount;
    float currentMultiplier = currentWeight*sampleMultiplier;

    tile.sampleCount += sampleCount;

    int tileSizeX = tile.viewCoords.tx1 - tile.viewCoords.tx0;
    int tileSizeY = tile.viewCoords.ty1 - tile.viewCoords.ty0;

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
    auto energy = ComputeIllumination(ray.dir,ray.org,0);
    return {energy[0].amount,energy[1].amount,energy[2].amount,0};
}

RGBRadiance
PhysicallyBasedRenderer::ComputeIllumination(UT_Vector3F observationDir, UT_Vector3F observationPos, int depth) {
    GU_RayInfo intersectionInfo;

    if(intersect->sendRay(observationPos,observationDir,intersectionInfo) == 0) return {0,0,0};

    auto intersectionPos = observationPos + intersectionInfo.myT*observationDir;
    auto intersectionNormal = scene.geometry.IntersectionVertexNormal(intersectionInfo);

    if(dot(observationDir,intersectionNormal) > 0) intersectionNormal = -intersectionNormal;

    TextureData textureData = GetTextureData(intersectionInfo,intersectionPos);

    if(scene.geometry.UsePointColor(intersectionInfo)){
        auto Cd = scene.geometry.IntersectionPointColor(intersectionInfo);
        textureData.DiffuseColor = {Cd.r(),Cd.g(),Cd.b()};
    }

    return ComputeIntersectionIllumination(textureData,intersectionNormal,observationDir,intersectionPos,depth);
}

RGBRadiance
PhysicallyBasedRenderer::ComputeIntersectionIllumination(const TextureData &textureData, UT_Vector3F normalDir,
                                                         UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                         int depth) {
    if(ShouldEliminate(depth)) return ComputeDirectIllumination(textureData,normalDir,observationDir,intersectionPos);

    if(textureData.Transparency > 0){
        return ComputeReflection(textureData,normalDir,observationDir,intersectionPos,depth) +
               ComputeDirectIllumination(textureData,normalDir,observationDir,intersectionPos) +
               ComputeRefraction(textureData,normalDir,observationDir,intersectionPos,depth);
    }

    return ComputeReflection(textureData,normalDir,observationDir,intersectionPos,depth) +
        ComputeDirectIllumination(textureData,normalDir,observationDir,intersectionPos);
}

RGBRadiance PhysicallyBasedRenderer::ComputeDirectIllumination(const TextureData &textureData, UT_Vector3F normalDir,
                                                               UT_Vector3F observationDir,
                                                               UT_Vector3F intersectionPos) {
    auto chosenLight = Generator::GenerateIRange(0,scene.lights.size()-1);
    auto lightSample = scene.lights[chosenLight]->GenerateSample(intersectionPos);

    if(Shadow(intersectionPos+epsilon*normalDir,lightSample.lightDir,lightSample.lightDistance)) return {0,0,0};

    RGBRadiance radiance = {lightSample.intensity*lightSample.color[0].amount,lightSample.intensity*lightSample.color[1].amount,lightSample.intensity*lightSample.color[2].amount};

    auto brdfMultiplier = bsdf.EvaluateBRDF(textureData,observationDir,lightSample.lightDir,normalDir);
    auto distanceFalloff = 1.0/(pow(lightSample.lightDistance > epsilon ? lightSample.lightDistance : epsilon,2));

    return brdfMultiplier*(distanceFalloff*radiance);
}

RGBRadiance PhysicallyBasedRenderer::ComputeReflection(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {
    auto reflectionDir = bsdf.GenerateReflection(textureData,observationDir, normalDir);
    auto reflectionOrigin = intersectionPos+epsilon*normalDir;

    auto radiance = ComputeIllumination(reflectionDir,reflectionOrigin,++depth);
    auto brdfMultiplier = bsdf.EvaluateBRDF(textureData,observationDir,reflectionDir, normalDir);

    return brdfMultiplier*radiance;
}

//Todo: Fix refractions
RGBRadiance PhysicallyBasedRenderer::ComputeRefraction(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {
    UT_Vector3F refractionDir = Normalize(bsdf.GenerateRefraction(textureData,observationDir, normalDir,1,textureData.IOR));
    UT_Vector3F refractionOrigin = intersectionPos-epsilon*normalDir;


    GU_RayInfo intersectionInfo{};
    if(intersect->sendRay(refractionOrigin,refractionDir,intersectionInfo) == 0) return {0,0,0};

    auto refractionNormal = scene.geometry.IntersectionVertexNormal(intersectionInfo);
    auto refractionIntersectionPos = refractionOrigin + intersectionInfo.myT*refractionDir;

    UT_Vector3F secondRefractionDir = bsdf.GenerateRefraction(GetTextureData(intersectionInfo,refractionIntersectionPos),refractionDir,-refractionNormal,textureData.IOR,1.0);
    auto secondRefractionOrigin = refractionIntersectionPos + epsilon*refractionNormal;
    return textureData.Transparency*ComputeIllumination(secondRefractionDir,secondRefractionOrigin,++depth);
}

bool PhysicallyBasedRenderer::Shadow(UT_Vector3F intersectionPosition, UT_Vector3F lightDir, float lightDistance) {
    GU_RayInfo shadowInfo{};
    if(intersect->sendRay(intersectionPosition,lightDir,shadowInfo) != 0){
        if(shadowInfo.myT < lightDistance) return true;
    }
    return false;
}





