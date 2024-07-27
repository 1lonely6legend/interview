cmake_minimum_required(VERSION 3.28)
project(math)
set(CMAKE_CXX_STANDARD 17)

add_executable(Newton_Solve_Equation.cpp ./Newton_Solve_Equation.cpp)
add_executable(Newton_Extreme_Value.cpp ./Newton_Extreme_Value.cpp)
add_executable(Newtown_Sqrt.cpp ./Newtown_Sqrt.cpp)
add_executable(Gradient_Descent_Extreme_Value_Multi_Variable.cpp ./GradientDescent_Extreme_Value_Multi_Variable.cpp)
add_executable(Gradient_Descent_Extreme_Value.cpp ./Gradient_Descent_Extreme_Value.cpp)
add_executable(Gradient_Descent_Solve_Equation.cpp ./Gradient_Descent_Solve_Equation.cpp)


