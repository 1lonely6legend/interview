//
// Created by ogier on 24-7-28.
//
#include <iostream>
#include <cmath>
using namespace std;

#define DELTA 1e-4
#define EPS 1e-6
/*
 * 使用牛顿法求函数极值点 x * x - 4 * x;
 * 类似求方程的根，只不过这里是求函数的极值点，也就是导数的零点
 */
double func(const double x) {
  return x * x - 4 * x;
}

double func_prime(const double x) {
  return (func(x + DELTA) - func(x - DELTA)) / (2 * DELTA);
}
double func_prime2(const double x) {
  return (func_prime(x + DELTA) - func_prime(x - DELTA)) / (2 * DELTA);
}

double solve(const double x0, const size_t max_iter) {
  double x = x0, x_last = 0;
  size_t cnt = 0;
  while (cnt < max_iter) {
    cnt++;
    x_last = x;
    //在导数上使用牛顿迭代找零点
    x = x_last - func_prime(x_last) / func_prime2(x_last);
    if (fabs(x - x_last) < EPS) {
      cout << "cnt: " << cnt << " x=" << x << endl;
      return x;
    }
  }
  cout << "fail:max iter. x=" << x << endl;
  return x;
}

int main() {
  double res = solve(1, 100);
  return 0;
}
