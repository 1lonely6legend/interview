//
// Created by ogier on 24-7-28.
//
#include <bits/stdc++.h>
using namespace std;
/*
 * 使用梯度下降法求解多元函数极值：f(x)=4(x1-1)^2+(x2-2)^4
 */
constexpr double DELTA = 1e-5;
constexpr double EPS = 1e-6;

double func(const double x1, const double x2) {
  return 4 * pow(x1 - 1, 2) + pow(x2 - 2, 4);
}

vector<double> func_prime(const double x1, const double x2) {
  double nabla_x1 = (func(x1 + DELTA, x2) - func(x1 - DELTA, x2)) / (2 * DELTA);
  double nabla_x2 = (func(x1, x2 + DELTA) - func(x1, x2 - DELTA)) / (2 * DELTA);
  return {nabla_x1, nabla_x2};
}

vector<double> solve(const vector<double> &x0, const double learning_rate, const size_t max_iter) {
  vector<double> x = x0, x_last;
  size_t cnt = 0;
  while (cnt < max_iter) {
    cnt++;
    x_last = x;
    auto prime = func_prime(x_last[0], x_last[1]);
    x[0] = x_last[0] - learning_rate * prime[0];
    x[1] = x_last[1] - learning_rate * prime[1];
    if (fabs(x[0] - x_last[0]) < EPS && fabs(x[1] - x_last[1]) < EPS) {
      cout << "cnt: " << cnt << " x=" << x[0] << " y=" << x[1] << endl;
      return x;
    }
  }
  cout << "fail:max iter. x=" << x[0] << " y=" << x[1] << endl;
  return x;
}
int main() {
  //使用梯度下降法时，学习率需要正确选择。过大会导致收敛不稳定，过小则可能导致收敛过慢。
  //并且相比于牛顿迭代的二次收敛，梯度下降法迭代次数显著增加。
  vector<double> x = solve({0, 0}, 0.01, 100000);
  return 0;
}
