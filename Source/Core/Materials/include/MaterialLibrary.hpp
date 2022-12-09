//
// Created by Vojtěch Pröschl on 07.12.2022.
//

#ifndef NPRG045_MATERIALLIBRARY_HPP
#define NPRG045_MATERIALLIBRARY_HPP

#include "../include/Material.hpp"

class MaterialDefault : public ConstantMaterial{
public:
    MaterialDefault();
};

class MaterialGlass : public ConstantMaterial{
public:
    MaterialGlass();
};

class MaterialPianoBlack : public ConstantMaterial{
public:
    MaterialPianoBlack();
};

class MaterialPlastic : public ConstantMaterial{
public:
    MaterialPlastic();
};

class MaterialRubber : public ConstantMaterial{
public:
    MaterialRubber();
};

class MaterialPorcelain : public ConstantMaterial{
public:
    MaterialPorcelain();
};

class MaterialMarble : public ConstantMaterial{
public:
    MaterialMarble();
};

class MaterialRock : public ConstantMaterial{
public:
    MaterialRock();
};

class MaterialRoughGlass : public ConstantMaterial{
public:
    MaterialRoughGlass();
};

class ProceduralTiles : public Material{
public:
    TextureData Evaluate(UT_Vector3F position) override;
};




#endif //NPRG045_MATERIALLIBRARY_HPP
