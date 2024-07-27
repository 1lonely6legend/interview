//
// Created by ogier on 24-7-28.
//
#include <bits/stdc++.h>
using namespace std;
/*
 * 使用梯度下降法求解函数极值
 */
constexpr double DELTA = 1e-5;
constexpr double EPS = 1e-6;

double func(const double x) {
  return x * x - 4 * x;
}

double func_prime(const double x) {
  return (func(x + DELTA) - func(x - DELTA)) / (2 * DELTA);
}

double GradientDescent(const double x0, const double learning_rate, const size_t max_iter) {
  double x = x0, x_last = 0;
  size_t cnt = 0;
  while (cnt < max_iter) {
    cnt++;
    x_last = x;
    x = x_last - learning_rate * func_prime(x_last);
    if (fabs(x - x_last) < EPS) {
      cout << "cnt: " << cnt << " x=" << x << endl;
      return x;
    }
  }
  cout << "fail: max iter. x=" << x << endl;
  return x;
}
int main() {
  double x1 = GradientDescent(0, 0.01, 10000);
  cout << x1 << endl;
}
