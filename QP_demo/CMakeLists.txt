cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

project(OsqpEigen-Example)

find_package(OsqpEigen)
find_package(Eigen3)

include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})

#MPCExample
add_executable(main src/main.cpp)
target_link_libraries(main OsqpEigen::OsqpEigen)

add_executable(test src/test.cpp)
target_link_libraries(test OsqpEigen::OsqpEigen)