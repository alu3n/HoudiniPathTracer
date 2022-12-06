//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#include <iostream>
#include "../include/PhysicallyBasedRenderer.hpp"
//#include "../../Mathematics/include/Vectors.hpp"
#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Optics.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"

constexpr int eliminationDepth = 11;
constexpr float epsilon = 0.0001;

constexpr std::array<float,3> T0_DiffuseColor = {0,0,0.9};
constexpr float T0_ReflectionRoughness = 0.1;
constexpr float T0_RefractionRoughness = 0.5;
constexpr float T0_Transparency = 0;
constexpr float T0_IOR = 1.5;

constexpr std::array<float,3> T1_DiffuseColor = {1,1,1};
constexpr float T1_ReflectionRoughness = 0;
constexpr float T1_RefractionRoughness = 0.5;
constexpr float T1_Transparency = 0.85;
constexpr float T1_IOR = 1.5;

constexpr std::array<float,3> T2_DiffuseColor = {0.3,0.9,0.9};
constexpr float T2_ReflectionRoughness = 0.45;
constexpr float T2_RefractionRoughness = 0.5;
constexpr float T2_Transparency = 0;
constexpr float T2_IOR = 1.5;

constexpr std::array<float,3> T3_DiffuseColor = {0.9,0.9,0.3};
constexpr float T3_ReflectionRoughness = 0.9;
constexpr float T3_RefractionRoughness = 0.5;
constexpr float T3_Transparency = 0;
constexpr float T3_IOR = 1.5;

constexpr std::array<float,3> T4_DiffuseColor = {0.9,0,0};
constexpr float T4_ReflectionRoughness = 0.15;
constexpr float T4_RefractionRoughness = 0.5;
constexpr float T4_Transparency = 0;
constexpr float T4_IOR = 1.5;

constexpr std::array<float,3> T5_DiffuseColor = {0,0.9,0};
constexpr float T5_ReflectionRoughness = 1;
constexpr float T5_RefractionRoughness = 0.5;
constexpr float T5_Transparency = 0;
constexpr float T5_IOR = 1.5;

constexpr std::array<float,3> D_DiffuseColor = {0.9,0.9,0.9};
constexpr float D_ReflectionRoughness = 0.5;
constexpr float D_RefractionRoughness = 0.5;
constexpr float D_Transparency = 0;
constexpr float D_IOR = 1.5;



PhysicallyBasedRenderer::PhysicallyBasedRenderer(Scene myScene) : Renderer(myScene){
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
    Textures.push_back(new ConstantTexture({T0_DiffuseColor,T0_ReflectionRoughness,T0_RefractionRoughness,T0_Transparency,T0_IOR}));
    Textures.push_back(new ConstantTexture({T1_DiffuseColor,T1_ReflectionRoughness,T1_RefractionRoughness,T1_Transparency,T1_IOR}));
    Textures.push_back(new ConstantTexture({T2_DiffuseColor,T2_ReflectionRoughness,T2_RefractionRoughness,T2_Transparency,T2_IOR}));
    Textures.push_back(new ConstantTexture({T3_DiffuseColor,T3_ReflectionRoughness,T3_RefractionRoughness,T3_Transparency,T3_IOR}));
    Textures.push_back(new ConstantTexture({T4_DiffuseColor,T4_ReflectionRoughness,T4_RefractionRoughness,T4_Transparency,T4_IOR}));
    Textures.push_back(new ConstantTexture({T5_DiffuseColor,T5_ReflectionRoughness,T5_RefractionRoughness,T5_Transparency,T5_IOR}));
    DefaultTexture = std::make_unique<ConstantTexture>(ConstantTexture({D_DiffuseColor,D_ReflectionRoughness,D_RefractionRoughness,D_Transparency,D_IOR}));
}

float minimum(float a, float b){
    return a < b ? a : b;
}

float PhysicallyBasedRenderer::EliminationProbability(int depth){
    return depth < eliminationDepth ? 1-1/(depth+1) : 1;
}

bool PhysicallyBasedRenderer::ShouldEliminate(int depth) {
    return gen.GenerateF01() < EliminationProbability(depth);
}


