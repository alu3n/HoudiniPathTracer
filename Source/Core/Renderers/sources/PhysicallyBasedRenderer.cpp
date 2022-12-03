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
constexpr float epsilon = 0.00001;

PhysicallyBasedRenderer::PhysicallyBasedRenderer(Scene myScene) : Renderer(myScene){
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
    textures.push_back(new ConstantTexture({{0.7,0.7,0},1.5,0,0.1,true}));
    DefaultTexture = std::make_unique<ConstantTexture>(ConstantTexture({{0.9,0.9,0.9},1.5,0.2,0,false}));
}

float PhysicallyBasedRenderer::EliminationProbability(int depth){
    return depth < eliminationDepth ? 1-1/(depth+1) : 1;
}

TextureData PhysicallyBasedRenderer::GetTextureData(GU_RayInfo info, UT_Vector3F position) {
    auto shader = scene.geometry.IntersectionPointShader(info);
    if(shader < 0 || shader >= textures.size()){
        bsdf.Load(DefaultTexture.get(),position);
    }
    else{
        bsdf.Load(textures[shader],position);
    }
    return bsdf.brdf->data;
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
    auto energy = ComputeIllumination(ray,0);
    return {energy[0].amount,energy[1].amount,energy[2].amount,0};
}

RGBRadiance PhysicallyBasedRenderer::ComputeIllumination(GU_Ray observer, int depth) {
    GU_RayInfo info{};
    int count = intersect->sendRay(observer.org,observer.dir,info);
    if(count == 0) return {0,0,0};//get<0>(ComputeDirectIllumination(info,observer));

//    auto direct = ComputeDirectIllumination(info,observer);
//    auto indirect = ComputeIndirectIllumination(info,observer,depth);
    return dot(observer.dir,scene.geometry.IntersectionVertexNormal(info))*get<0>(ComputeIndirectIllumination(info,observer,depth));
//    return get<0>(direct) + get<0>(indirect);


//    Color surfaceColor{0,0,0};
//    auto texture = GetTextureData(info,observer.org);
//    if(texture.OverrideColor){
//        surfaceColor.r = texture.DiffuseColor[0];
//        surfaceColor.g = texture.DiffuseColor[1];
//        surfaceColor.b = texture.DiffuseColor[2];
//    }
//    else{
//        auto temp = scene.geometry.IntersectionPointColor(info);
//        surfaceColor.r = temp.r();
//        surfaceColor.g = temp.g();
//        surfaceColor.b = temp.b();
//    }
//
//    float multiplierDirectPerfectlyReflected = (get<1>(direct)/(1+get<1>(direct)))/4;
//    float multiplierDirectDiffuse = 1 - multiplierDirectPerfectlyReflected;
//
//    auto rtrval =  get<0>(direct);
//    rtrval[0].amount *= surfaceColor.r * multiplierDirectDiffuse * (1-texture.Transparency);
//    rtrval[1].amount *= surfaceColor.g * multiplierDirectDiffuse * (1-texture.Transparency);
//    rtrval[2].amount *= surfaceColor.b * multiplierDirectDiffuse * (1-texture.Transparency);
//    rtrval[0].amount += multiplierDirectPerfectlyReflected * get<0>(direct)[0].amount;
//    rtrval[1].amount += multiplierDirectPerfectlyReflected * get<0>(direct)[1].amount;
//    rtrval[2].amount += multiplierDirectPerfectlyReflected * get<0>(direct)[2].amount;
//
//    auto indirectRad = get<0>(indirect);
//
//    float multiplierIndirectPerfectlyReflected = (get<1>(indirect)/(1+get<1>(indirect)))/2;
//    float multiplierIndirectDiffuse = 1 - multiplierDirectPerfectlyReflected;
//
//    rtrval[0].amount += get<0>(indirect)[0].amount * multiplierIndirectDiffuse * surfaceColor.r * (1-texture.Transparency);
//    rtrval[1].amount += get<0>(indirect)[1].amount * multiplierIndirectDiffuse * surfaceColor.g * (1-texture.Transparency);
//    rtrval[2].amount += get<0>(indirect)[2].amount * multiplierIndirectDiffuse * surfaceColor.b * (1-texture.Transparency);
//
//    rtrval[0].amount += get<0>(indirect)[0].amount * multiplierIndirectPerfectlyReflected;
//    rtrval[1].amount += get<0>(indirect)[1].amount * multiplierIndirectPerfectlyReflected;
//    rtrval[2].amount += get<0>(indirect)[2].amount * multiplierIndirectPerfectlyReflected;
//
//    return rtrval + texture.Transparency * ComputeRefraction(info,observer,depth);
}

