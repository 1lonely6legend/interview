//
// Created by ogier on 24-7-28.
//
#include <cmath>
#include <iostream>
using namespace std;

constexpr double DELTA = 1e-4;
constexpr double EPS = 1e-6;
/*
 * 使用牛顿迭代法求解方程的根：log(x)+x^2=0
 * cmath中，log() = ln, log10() = log_10
 */
double func(const double x) {
  return log10(x) + x * x;
}
double func_prime(const double x) {
  return (func(x + DELTA) - func(x - DELTA)) / (2 * DELTA);
}
double solver(const double x0, const size_t max_iter) {
  double x = x0, x_last = 0;
  size_t cnt = 0;
  while (cnt < max_iter) {
    cnt++;
    x_last = x;
    x = x_last - func(x_last) / func_prime(x_last);
    if (fabs(x_last - x) < EPS) {
      cout << "cnt: " << cnt << " x=" << x << endl;
      return x;
    }
  }
  cout << "fail:max iter. x=" << x << endl;
  return x;
}
int main() {
  double res = solver(1, 100);
  return 0;
}
