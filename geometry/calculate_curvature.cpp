//
// Created by ogier on 24-8-3.
// 计算离散点的path曲率
// 参考https://blog.csdn.net/beiyangxiaokai/article/details/135269999
// todo 说实话，这里没明白为什么这样计算曲率
#include <iostream>
#include <cmath>
#include "utils.h"
using namespace std;

double get_curvature(const Point &p1, const Point &p2, const Point &p3) {
  const auto &p1p2 = Vector(p2, p1);
  const auto &p2p3 = Vector(p3, p2);
  const auto &p1p3 = Vector(p3, p1);
  const auto cross_product = p1p2.cross_product(p2p3);
  return 2 * cross_product / (p1p2.norm() * p2p3.norm() * p1p3.norm());
}

int main() {
  Point p1{1.0, 1.0},p2 {2.0, 4.0},p3{3.0, 1.0};
  double curvature = get_curvature(p1, p2, p3);
  cout << curvature << endl;
  return 0;
}
