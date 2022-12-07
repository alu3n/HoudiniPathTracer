//
// Created by Vojtěch Pröschl on 07.12.2022.
//

#ifndef NPRG045_MATERIALLIBRARY_HPP
#define NPRG045_MATERIALLIBRARY_HPP

#include "Texture.hpp"

class MaterialDefault : public ConstantTexture{
public:
    MaterialDefault();
};

class MaterialGlass : public ConstantTexture{
public:
    MaterialGlass();
};

class MaterialPianoBlack : public ConstantTexture{
public:
    MaterialPianoBlack();
};

class MaterialPlastic : public ConstantTexture{
public:
    MaterialPlastic();
};

class MaterialRubber : public ConstantTexture{
public:
    MaterialRubber();
};

class MaterialPorcelain : public ConstantTexture{
public:
    MaterialPorcelain();
};

class MaterialMarble : public ConstantTexture{
public:
    MaterialMarble();
};

class MaterialRock : public ConstantTexture{
public:
    MaterialRock();
};




#endif //NPRG045_MATERIALLIBRARY_HPP
