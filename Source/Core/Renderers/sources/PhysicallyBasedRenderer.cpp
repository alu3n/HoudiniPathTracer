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
constexpr float epsilon = 0.00001;

PhysicallyBasedRenderer::PhysicallyBasedRenderer(Scene myScene) : Renderer(myScene){
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
    Textures.push_back(new ConstantTexture({{0.7,0.7,0},1.5,1,0,true}));
    Textures.push_back(new ConstantTexture({{0.7,0.7,0.7},1.5,1,0.95,true}));
    Textures.push_back(new ConstantTexture({{0.9,0.9,0.9},1.5,1,0,true}));
    DefaultTexture = std::make_unique<ConstantTexture>(ConstantTexture({{0.9,0.9,0.9},1.5,1,0,false}));
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
        BSDF.Load(DefaultTexture.get(),position);
    }
    else{
        BSDF.Load(Textures[shader],position);
    }
    return BSDF.brdf->data;
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

    TextureData textureData{};

    if(shader < 0 || shader >= Textures.size()){
        BSDF.Load(DefaultTexture.get(),intersectionPos);
        textureData = BSDF.brdf->data;
    }
    else{
        BSDF.Load(Textures[shader],intersectionPos);
        textureData = BSDF.brdf->data;
    }

    return ComputeIntersectionIllumination(textureData,normalDir,observationDir,intersectionPos,depth);
}

RGBRadiance
PhysicallyBasedRenderer::ComputeIntersectionIllumination(const TextureData &textureData, UT_Vector3F normalDir,
                                                         UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                         int depth) {
    if(ShouldEliminate(depth)){
        return ComputeDirectIllumination(textureData,normalDir,observationDir,intersectionPos);
    }

    if(gen.GenerateF01() > textureData.Transparency){
        return ComputeReflection(textureData,normalDir,observationDir,intersectionPos,depth) + ComputeDirectIllumination(textureData,normalDir,observationDir,intersectionPos);
    }
    else{
        return ComputeRefraction(textureData,normalDir,observationDir,intersectionPos,depth);
    }
}

RGBRadiance PhysicallyBasedRenderer::ComputeDirectIllumination(const TextureData &textureData, UT_Vector3F normalDir,
                                                               UT_Vector3F observationDir,
                                                               UT_Vector3F intersectionPos) {
    auto chosenLight = Generator::GenerateIRange(0,scene.lights.size()-1);
    auto lightSample = scene.lights[chosenLight]->GenerateSample(intersectionPos);

    auto shadow = Shadow(intersectionPos+epsilon*normalDir,lightSample.lightDir,lightSample.lightDistance);
    if(shadow <= 0) return {0,0,0};

    auto color = textureData.DiffuseColor;


    auto mult = dot(normalDir,lightSample.lightDir); //This should be replaced by BRDF
    auto total = (mult > 0 ? mult : 0)*lightSample.intensity*(1/(lightSample.lightDistance*lightSample.lightDistance))*shadow;

    return {total*color[0],total*color[1],total*color[2]};
}

RGBRadiance PhysicallyBasedRenderer::ComputeReflection(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {
    auto sampleDir = BSDF.brdf->GenerateSample(observationDir,normalDir);

    auto incommingRadiance = ComputeIllumination(sampleDir,intersectionPos+epsilon*normalDir,++depth);
    auto color = textureData.DiffuseColor;

    auto mult = dot(normalDir,sampleDir); //This should be replaced by BRDF
    auto total = (mult > 0 ? mult : 0)*incommingRadiance.data()[0].amount;
    return {total*color[0],total*color[1],total*color[2]};
}

constexpr float airIOR = 1.003;
constexpr float matterIOR = 1.35;
constexpr float ratioIOR = airIOR/matterIOR;


//Todo: Fix refractions
RGBRadiance PhysicallyBasedRenderer::ComputeRefraction(const TextureData &textureData, UT_Vector3F normalDir,
                                                       UT_Vector3F observationDir, UT_Vector3F intersectionPos,
                                                       int depth) {
    GU_RayInfo refractionInfo{};

    auto internalPath = (ratioIOR*dot(normalDir,-observationDir)-sqrt(1-pow(ratioIOR,2)*(1-dot(normalDir,-observationDir))))*normalDir - ratioIOR * (-observationDir);



    auto nextPathOrigin = intersectionPos-epsilon*normalDir;
    if(0 == intersect->sendRay(nextPathOrigin,internalPath,refractionInfo)) return {0,0,0};

    auto internalIntersectionPos = nextPathOrigin + refractionInfo.myT*internalPath;
    return ComputeIllumination(internalPath,internalIntersectionPos,++depth);
}

float PhysicallyBasedRenderer::Shadow(UT_Vector3F intersectionPosition, UT_Vector3F lightDir, float lightDistance) {
    GU_RayInfo shadowInfo{};
    if(intersect->sendRay(intersectionPosition,lightDir,shadowInfo) != 0){
        if(shadowInfo.myT < lightDistance){
            auto txt = GetTextureData(shadowInfo,intersectionPosition+lightDir*shadowInfo.myT);
            return txt.Transparency >= 0 ? (txt.Transparency < 1 ? txt.Transparency : 1) : 0;
        }
    }
    return 1;
}





