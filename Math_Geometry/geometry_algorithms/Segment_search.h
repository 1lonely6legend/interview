//
// Created by CHH3213 on 2024/1/6.
//

#ifndef MATH_GEOMETRY_SEGMENT_SEARCH_H
#define MATH_GEOMETRY_SEGMENT_SEARCH_H

#include "utils.h"
#include "Geometry.h"
#include "Distance.h"
#include "Projection.h"

// Find the given point's closest segment in polyline using linear search.
// Option 1.
Segment FindClosestSegmentByLinearSearch(const Point& point, const Polyline& polyline){
    const auto points = polyline.Points();
    const auto segments = polyline.Segments();
    //Compute the square distance between given point and first point in polyline.
    double min_dist_sq = GetDistance(point,points[0]);
    int closest_segment_index = 0;
    for(int i=1;i<points.size();++i){
        const auto& p1 = points[i-1];
        const auto& p2 = points[i];
        const auto& seg = segments[i-1];
        const auto& v = seg.unit_direction();
        const auto& w = point-p1;
        const double c1 = DotProduct(w,v);
        if(c1<=0){
            continue;
        }
        double dist_sq= 0.0;
        const double c2 = seg.length();
        if(c2<=c1){
            dist_sq = GetDistance(point,p2);
        }else{
            dist_sq = GetDistance(point,seg);
        }

        if(dist_sq<min_dist_sq){
            min_dist_sq = dist_sq;
            closest_segment_index=i-1;
            if(min_dist_sq<Epsilon){
                break;
            }
        }

    }
    return segments[closest_segment_index];
}

// Find the given point's closest segment in polyline using linear search.
// Option 2: since we have implemented distance function, we can directly use it.
//Segment FindClosestSegmentByLinearSearch(const Point& point, const Polyline& polyline){
//    const auto& points = polyline.Points();
//    const auto& segments = polyline.Segments();
//    //Compute the square distance  between given point and first point in polyline.
//    double min_dist_sq = GetDistance(point,points[0]);
//    int closest_segment_index = 0;
//    for(int i=0;i<segments.size();++i){
//        const auto& seg = segments[i];
//        const double dist_sq = GetDistance(point,seg);
//        if(dist_sq<min_dist_sq){
//            min_dist_sq = dist_sq;
//            closest_segment_index=i;
//            if(min_dist_sq<Epsilon){
//                break;
//            }
//        }
//    }
//    return segments[closest_segment_index];
//}

#endif //MATH_GEOMETRY_SEGMENT_SEARCH_H
