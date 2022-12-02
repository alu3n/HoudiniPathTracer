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
//#include "../../Materials/include/BxDF.hpp"
#include "../../Materials/include/PB_BxDF.hpp"

class PhysicallyBasedRenderer : public Renderer{
public:
    PhysicallyBasedRenderer(Scene myScene);
    virtual void ImproveTile(ImageTile & tile,int sampleCount) override;
private:
    Generator gen{};
    GU_RayIntersect * intersect;
    Color ComputePixel(UT_Vector2i coordinates);
    RGBRadiance ComputeIllumination(GU_Ray observer, int depth, float IOR);
    std::tuple<RGBRadiance,float> ComputeIndirectIllumination(GU_RayInfo info, GU_Ray observer, int depth, float IOR);
    std::tuple<RGBRadiance,float> ComputeDirectIllumination(GU_RayInfo info, GU_Ray observer, float IOR);
    float EliminationProbability(int depth);
    std::vector<Texture *> textures;
    std::unique_ptr<Texture> DefaultTexture;
    PB_BSDF bsdf;
};

#endif //NPRG045_PHYSICALLYBASEDRENDERER_HPP
