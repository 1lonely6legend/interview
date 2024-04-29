//
// Created by CHH3213 on 2024/1/6.
//

#ifndef MATH_GEOMETRY_SIDE_H
#define MATH_GEOMETRY_SIDE_H
#include<cmath>

#include "Geometry.h"
#include "utils.h"
#include <cassert>


/**
 * This file contains the relative position of point to segment.
 */
enum class Side{
    // When the segment's length is zero, it's useless to determine the side, so we use DEFAULT_NO_SIDE to show.
    DEFAULT_NO_SIDE=0,
    LEFT,
    RIGHT,
    // The three below states mean that the point is in line.
    ON_AFTER,
    ON_BEFORE,
    WITHIN
};


// Determine which side of the segment the point is.
Side GetSide(const Point& p,const Segment& s){
    const auto& p0 = s.start;
    const auto& p2 = s.end;
    const auto& a = p-p0;
    const auto& b = p2-p0;
    const auto cross_product = CrossProduct(a,b);
    if(cross_product!=0){
        // Returns LEFT if p0,p,p2 are clockwise position, returns RIGHT means p0,p,p2 are counter-clockwise position.
        return cross_product<0?Side::LEFT:Side::RIGHT;
    }
    const auto dot_product = DotProduct(a,b);
    if(dot_product<0){
        return Side::ON_BEFORE;
    }else if(dot_product>0){
        if(b.modulus()<a.modulus()){
            return Side::ON_AFTER;
        }else{
            return Side::WITHIN;
        }
    }else{
        if(a.modulus()==0){
            return Side::WITHIN;
        }
        return Side::DEFAULT_NO_SIDE;
    }
}

// Determine which side of two segments the point is.
//Method 1: directly use cross product to determine and only have left/right options.
//Side GetSide(const Point& p, const Segment& s1,const Segment& s2) {
//    //DCHECK(s1.end==s2.start)<<"please ensure the two segments are connected.";
//    if (s1.end != s2.start) {
//        throw std::runtime_error("Error: The two segments are not connected.");
//    }
//    const auto& p0p = p-s1.start;
//    const auto& p1p = p-s2.start;
//    const auto c1 = CrossProduct(s1.direction,p0p);
//    const auto c2 = CrossProduct(s2.direction,p1p);
//
//    if(c1>0&&c2>0){
//        return Side::LEFT;
//    }
//    if(c1<0&&c2<0){
//        return Side::RIGHT;
//    }
//    return std::abs(c1)>std::abs(c2)?Side::LEFT:Side::RIGHT;
//}

// Determine which side of two segments the point is.
// Method 2: through the side of p to one segment to determine, and except left/right side, we also provide other options.
Side GetSide(const Point& p, const Segment& s1,const Segment& s2) {
    //DCHECK(s1.end==s2.start)<<"please ensure the two segments are connected.";
    if (s1.end != s2.start) {
        throw std::runtime_error("Error: The two segments are not connected.");
    }
    const auto side_1 = GetSide(p,s1);
    const auto side_2 = GetSide(p,s2);
    if(side_1==side_2){
        return side_1;
    }
    if(side_1==Side::WITHIN||side_2==Side::WITHIN){
        return Side::WITHIN;
    }
    const auto& p0p = p-s1.start;
    const auto& p1p = p-s2.start;
    const auto c1 = CrossProduct(s1.direction,p0p);
    const auto c2 = CrossProduct(s2.direction,p1p);
    return std::abs(c2) > std::abs(c1) ? side_2 : side_1;
}




#endif //MATH_GEOMETRY_SIDE_H
