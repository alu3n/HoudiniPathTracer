//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_DISTRIBUTEDRAYTRACER_HPP
#define NPRG045_DISTRIBUTEDRAYTRACER_HPP

#include "Renderer.hpp"

class DistributedRaytracer : public Renderer{
public:
    void ImproveTile(ImageTile & tile, int sampleCount) override;
};

#endif //NPRG045_DISTRIBUTEDRAYTRACER_HPP
