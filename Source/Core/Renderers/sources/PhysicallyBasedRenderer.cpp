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

    Materials.emplace("Marble",std::make_unique<MaterialMarble>());
    Materials.emplace("Porcelain",std::make_unique<MaterialPorcelain>());
    Materials.emplace("Rubber",std::make_unique<MaterialRubber>());
    Materials.emplace("Glass",std::make_unique<MaterialGlass>());
    Materials.emplace("Piano Black",std::make_unique<MaterialPianoBlack>());
    Materials.emplace("Rock",std::make_unique<MaterialRock>());
    Materials.emplace("Plastic",std::make_unique<MaterialPlastic>());
    Materials.emplace("Checker Board",std::make_unique<ProceduralTiles>());
    Materials.emplace("Rough Glass",std::make_unique<MaterialRoughGlass>());
    DefaultMaterial = std::make_unique<MaterialDefault>();
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

    if(Materials.count(shader) != 0){
        return Materials[shader]->Evaluate(position);
    }
    return DefaultMaterial->Evaluate(position);
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
    auto E = ComputeIllumination(ray.dir,ray.org,0);
    return {E.R,E.G,E.B};
}

RGBEnergy
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

RGBEnergy
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

RGBEnergy PhysicallyBasedRenderer::ComputeDirectIllumination(const TextureData &textureData, UT_Vector3F normalDir,
                                                               UT_Vector3F observationDir,
                                                               UT_Vector3F intersectionPos) {
    auto chosenLight = Generator::GenerateIRange(0,scene.lights.size()-1);
    auto lightSample = scene.lights[chosenLight]->GenerateSample(intersectionPos);

    if(Shadow(intersectionPos+epsilon*normalDir,lightSample.LightDir,lightSample.LightDistance)) return {0,0,0};

    auto energy = lightSample.Energy;

    auto brdfMultiplier = BSDF::EvaluateBRDF(textureData,observationDir,lightSample.LightDir,normalDir);
    auto distanceFalloff = 1.0/(pow(lightSample.LightDistance > epsilon ? lightSample.LightDistance : epsilon,2));

    return distanceFalloff*brdfMultiplier*energy;
}

RGBEnergy PhysicallyBasedRenderer::ComputeReflection(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {
    auto reflectionDir = BSDF::GenerateReflection(textureData,observationDir, normalDir);
    auto reflectionOrigin = intersectionPos+epsilon*normalDir;

    auto radiance = ComputeIllumination(reflectionDir,reflectionOrigin,++depth);
    auto brdfMultiplier = BSDF::EvaluateBRDF(textureData,observationDir,reflectionDir, normalDir);

    return brdfMultiplier*radiance;
}

RGBEnergy PhysicallyBasedRenderer::ComputeRefraction(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {
    UT_Vector3F refractionDir = Normalize(BSDF::GenerateRefraction(textureData,observationDir, normalDir,1,textureData.IOR));
    UT_Vector3F refractionOrigin = intersectionPos-epsilon*normalDir;


    GU_RayInfo intersectionInfo{};
    if(intersect->sendRay(refractionOrigin,refractionDir,intersectionInfo) == 0) return {0,0,0};

    auto refractionNormal = scene.geometry.IntersectionVertexNormal(intersectionInfo);
    auto refractionIntersectionPos = refractionOrigin + intersectionInfo.myT*refractionDir;

    UT_Vector3F secondRefractionDir = BSDF::GenerateRefraction(GetTextureData(intersectionInfo,refractionIntersectionPos),refractionDir,-refractionNormal,textureData.IOR,1.0);
    auto secondRefractionOrigin = refractionIntersectionPos + epsilon*refractionNormal;
    auto radiance = textureData.Transparency*ComputeIllumination(secondRefractionDir,secondRefractionOrigin,++depth);
    return BSDF::EvaluateBTDF(textureData)*radiance;
}

bool PhysicallyBasedRenderer::Shadow(UT_Vector3F intersectionPosition, UT_Vector3F lightDir, float lightDistance) {
    GU_RayInfo shadowInfo{};
    if(intersect->sendRay(intersectionPosition,lightDir,shadowInfo) != 0){
        if(shadowInfo.myT < lightDistance) return true;
    }
    return false;
}