cmake_minimum_required(VERSION 3.28)
project(interview_problem)
set(CMAKE_CXX_STANDARD 17)

add_executable(angle angle_calculate.cpp)
add_executable(bbox Bbox_collision_check.cpp)
add_executable(vec_projecction 向量投影_点与向量位置关系.cpp)
add_executable(rotate_point CoordinateSystemTransformation.cpp)