//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "../../Mathematics/Headers/Sampling.hpp"
#include "../Headers/OldDistributedRaytracer.hpp"
#include "../../Mathematics/Headers/Vectors.hpp"
#include "../../Materials/Headers/LambertBRDF.hpp"

//OldDistributedRaytracer::OldDistributedRaytracer(Scene myScene) : OldRenderer(myScene) {
//    intersect = new GU_RayIntersect(scene.geometry.gdh->gdp());
//}
//
//void OldDistributedRaytracer::ImproveTile(ImageTile &tile, int sampleCount) {
//    Generator gen{};
//
//    float previousWeight = tile.sampleCount == 0 ? 0.0 : ((float)tile.sampleCount) / (sampleCount + tile.sampleCount);
//    float currentWeight = 1 - previousWeight;
//    float sampleMultiplier = 1.0/sampleCount;
//    float currentMultiplier = currentWeight*sampleMultiplier;
//
//    tile.sampleCount += sampleCount;
//
//    int tileSizeX = tile.viewCoords.tx1 - tile.viewCoords.tx0;
//    int tileSizeY = tile.viewCoords.ty1 - tile.viewCoords.ty0;
//
//    for(int x = 0; x <= tileSizeX; ++x){
//        for(int y = 0; y <= tileSizeY; ++y){
//            Color buffer{};
//            for(int i = 0; i < sampleCount; ++i){
//                buffer = buffer + RenderPixel({tile.viewCoords.tx0 + x,tile.viewCoords.ty0 + y});
//            }
//            tile.data[x][y] = previousWeight * tile.data[x][y] + currentMultiplier * buffer;
//        }
//    }
//}
//
//constexpr size_t recursionDepth = 10;
//
//Color OldDistributedRaytracer::RenderPixel(UT_Vector2i coordinates) {
//
//    auto ray = scene.camera.GenerateRay(coordinates);
//
//    GU_RayInfo info;
//    info.init();
//
//    int count = intersect->sendRay(ray.org,ray.dir,info);
//    if(count == 0){
//        return {{0},{0},{0},1};
//    }
//    else{
//        return ComputeColor(ray,info,recursionDepth);
//    }
//
//}
//
//float eliminationProbability = 0.25;
//
//Color OldDistributedRaytracer::ComputeColor(const GU_Ray & ray, const GU_RayInfo & info, int depth) {
//    auto P = ray.org + info.myT * ray.dir;
//
////    std::cout << N << std::endl;
//    auto N = scene.geometry.IntersectionVertexNormal(info);
//    auto Cd = scene.geometry.IntersectionPointColor(info);
////    UT_Vector3F Cd = {1,1,1};
//
//    Color color{{Cd.x()},{Cd.y()},{Cd.z()},0};
//    LambertBRDF brdf{color};
//
//    //Direct illumination
//
//    Color rtrval{{0},{0},{0},0};
//
//    float totalLight{0};
//
//    if(SampleGenerator::Uniform01() > eliminationProbability){
////        auto recursiveRay = brdf.Sample(ray.dir);
//
//        UT_Vector3F tangentVector;
//        N.arbitraryPerp(tangentVector);
//        UT_Vector3F perp = cross(tangentVector,N);
//
//        auto coeffs = SampleGenerator::CosineWeightedHemisphereSample();
//
//        auto recursiveRay = coeffs.x() * tangentVector + coeffs.y() * N + coeffs.z() * perp;
//
//        GU_RayInfo recursiveInfo;
//        recursiveInfo.init();
//
//        int count = intersect->sendRay(P+0.001*recursiveRay,recursiveRay,recursiveInfo);
//        if(count != 0){
//            auto tmp = ComputeColor({P,recursiveRay},recursiveInfo,0);
//            auto evalBrdf = brdf.Evaluate(ray.dir,recursiveRay);
//            tmp.R.amount *= evalBrdf.R.amount;
//            tmp.G.amount *= evalBrdf.G.amount;
//            tmp.B.amount *= evalBrdf.B.amount;
//            return tmp;
//        }
//    }
//
//    for(auto && light : scene.lights){
//        auto sample = light->GenerateSample();
//        auto L = Normalize<2>(sample.myPosition - P);
//
//        GU_RayInfo shadowInfo;
//        shadowInfo.init();
//
//        if(intersect->sendRay(P+0.001*L,L,shadowInfo) > 0){
//            if(shadowInfo.myT < 1) continue;
//        }
//
//        auto d = Norm<2>(sample.myPosition - P);
//        auto mult = dot(L,N);
//
//        auto radiosity = (1.0/(d*d)) * sample.myIntensity * (mult > 0 ? mult : 0);
//        auto evalBrdf = brdf.Evaluate(ray.dir,L);
//        rtrval.R.amount += radiosity * evalBrdf.R.amount;
//        rtrval.G.amount += radiosity * evalBrdf.G.amount;
//        rtrval.B.amount += radiosity * evalBrdf.B.amount;
//    }
//
//    return rtrval;
//}
