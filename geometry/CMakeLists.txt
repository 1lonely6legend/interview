cmake_minimum_required(VERSION 3.28)
project(interview_problem)
set(CMAKE_CXX_STANDARD 17)

find_package(Python3 COMPONENTS Development NumPy)
find_package(OsqpEigen REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(SYSTEM ${OSQP_EIGEN_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})

add_executable(vector_angle_projection_position vector_angle_projection_position.cpp utils.h)
target_link_libraries(vector_angle_projection_position Python3::Python Python3::NumPy)
target_link_libraries(vector_angle_projection_position OsqpEigen::OsqpEigen)

add_executable(aabb_collision_check aabb_collision_check.cpp)
target_link_libraries(aabb_collision_check Python3::Python Python3::NumPy)
target_link_libraries(aabb_collision_check OsqpEigen::OsqpEigen)

add_executable(check_convex_polygon.cpp check_convex_polygon.cpp utils.h)
target_link_libraries(check_convex_polygon.cpp Python3::Python Python3::NumPy)
target_link_libraries(check_convex_polygon.cpp OsqpEigen::OsqpEigen)

add_executable(coordinate_transformation coordinate_transformation.cpp utils.h)

