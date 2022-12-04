//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_PHYSICALLYBASEDRENDERER_HPP
#define NPRG045_PHYSICALLYBASEDRENDERER_HPP

#include <tuple>

#include "Renderer.hpp"
#include "../../Physics/include/Radiometry.hpp"
#include "../../Scene/include/Light.hpp"
#include "ImageRepresentation.hpp"
#include "../../Materials/include/Texture.hpp"
#include "../../Materials/include/PB_BxDF.hpp"

class PhysicallyBasedRenderer : public Renderer{
public:
    PhysicallyBasedRenderer(Scene myScene);
    virtual void ImproveTile(ImageTile & tile,int sampleCount) override;
private:
    Generator gen{};
    GU_RayIntersect * intersect;
    Color ComputePixel(UT_Vector2i coordinates);
    TextureData GetTextureData(GU_RayInfo info, UT_Vector3F position);
    RGBRadiance ComputeIllumination(UT_Vector3F observationDir, UT_Vector3F observationPos, int depth);
    RGBRadiance ComputeIntersectionIllumination(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos, int depth);
    RGBRadiance ComputeReflection(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos, int depth);
    RGBRadiance ComputeRefraction(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos, int depth);
    RGBRadiance ComputeDirectIllumination(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos);
    float Shadow(UT_Vector3F intersectionPosition, UT_Vector3F lightDir, float lightDistance);

//    std::tuple<RGBRadiance,float> ComputeIndirectIllumination(GU_RayInfo info, GU_Ray observer, int depth);
//    std::tuple<RGBRadiance,float> ComputeDirectIllumination(GU_RayInfo info, GU_Ray observer);
//    RGBRadiance ComputeRefraction(GU_RayInfo, GU_Ray observer, int depth);
//    TextureData GetTextureData(GU_RayInfo,UT_Vector3F);

    float EliminationProbability(int depth);
    bool ShouldEliminate(int depth);
    std::vector<Texture *> Textures;
    std::unique_ptr<Texture> DefaultTexture;
    PB_BSDF BSDF;
};

#endif //NPRG045_PHYSICALLYBASEDRENDERER_HPP
