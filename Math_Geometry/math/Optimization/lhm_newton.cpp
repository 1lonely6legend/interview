//
// Created by ogier on 24-4-27.
//
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
const double DELTA = 1e-4;
// 计算 f(x) = log10(x) + x^2
double f(double x) { return log10(x) + x * x; }

// 导数 df(x) = 1 / (x * log(10)) + 2 * x
double df(double x) { return 1 / (x * log(10.0)) + 2 * x; }

//使用导数定义求导数
double f_prime(double x) {
  //前向差分法，速度快，但是精度不高,误差是O(DELTA)
  //return (f(x+DELTA)-f(x))/DELTA;

  //中心差分法，速度慢，但也不是显著的负担，但是精度高，误差是O(DELTA^2)
  return (f(x+DELTA)-f(x-DELTA))/(2*DELTA);
}

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
  long double res = newton(tor, max_iter, initial);
  double test = 123.1231123;
  //这里是输出的格式控制，使用iomanip头文件
  //这里fixed是使用小数点后面的位数，setprecision是设置小数点后面的位数
  //如果不使用fixed，那么输出的是有效数字位数
  cout << setprecision(2) << test << endl;
  cout << fixed << setprecision(2) << test << endl;
  cout << "我求得的解为： "<<fixed << setprecision(2) << res << endl;
  return 0;
}
