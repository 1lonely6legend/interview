//
// Created by ogier on 24-7-28.
//
#include <bits/stdc++.h>
using namespace std;
/*
 * 使用梯度下降法求解二次方程y=ax^2+bx+c的根
 * 步骤：原函数->构造损失函数->对损失函数求导->进行梯度下降
 */
constexpr double DELTA = 1e-5;
constexpr double EPS = 1e-6;

double func(const double a, const double b, const double c, const double x) {
  return a * pow(x, 2) + b * x + c;
}

//构造损失函数，因为是求根，所以损失函数为(f(x)-0)^2,当然可以直接定义为f(x)
double loss_func(const double a, const double b, const double c, const double x) {
  return pow(func(a, b, c, x) - 0, 2);
}

//构造损失函数导数
double loss_func_prime(const double a, const double b, const double c, const double x) {
  return (loss_func(a, b, c, x + DELTA) - loss_func(a, b, c, x)) / DELTA;
}

/**
 * @detail 梯度下降算法
 * @param a,b,c 二次函数的系数
 * @param x0 迭代初值
 * @param learning_rate 学习率
 * @param max_iter 最大迭代次数
 * @return 函数的根
 */
double solve(const double a,
             const double b,
             const double c,
             const double x0,
             const double learning_rate,
             const size_t max_iter) {
  double x = x0, x_last = 0;
  size_t cnt = 0;
  while (cnt < max_iter) {
    cnt++;
    x_last = x;
    x = x_last - learning_rate * loss_func_prime(a, b, c, x_last);
    if (fabs(x - x_last) < EPS) {
      cout << "cnt: " << cnt << " x=" << x << endl;
      return x;
    }
  }
  cout << "fail:max iter. x=" << x << endl;
  return x;
}

int main() {
  double a = 1.0, b = 2.0, c = -3.0;
  //通过设置不同初值找出来,选择合适的初值可以加速收敛
  //计算-b / (2 * a)得到的是函数的极值点，在极值点附近进行梯度下降从而找到不同的根
  double x0 = -b / (2 * a) - 1;
  double x1 = solve(a, b, c, x0, 0.01, 10000);
  x0 = -b / (2 * a) + 1;
  double x2 = solve(a, b, c, x0, 0.01, 10000);
  return 0;
}
