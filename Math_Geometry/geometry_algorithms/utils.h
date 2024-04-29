//
// Created by CHH3213 on 2024/1/2.
//

#ifndef MATH_GEOMETRY_UTILS_H
#define MATH_GEOMETRY_UTILS_H
#include <iostream>
#include <vector>
#include "Geometry.h"

constexpr double Epsilon = 1e-6;

using Vec = Point;

// Calculates dot product.
double DotProduct(const Vec& v1,const Vec& v2){
    return v1.x*v2.x+v1.y*v2.y;
}

// Calculates cross product.
double CrossProduct(const Vec& v1,const Vec& v2) {
    return v1.x*v2.y-v2.x*v1.y;
}

// Define a sign function.
int Sign(double x){
    return x<0?-1:x>0?1:0;
}



#endif //MATH_GEOMETRY_UTILS_H