TextureData PhysicallyBasedRenderer::GetTextureData(GU_RayInfo info, UT_Vector3F position) {
    auto shader = scene.geometry.IntersectionPointShader(info);
    if(shader < 0 || shader >= Textures.size()){
        return DefaultTexture->Evaluate(position);
    }
    else{
        return Textures[shader]->Evaluate(position);
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
    //Maybe add direct illumination if intersection fails?
    //Todo: Load propper texture from the texture vector
    GU_RayInfo intersectionInfo;

    if(intersect->sendRay(observationPos,observationDir,intersectionInfo) == 0) return {0,0,0};

    auto intersectionPos = observationPos + intersectionInfo.myT*observationDir;
    auto normalDir = scene.geometry.IntersectionVertexNormal(intersectionInfo);
    auto shader = scene.geometry.IntersectionPointShader(intersectionInfo);

    TextureData textureData = GetTextureData(intersectionInfo,intersectionPos);

    return ComputeIntersectionIllumination(textureData,normalDir,observationDir,intersectionPos,depth);
}

RGBRadiance
PhysicallyBasedRenderer::ComputeIntersectionIllumination(const TextureData &textureData, UT_Vector3F normalDir,
                                                         UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                         int depth) {
    if(ShouldEliminate(depth)) return ComputeDirectIllumination(textureData,normalDir,observationDir,intersectionPos);

    return ComputeReflection(textureData,normalDir,observationDir,intersectionPos,depth) +
        ComputeDirectIllumination(textureData,normalDir,observationDir,intersectionPos) +
        ComputeRefraction(textureData,normalDir,observationDir,intersectionPos,depth);
}

RGBRadiance PhysicallyBasedRenderer::ComputeDirectIllumination(const TextureData &textureData, UT_Vector3F normalDir,
                                                               UT_Vector3F observationDir,
                                                               UT_Vector3F intersectionPos) {

    auto chosenLight = Generator::GenerateIRange(0,scene.lights.size()-1);

    auto lightSample = scene.lights[chosenLight]->GenerateSample(intersectionPos);

    auto shadow = Shadow(intersectionPos+epsilon*normalDir,lightSample.lightDir,lightSample.lightDistance);
    if(shadow <= 0) return {0,0,0};


    auto brdfMult = bsdf.EvaluateBRDF(textureData,observationDir,lightSample.lightDir,normalDir);
    RGBRadiance radiance = {lightSample.intensity*lightSample.color[0].amount,lightSample.intensity*lightSample.color[1].amount,lightSample.intensity*lightSample.color[2].amount};

    auto distanceFalloff = 1.0/(pow(lightSample.lightDistance > epsilon ? lightSample.lightDistance : epsilon,2));

    radiance = distanceFalloff * radiance;
//    radiance = shadow * radiance;

    return brdfMult*radiance;
}

RGBRadiance PhysicallyBasedRenderer::ComputeReflection(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {
    auto reflectionDir = bsdf.GenerateReflection(textureData,observationDir, normalDir);
    auto multiplier = bsdf.EvaluateBRDF(textureData,observationDir,reflectionDir, normalDir);
    auto newPathPos = intersectionPos+epsilon*normalDir;

    auto incommingRadiance = ComputeIllumination(reflectionDir,newPathPos,++depth);
    return multiplier*incommingRadiance;
}

//Todo: Fix refractions
RGBRadiance PhysicallyBasedRenderer::ComputeRefraction(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {

    UT_Vector3F refractionDir = bsdf.GenerateRefraction(textureData,observationDir, normalDir,1,1.5);

    UT_Vector3F newOrigin = intersectionPos-epsilon*normalDir;


    GU_RayInfo intersectionInfo{};

    if(intersect->sendRay(newOrigin,refractionDir,intersectionInfo) == 0) {
        return {0,0,0};
    }

    auto refractionNormal = scene.geometry.IntersectionVertexNormal(intersectionInfo);
    auto newPos = newOrigin + intersectionInfo.myT*refractionDir + 0.1*refractionNormal;

//    UT_Vector3F newDir = refractionNormal;
    UT_Vector3F newDir = bsdf.GenerateRefraction(GetTextureData(intersectionInfo,newPos),refractionDir,-refractionNormal,1.5,1.0);


    return textureData.Transparency*ComputeIllumination(newDir,newPos,++depth);


//    if(textureData.Transparency != 0)
//    std::cout << radiance[0].amount << std::endl;
//
//    return btdfMult * radiance;


//    return {0,0,0};
//    GU_RayInfo refractionInfo{};
//    auto refractionDir = bsdf.GenerateRefraction(textureData);
//    auto refractionOrigin = intersectionPos-epsilon*normalDir;
//
//    //maybe flip normal?
//    if(0 == intersect->sendRay(refractionOrigin,refractionDir,refractionInfo)) return {0,0,0};
//    auto internalIntersectionPos = refractionOrigin + refractionInfo.myT*refractionDir;
//    auto multiplier = bsdf.EvaluateBSDF(textureData);
//    auto incommingRadiance = ComputeIllumination(refractionDir,internalIntersectionPos,++depth);
//
//    return multiplier*incommingRadiance;
}

float PhysicallyBasedRenderer::Shadow(UT_Vector3F intersectionPosition, UT_Vector3F lightDir, float lightDistance) {
    GU_RayInfo shadowInfo{};
    if(intersect->sendRay(intersectionPosition,lightDir,shadowInfo) != 0){
        if(shadowInfo.myT < lightDistance){
            auto txt = GetTextureData(shadowInfo,intersectionPosition+lightDir*shadowInfo.myT);
            return 0;
//            return txt.Transparency >= 0 ? (txt.Transparency < 1 ? txt.Transparency : 1) : 0;
        }
    }
    return 1;
}





