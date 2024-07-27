cmake_minimum_required(VERSION 3.28)
project(math)
set(CMAKE_CXX_STANDARD 17)

find_package(Python3 COMPONENTS Development NumPy)
find_package(OsqpEigen REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(Newton_Solve_Equation.cpp ./Newton_Solve_Equation.cpp)
add_executable(Newton_Extreme_Value.cpp ./Newton_Extreme_Value.cpp)
add_executable(Newtown_Sqrt.cpp ./Newtown_Sqrt.cpp)
add_executable(Gradient_Descent_Extreme_Value_Multi_Variable.cpp ./GradientDescent_Extreme_Value_Multi_Variable.cpp)
add_executable(Gradient_Descent_Extreme_Value.cpp ./Gradient_Descent_Extreme_Value.cpp)
add_executable(Gradient_Descent_Solve_Equation.cpp ./Gradient_Descent_Solve_Equation.cpp)
add_executable(matrix.cpp ./matrix.cpp)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories(SYSTEM ${OSQP_EIGEN_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})

add_executable(Lagrange_Interpolation.cpp ./Lagrange_Interpolation.cpp)

target_link_libraries(Lagrange_Interpolation.cpp Python3::Python Python3::NumPy)
target_link_libraries(Lagrange_Interpolation.cpp OsqpEigen::OsqpEigen)
