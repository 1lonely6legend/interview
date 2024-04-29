//
// Created by CHH3213 on 2024/1/6.
//

#ifndef MATH_GEOMETRY_CURVATURE_H
#define MATH_GEOMETRY_CURVATURE_H

#include "utils.h"
#include "Geometry.h"

// Obtain curvature according to p1,p2,p3.
// NOTE : curvature has a sign, not just an unsigned value.
double GetCurvature(const Point& p1, const Point& p2, const Point& p3){
    const auto& p1p2 = p2 - p1;
    const auto& p2p3 = p3 - p2;
    const auto& p1p3 = p3 - p1;
    const auto& a = p1p2.modulus();
    const auto& b = p2p3.modulus();
    const auto& c = p1p3.modulus();
    const auto cross_product = CrossProduct(p1p2, p2p3);
    return 2 * cross_product / (a * b * c);
}

#endif // MATH_GEOMETRY_CURVATURE_H
