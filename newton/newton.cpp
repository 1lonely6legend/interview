//
// Created by ogier on 24-4-27.
//
#include <cmath>
#include <iostream>
#include <cmath>
#include <iostream>
using namespace std;

// 计算 f(x) = log10(x) + x^2
double f(double x) { return log10(x) + x * x; }

// 导数 df(x) = 1 / (x * log(10)) + 2 * x
double df(double x) { return 1 / (x * log(10.0)) + 2 * x; }

// 牛顿法求解
double newton(const double tor, const int max_iter, double initial) {
  double x = initial;
  int iter = 0;
  while (fabs(f(x)) > tor) {
    double dfx = df(x);
    if (fabs(dfx) < 1e-6) {
      // 防止除以一个非常小的数
      cout << "Derivative too small." << endl;
      break;
    }
    x = x - f(x) / dfx;
    iter++;
    if (iter > max_iter) {
      cout << "Exceeded maximum iterations." << endl;
      break;
    }
  }
  return x;
}

int main() {
  double tor = 1e-5;
  int max_iter = 100;
  double initial = 1.0; // 选择一个合适的初始值
  double res = newton(tor, max_iter, initial);
  cout << "Root found at x = " << res << endl;
  return 0;
}
