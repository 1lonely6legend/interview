//
// Created by CHH3213 on 2024/1/2.
//

#ifndef MATH_GEOMETRY_PROJECTION_H
#define MATH_GEOMETRY_PROJECTION_H
#include "Geometry.h"
# include "utils.h"

// Compute projection length of point p.
double ComputeProjectionLength(const Point& p,const Segment& segment){
    const auto& p1p = p-segment.start;
    return DotProduct(p1p,segment.unit_direction());
}

// Compute projection point of point p.
Point ComputeProjection(const Point& p,const Segment& segment){
    double projection_length = ComputeProjectionLength(p,segment);
    return segment.start + segment.unit_direction()*projection_length;
}


#endif //MATH_GEOMETRY_PROJECTION_H