constexpr float airIOR = 1.003;
constexpr float matterIOR = 1.35;
constexpr float ratioIOR = airIOR/matterIOR;

//RGBRadiance  ComputeRefraction()

RGBRadiance PhysicallyBasedRenderer::ComputeRefraction(GU_RayInfo info, GU_Ray observer, int depth) {
    if(Generator::GenerateF01() < EliminationProbability(depth)) return {0,0,0};

    auto normal = scene.geometry.IntersectionVertexNormal(info);
    auto shader = scene.geometry.IntersectionPointShader(info);
    auto intersectionLocation = observer.org+ info.myT*observer.dir;

    auto internalPath = (ratioIOR*dot(normal,-observer.dir)-sqrt(1-pow(ratioIOR,2)*(1-dot(normal,-observer.dir))))*normal - ratioIOR * (-observer.dir);
    auto internalRay = GU_Ray(intersectionLocation+epsilon*internalPath,internalPath);
    if(0 == intersect->sendRay(internalRay.org,internalRay.dir,info)) return {0,0,0};
    GU_Ray nextPath = GU_Ray(internalRay.org + (epsilon+info.myT)*internalRay.dir,scene.geometry.IntersectionVertexNormal(info));
    return ComputeIllumination(nextPath,depth++);

}

std::tuple<RGBRadiance,float> PhysicallyBasedRenderer::ComputeIndirectIllumination(GU_RayInfo info, GU_Ray observer, int depth) {
    if(Generator::GenerateF01() < EliminationProbability(depth)) return ComputeDirectIllumination(info,observer);

    auto normal = scene.geometry.IntersectionVertexNormal(info);
    auto shader = scene.geometry.IntersectionPointShader(info);


    if(shader < 0 || shader >= textures.size()){
        bsdf.Load(DefaultTexture.get(),observer.org);
    }
    else{
        bsdf.Load(textures[shader],observer.org);
    }

    auto nextPathCartesian = bsdf.brdf->GenerateSample(observer.dir, normal);

    auto next = GU_Ray(observer.org+observer.dir*info.myT+nextPathCartesian*epsilon,nextPathCartesian);

    auto mult = bsdf.brdf->Evaluate(observer.dir,next.dir,normal);
    auto temp = ComputeIllumination(next,++depth);

    auto fresnell = ReflectionCoefficient(nextPathCartesian,normal,airIOR,matterIOR);

    auto rtrval = std::tuple<RGBRadiance,float>({temp[0].amount*mult[0],temp[1].amount*mult[1],temp[2].amount*mult[2]},fresnell);
    return rtrval;
}



std::tuple<RGBRadiance,float> PhysicallyBasedRenderer::ComputeDirectIllumination(GU_RayInfo info, GU_Ray observer) {
    auto chosenLight = Generator::GenerateIRange(0,scene.lights.size()-1);
    auto intersectionPos = info.myT*observer.dir+observer.org;
    auto lightSample = scene.lights[chosenLight]->GenerateSample(intersectionPos);

    auto normal = scene.geometry.IntersectionVertexNormal(info);
    auto lightDirNormalized = Normalize(lightSample.directionTargetToLight);

    auto shader = scene.geometry.IntersectionPointShader(info);

    if(shader < 0 || shader >= textures.size()){
        bsdf.Load(DefaultTexture.get(),observer.org);
    }
    else{
        bsdf.Load(textures[shader],observer.org);
    }

    auto mult = bsdf.brdf->Evaluate(observer.dir,lightDirNormalized,normal);

    GU_RayInfo shadowInfo{};
    int count = intersect->sendRay(intersectionPos+lightDirNormalized*epsilon,lightSample.directionTargetToLight,shadowInfo);
    if(count != 0){
        if(shadowInfo.myT < 1){
            return {{0,0,0},0};
        }
    }

    auto distance = Norm(lightSample.directionTargetToLight);
    auto radiance = lightSample.amount*dot(normal,lightDirNormalized)/(distance*distance);
    auto fresnell = ReflectionCoefficient(lightDirNormalized,normal,airIOR,matterIOR);

    //fourth value is the amount of refracted to reflected light - computed by the fresnell
    return {{radiance.amount,radiance.amount,radiance.amount},fresnell};
}




