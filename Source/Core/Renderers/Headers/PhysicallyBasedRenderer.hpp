//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_PHYSICALLYBASEDRENDERER_HPP
#define NPRG045_PHYSICALLYBASEDRENDERER_HPP

#include "Renderer.hpp"
#include "../../Physics/Headers/Radiometry.hpp"
#include "../../Scene/Headers/Light.hpp"
#include "ImageRepresentation.hpp"
#include "../../Materials/Headers/Texture.hpp"
#include "../../Materials/Headers/BRDF.hpp"


class PhysicallyBasedRenderer : public Renderer{
public:
    PhysicallyBasedRenderer(Scene myScene);
    virtual void ImproveTile(ImageTile & tile,int sampleCount) override;
private:
    Generator gen{};
    GU_RayIntersect * intersect;
    Color ComputePixel(UT_Vector2i coordinates);
    RGBRadiance ComputeIllumination(GU_Ray observer, int depth);
    RGBRadiance ComputeIndirectIllumination(GU_RayInfo info, GU_Ray observer, int depth);
    RGBRadiance ComputeDirectIllumination(GU_RayInfo info, GU_Ray observer);
    float EliminationProbability(int depth);
    std::vector<Texture *> textures;
    PBBRDF brdf;
};

#endif //NPRG045_PHYSICALLYBASEDRENDERER_HPP
