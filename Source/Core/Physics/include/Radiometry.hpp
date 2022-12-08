//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_QUANTITIES_HPP
#define NPRG045_QUANTITIES_HPP

#include <stdexcept>
#include <array>


enum class RadiometricQuantities{
    RadiantEnergy, // J
    RadiantFlux, // J/s = W
    Intensity, // W/sr
    Irradiance, // W/m^2
    Radiance // W/(m^2 sr)
};

template<RadiometricQuantities Q>
struct RadiometricQuantity{
    float amount;
    RadiometricQuantity(float amount){
        this->amount = amount;
    }
};

using Radiance = RadiometricQuantity<RadiometricQuantities::Radiance>;

using RGBRadiance = std::array<Radiance,3>;



template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator+(RadiometricQuantity<Q> A, RadiometricQuantity<Q> B){
    return RadiometricQuantity<Q>(A.amount + B.amount);
}

template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator-(RadiometricQuantity<Q> A, RadiometricQuantity<Q> B){
    return RadiometricQuantity<Q>(A.amount + B.amount);
}

template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator/(RadiometricQuantity<Q> A, RadiometricQuantity<Q> B){
    if(B.amount == 0){
        throw std::invalid_argument( "zero division error" );
    }
    return RadiometricQuantity<Q>(A.amount / B.amount);
}

template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator*(RadiometricQuantity<Q> A, float B){
    return RadiometricQuantity<Q>(A.amount * B);
}

template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator+(RadiometricQuantity<Q> A, float B){
    return RadiometricQuantity<Q>(A.amount + B);
}

template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator-(RadiometricQuantity<Q> A, float B){
    return RadiometricQuantity<Q>(A.amount + B);
}

template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator/(RadiometricQuantity<Q> A, float B){
    if(B == 0){
        throw std::invalid_argument( "zero division error" );
    }
    return RadiometricQuantity<Q>(A.amount / B);
}

template<RadiometricQuantities Q>
RadiometricQuantity<Q> operator*(RadiometricQuantity<Q> A, RadiometricQuantity<Q> B){
    return RadiometricQuantity<Q>(A.amount * B.amount);
}

RGBRadiance operator+(const RGBRadiance & C1, const RGBRadiance & C2);
RGBRadiance operator-(const RGBRadiance & C1, const RGBRadiance & C2);
RGBRadiance operator*(float a, const RGBRadiance &C);

#endif //NPRG045_QUANTITIES_HPP
