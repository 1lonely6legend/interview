//
// Created by CHH3213 on 2024/1/6.
//

#ifndef MATH_GEOMETRY_INTERSECTION_H
#define MATH_GEOMETRY_INTERSECTION_H

#include "Geometry.h"
#include"utils.h"
#include "Side.h"


// Determine whether segment 1 intersects segment 2.
bool IsIntersection(const Segment& s1, const Segment& s2){
    const double o1 = CrossProduct(s2.start - s1.start, s1.direction);
    const double o2 = CrossProduct(s2.end - s1.start, s1.direction);
    const double o3 = CrossProduct(s1.start - s2.start, s2.direction);
    const double o4 = CrossProduct(s1.end - s2.start, s2.direction);
    // Segments are considered intersecting if they have different orientations.
    if(o1 * o2 < 0 && o3 * o4 < 0){
        return true;
    }

    auto on_segment = [](const Point &p, const Point &q, const Point &r){
        return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
                q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
    };
    // Additional checks for collinear points.
    if(o1 == 0 && on_segment(s1.start, s2.start, s1.end)){
        return true;
    }

    if(o2 == 0 && on_segment(s1.start, s2.end, s1.end)){
        return true;
    }

    if(o3 == 0 && on_segment(s2.start, s1.start, s2.end)){
        return true;
    }

    if(o4 == 0 && on_segment(s2.start, s1.end, s2.end)){
        return true;
    }

    return false;
}

//Calculate the intersection between segment 𝑝0𝑝1 and segment 𝑝2𝑝3.
Point GetIntersectionPoint(const Segment& s1, const Segment& s2){
    if(!IsIntersection(s1, s2)){
        std::cout << "No intersection, return a deafult point value:(0,0)!";
        return Point(0, 0);
    }
    const auto& u = s1.direction;
    const auto& v = s2.direction;
    const auto& w = s1.start - s2.end;
    const auto c1 = CrossProduct(w, v);
    const auto c2 = CrossProduct(v, u);
    if(c2 != 0){
        const double t = std::abs(c1 / c2);
        return s1.start + t * u;
    }
    // Address collinear and overlapping situation. If so, we return overlaping start or end.
    const auto side_1 = GetSide(s1.start, s2);
    const auto side_2 = GetSide(s1.end, s2);
    const auto side_3 = GetSide(s2.start, s1);
    const auto side_4 = GetSide(s2.end, s1);
    if(side_1 == Side::WITHIN){
        return s1.start;
    }
    if(side_2 == Side::WITHIN){
        return s1.end;
    }
    if(side_3 == Side::WITHIN){
        return s2.start;
    }
    if(side_4 == Side::WITHIN){
        return s2.end;
    }
    throw std::runtime_error("Something is wrong, please check.");
}


#endif //MATH_GEOMETRY_INTERSECTION_H
