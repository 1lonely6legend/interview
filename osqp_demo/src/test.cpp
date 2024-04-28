//
// Created by ogier on 24-3-26.
// 求解二次规划问题
// min f(x_1,x_2,x_3) = (x_1 - 1)^2 + (x_2 - 2)^2 + (x_3 - 3)^2 + (x_1 - x_2)^2 + (x_2 - x_3)^2
// 约束为无约束
// 得到矩阵p和向量q,其中p为Hessian矩阵,q为梯度向量,p = [2 -1 0;-1 3 -1;0 -1 2],q = [-2 -4 -6]
#include "Eigen/Dense"
#include "OsqpEigen/OsqpEigen.h"
#include "iostream"
#include <Eigen/src/Core/Matrix.h>
#include <Eigen/src/SparseCore/SparseMatrix.h>
#include <OsqpEigen/Solver.hpp>

int main() {
  Eigen::SparseMatrix<double> hessian(3, 3);
  Eigen::VectorXd gardient(3);

  hessian.insert(0, 0) = 2;
  hessian.insert(1, 0) = -1;
  hessian.insert(0, 1) = -1;
  hessian.insert(1, 1) = 3;
  hessian.insert(1, 2) = -1;
  hessian.insert(2, 1) = -1;
  hessian.insert(2, 2) = 2;

  gardient << -2, -4, -6;

  OsqpEigen::Solver solver;
  solver.settings()->setVerbosity(true);
  solver.settings()->setWarmStart(true);

  solver.data()->setNumberOfVariables(3);
  solver.data()->setNumberOfConstraints(0);

  solver.data()->setHessianMatrix(hessian);
  solver.data()->setGradient(gardient);

  solver.initSolver();

  Eigen::VectorXd QPanswer;

  solver.solve();

  QPanswer = solver.getSolution();
  std::cout << "QPanswer" << QPanswer << std::endl;

  return 0;
}
