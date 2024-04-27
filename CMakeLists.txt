cmake_minimum_required(VERSION 3.28)
project(interview_problem)
set(CMAKE_CXX_STANDARD 17)

#add_executable(a_star jiushi/a_star.cpp)
#
#add_executable(dijkstra jiushi/dijkstra.cpp)

add_executable(angle sensetime/angle_calculate.cpp)
add_executable(bbox sensetime/Bbox_collision_check.cpp)
add_executable(vec_projecction sensetime/向量投影_点与向量位置关系.cpp)

add_executable(main main.cpp)