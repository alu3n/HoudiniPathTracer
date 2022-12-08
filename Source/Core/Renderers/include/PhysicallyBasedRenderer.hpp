//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_PHYSICALLYBASEDRENDERER_HPP
#define NPRG045_PHYSICALLYBASEDRENDERER_HPP

#include <tuple>

#include "Renderer.hpp"
#include "../../Physics/include/Units.hpp"
#include "../../Scene/include/Light.hpp"
#include "ImageRepresentation.hpp"
#include "../../Materials/include/Texture.hpp"
#include "../../Materials/include/BxDF.hpp"
//#include "../../Materials/include/PB_BxDF.hpp"

class PhysicallyBasedRenderer : public Renderer{
public:
    PhysicallyBasedRenderer(Scene myScene);
    virtual void ImproveTile(ImageTile & tile,int sampleCount) override;
private:
    Generator gen{};
    GU_RayIntersect * intersect;
    Color ComputePixel(UT_Vector2i coordinates);
    TextureData GetTextureData(GU_RayInfo info, UT_Vector3F position);
    RGBEnergy ComputeIllumination(UT_Vector3F observationDir, UT_Vector3F observationPos, int depth);
    RGBEnergy ComputeIntersectionIllumination(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos, int depth);
    RGBEnergy ComputeReflection(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos, int depth);
    RGBEnergy ComputeRefraction(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos, int depth);
    RGBEnergy ComputeDirectIllumination(const TextureData & textureData, UT_Vector3F normalDir, UT_Vector3F observationDir, UT_Vector3F intersectionPos);
    bool Shadow(UT_Vector3F intersectionPosition, UT_Vector3F lightDir, float lightDistance);

    float EliminationProbability(int depth);
    bool ShouldEliminate(int depth);

    std::vector<std::unique_ptr<Material>> Materials;
    std::unique_ptr<Material> DefaultMaterial;
};

#endif //NPRG045_PHYSICALLYBASEDRENDERER_HPP
