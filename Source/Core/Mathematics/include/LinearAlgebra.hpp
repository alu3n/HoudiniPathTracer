//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#ifndef NPRG045_VECTORS_HPP
#define NPRG045_VECTORS_HPP

#include <array>
#include <iostream>


//Todo:
// - Access row/column (matrix)
// - Access specific element (different for matrix and vector)

template<int rows, int columns>
class Matrix{
    std::array<std::array<float,columns>,rows> Data;
    //Todo: Create constructor
};

template<int rows>
using ColumnVector = Matrix<rows,1>;

template<int columns>
using RowVector = Matrix<1,columns>;

template<int rows>
using Vector = ColumnVector<rows>;

template<int rows,int columns>
Matrix<columns,rows> Transpose(){
    //Todo: Implement
}

template<int rows, int columns>
Matrix<rows, columns> operator+(Matrix<rows, columns> A, Matrix<rows,columns> B){
    //Todo: Implement
}

template<int rows, int columns>
Matrix<rows, columns> operator-(Matrix<rows, columns> A, Matrix<rows,columns> B){
    //Todo: Implement
}

template<int rows, int columns>
Matrix<rows, columns> operator*(float a, Matrix<rows,columns> B){
    //Todo: Implement
}

template<int rows, int columns>
Matrix<rows, columns> operator*(Matrix<rows, columns> A, Matrix<columns,rows> B){
    //Todo: Implement
}

template<int rows, int columns>
RowVector<columns> GetRowVector(int i){
    //Todo: Implement
}

template<int rows, int columns>
ColumnVector<rows> GetColumnVector(int j){
    //Todo: Implement
}
template<int rows, int columns>
void operator<<(std::ostream & os, Matrix<rows,columns> A){
    //Todo: Implement
}







//template<int n>
//class Vector{
//
//};

//template<>

//#include <UT/UT_Vector3.h>

//template<int p>
//float Norm(UT_Vector3F V){
//    return pow(pow(V.x(),p)+pow(V.y(),p)+pow(V.z(),p),1.0/p);
//}
//
//template<int p>
//UT_Vector3F Normalize(UT_Vector3F V){
//    return (1.0/Norm<p>(V))*V;
//}


#endif //NPRG045_VECTORS_HPP
