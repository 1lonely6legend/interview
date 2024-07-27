//
// Created by ogier on 24-7-28.
//
#include <cmath>
#include <iostream>
using namespace std;

constexpr double DELTA = 1e-5;
constexpr double EPS = 1e-6;
/*
 * 使用牛顿迭代法求根号sqrt(c),转为求f(x) = x^2 - c的根
 */
double func(const double c, const double x) {
  return x * x - c;
}
double func_prime(const double c, const double x) {
  return (func(c, x + DELTA) - func(c, x - DELTA)) / (2 * DELTA);
}
/**
 * @detail 牛顿迭代法求方程根
 * @param c 对c求根，sqrt(c)
 * @param x0 给的迭代初始值
 * @param max_iter  最大迭代次数
 * @return sqrt(c)
 */
double solve(const double c, const double x0, const size_t max_iter) {
  double x = x0, x_last = 0;
  size_t cnt = 0;
  while (cnt < max_iter) {
    cnt++;
    x_last = x;
    x = x_last - func(c, x_last) / func_prime(c, x_last);
    if (fabs(x_last - x) < EPS) {
      cout << "cnt: " << cnt << " x=" << x << endl;
      return x;
    }
  }
  cout << "fail:max iter. x=" << x << endl;
  return x;
}
int main() {
  double res = solve(10, 1, 100);
  return 0;
}
