//
// Created by ogier on 24-7-28.
//
//拉格朗日插值，拉格朗日多项式:L（x）穿过所有点。
//而每个基本多项式各穿过对应的一点，并在其它的三个点的x值上取零。
#include <bits/stdc++.h>
#include <iostream>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;
typedef struct point {
  double x, y;
  point(double x, double y) : x(x), y(y) {
  };
} POINT;
/**
 * @details 使用拉格朗日插值法计算插值函数值
 * @param points 插值节点的坐标(x_i,z_i)集合
 * @param x_predict 为需计算的插值函数值的横坐标
 * @return 插值函数值
 */
POINT Lagrange(std::vector<POINT> points, double x_predict) {
  double res = 0;
  int size = points.size(); //插值点个数
  for (int i = 0; i < size; i++) {
    //计算当前点的基本多项式
    double nume = 1; //分子
    double deno = 1; //分母
    for (int k = 0; k < size; k++) {
      //计算基本多项式的分子和分母
      if (k != i) {
        nume *= (x_predict - points[k].x);
        deno *= (points[i].x - points[k].x);
      }
    }
    res += nume / deno * points[i].y;
  }

  return {x_predict, res};
}

int main() {
  std::vector<POINT> points = {
    {1.1, 3.887}, {2.3, 4.276}, {3.9, 4.651}, {5.1, 2.117}
  };
  for (const auto [x,y] : points) {
    plt::plot({x}, {y}, "ro");
  }
  POINT p1 = Lagrange(points, 2.101);
  plt::plot({p1.x}, {p1.y}, "bo");
  cout << "2.101: " << p1.y << endl;
  POINT p2 = Lagrange(points, 4.234);
  plt::plot({p2.x}, {p2.y}, "bo");
  cout << "4.234: " << p2.y << endl;

  plt::show();
  return 0;
}
