cmake_minimum_required(VERSION 3.25)
project(Math_Geometry)

set(CMAKE_CXX_STANDARD 17)

add_executable(Math_Geometry main.cpp geometry_algorithms/utils.h geometry_algorithms/Projection.h geometry_algorithms/Geometry.h geometry_algorithms/Distance.h geometry_algorithms/Side.h geometry_algorithms/Intersection.h geometry_algorithms/Curvature.h geometry_algorithms/Segment_search.h)

add_subdirectory(geometry_algorithms)
add_subdirectory(math)