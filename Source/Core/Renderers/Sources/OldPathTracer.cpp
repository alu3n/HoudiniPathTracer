//
// Created by Vojtěch Pröschl on 07.11.2022.
//

#include "../Headers/OldPathTracer.hpp"
#include "../../Mathematics/Headers/Sampling.hpp"
#include "../../Mathematics/Headers/Vectors.hpp"
#include "../../Materials/Headers/LambertBRDF.hpp"

OldPathTracer::OldPathTracer(Scene myScene) : OldRenderer(myScene){
    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
}

void OldPathTracer::ImproveTile(ImageTile &tile, int sampleCount) {
    float previousWeight = tile.sampleCount == 0 ? 0.0 : ((float)tile.sampleCount) / (sampleCount + tile.sampleCount);
    float currentWeight = 1 - previousWeight;
    float sampleMultiplier = 1.0/sampleCount;
    float currentMultiplier = currentWeight*sampleMultiplier;

    tile.sampleCount += sampleCount;

    int tileSizeX = tile.viewCoords.tx1 - tile.viewCoords.tx0;
    int tileSizeY = tile.viewCoords.ty1 - tile.viewCoords.ty0;

    for(int x = 0; x <= tileSizeX; ++x){
        for(int y = 0; y <= tileSizeY; ++y){
            Color buffer{};
            for(int i = 0; i < sampleCount; ++i){
                buffer = buffer + RenderPixel({tile.viewCoords.tx0 + x,tile.viewCoords.ty0 + y});
            }
            tile.data[x][y] = previousWeight * tile.data[x][y] + currentMultiplier * buffer;
        }
    }
}

float OldPathTracer::EliminationProbability(int depth) {
    if(depth >= maxRecursionDepth){
        return 1.0;
    }
    else{
        return 1.0 - 2.0/(1.0+depth);
    }
}

Color OldPathTracer::RenderPixel(UT_Vector2i coordinates) {
    auto ray = scene.camera.GenerateRay(coordinates);

    GU_RayInfo info;
    info.init();

    int count = intersect->sendRay(ray.org,ray.dir,info);
    if(count == 0){
        return {{0},{0},{0},1};
    }
    else{
        return ComputeIllumination(ray,info,0);
    }
}

Color OldPathTracer::ComputeIllumination(const GU_Ray & ray, const GU_RayInfo & info, int depth) {
    Color colorBuffer{{0},{0},{0},0};

    auto P = ray.org + info.myT * ray.dir;
    auto N = scene.geometry.IntersectionVertexNormal(info);
    auto Cd = scene.geometry.IntersectionPointColor(info);

    Color color{{Cd.x()},{Cd.y()},{Cd.z()},0};
    LambertBRDF brdf{color};

    if(SampleGenerator::Uniform01() > EliminationProbability(depth)){
        UT_Vector3F tangentVector;
        N.arbitraryPerp(tangentVector);
        UT_Vector3F perp = cross(tangentVector,N);

        auto coeffs = SampleGenerator::CosineWeightedHemisphereSample();

        auto recursiveRay = coeffs.x() * tangentVector + coeffs.y() * N + coeffs.z() * perp;

        GU_RayInfo recursiveInfo;
        recursiveInfo.init();

        int count = intersect->sendRay(P+0.001*recursiveRay,recursiveRay,recursiveInfo);



        if(count != 0){
            auto tmp = ComputeIllumination({P,recursiveRay},recursiveInfo,depth++);

            auto evalBrdf = brdf.Evaluate(ray.dir,recursiveRay);
            colorBuffer.R.amount = tmp.R.amount * evalBrdf.R.amount;
            colorBuffer.G.amount = tmp.G.amount * evalBrdf.G.amount;
            colorBuffer.B.amount = tmp.B.amount * evalBrdf.B.amount;

            return colorBuffer;
        }

    }

    //Compute local color
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

        auto radiosity = (1.0/(d*d)) * sample.myIntensity * (mult > 0 ? mult : 0);
        auto evalBrdf = brdf.Evaluate(ray.dir,L);
        colorBuffer.R.amount += radiosity * evalBrdf.R.amount;
        colorBuffer.G.amount += radiosity * evalBrdf.G.amount;
        colorBuffer.B.amount += radiosity * evalBrdf.B.amount;
    }
    return colorBuffer;
}