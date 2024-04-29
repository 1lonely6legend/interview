#include <iostream>

#include "geometry_algorithms/Geometry.h"
#include"geometry_algorithms/Projection.h"
#include "geometry_algorithms/Distance.h"
#include "geometry_algorithms/Side.h"
#include"geometry_algorithms/Intersection.h"
#include "geometry_algorithms/Curvature.h"
#include "geometry_algorithms/Segment_search.h"

int main() {
    Point point(3, 4);
    Segment segment(Point(0.0, 0.0), Point(10.0, 0.0));
    Point projection = ComputeProjection(point, segment); // (3, 0)
    std::cout <<"projection: "<< projection << std::endl;

    Point p1(1, 1), p2(4, 5);
    std::cout << "Distance between p1 and p2: "
              << GetDistance(p1, p2) << std::endl;//5.0.
    Line line(Point(0, 0), Point(10, 0));
    Point p(3, 4);
    std::cout << "Distance between p and line: "
              << GetDistance(p, line) << std::endl;//4.0.
    Segment seg(Point(5, 5), Point(9, 6));
    std::cout << "Distance between p and segment: "
              << GetDistance(p, seg) << std::endl;//2.2367.


    Segment s1(Point(1,1), Point(4,1));
    Segment s2(Point(2,3), Point(5,4));
    double dist = GetDistance(s1, s2);
    std::cout << "Distance: " << dist << std::endl;//2.0
    Segment s3(Point(2,2), Point(3,2));
    dist = GetDistance(s1, s3);
    std::cout << "Distance: " << dist << std::endl;//1.0


    // Create points and segments for testing
    Point p_t(2,2.5);
    Point p3(0.0, 0.0);
    Point p4(1.0, 1.0);
    Point p5(2.0, 3.0);

    Segment s4(p3, p4);
    Segment s5(p4, p5);

    // Test GetSide function for a single segment
    Side side = GetSide(p_t, s4);
    std::cout << "Relative position to single segment: ";
    switch (side) {
        case Side::LEFT:
            std::cout << "LEFT";
            break;
        case Side::RIGHT:
            std::cout << "RIGHT";
            break;
        case Side::ON_AFTER:
            std::cout << "ON_AFTER";
            break;
        case Side::ON_BEFORE:
            std::cout << "ON_BEFORE";
            break;
        case Side::WITHIN:
            std::cout << "WITHIN";
            break;
        default:
            std::cout << "DEFAULT_NO_SIDE";
    }
    std::cout << std::endl;

    // Test GetSide function for two connected segments (Method 1)
    try {
        Side sideMethod1 = GetSide(p_t, s4, s5);
        std::cout << "Relative position to connected segments: ";
        switch (sideMethod1) {
            case Side::LEFT:
                std::cout << "LEFT";
                break;
            case Side::RIGHT:
                std::cout << "RIGHT";
                break;
            case Side::ON_AFTER:
                std::cout << "ON_AFTER";
                break;
            case Side::ON_BEFORE:
                std::cout << "ON_BEFORE";
                break;
            case Side::WITHIN:
                std::cout << "WITHIN";
                break;
            default:
                std::cout << "DEFAULT_NO_SIDE";
        }
        std::cout << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    Segment s6({1, 1}, {4, 4});
    Segment s7({2, 2}, {5, 5});

    // Check if the segments intersect
    if (IsIntersection(s6, s7)) {
        // If they intersect, get the intersection point
        Point intersection = GetIntersectionPoint(s6, s7);
        std::cout << "Segments are intersecting at " << intersection << std::endl;
    } else {
        std::cout << "Segments are not intersecting." << std::endl;
    }

    Point p10{1.0, 1.0};
    Point p20{2.0, 4.0};
    Point p30{3.0, 1.0};

    // Calculate curvature
    double curvature = GetCurvature(p10, p20, p30);

    // Print the result
    std::cout << "Curvature at points p1, p2, p3: " << curvature << std::endl;


    const std::vector<Point> points = {{0, 0}, {1, 1}, {2, 0}, {3, 1}, {4, 0}};
    Polyline polyline(points);
    Point testPoint{5.1, 1};
    Segment closestSegment = FindClosestSegmentByLinearSearch(testPoint, polyline);

    std::cout << "Closest Segment: " << closestSegment<< std::endl;

    return 0;
}
