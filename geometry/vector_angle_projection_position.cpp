//
// Created by ogier on 24-7-28.
//
#include <iostream>
#include <cmath>
#include "utils.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;
int main() {
  //1.计算向量投影，2.判断点与向量的位置关系，3.计算向量夹角
  Vector v1{0, 1}, v2{1, 1};
  Point p1{-1, 1};
  //可视化向量v1,v2 以及点p1
  plt::plot({0, v1.x}, {0, v1.y}, "r-");
  plt::plot({0, v2.x}, {0, v2.y}, "b-");
  plt::plot({p1.x}, {p1.y}, "go");
  plt::show();
  //1. 计算向量v1在向量v2上的投影v3
  double dot_res = v1.dot_product(v2); //计算点积，v1*v2=|v1|*|v2|*cos(θ)
  double v2_norm = v2.norm(); //计算向量v2的模长
  //|v1|* (|v2|*cos(θ)/|v2|^2) *v2 = |v1|*cos(θ)*v2/|v2| = v1在v2上的投影长度*v2单位向量
  Vector v3 = v2 * (dot_res / (v2_norm * v2_norm));
  cout << "v1 projection on v2: (" << v3.x << "," << v3.y << ")" << endl;

  //2. 判断点p1在向量v1的左边还是右边,使用叉乘，右手定则，a叉乘b,a向b攥拳，大拇指向下为负，向上为正
  double cross_res = v1.cross_product(Vector(p1.x, p1.y));
  if (cross_res > 0) {
    cout << "p1 is on the left of v1" << endl;
  } else if (cross_res < 0) {
    cout << "p1 is on the right of v1" << endl;
  } else {
    cout << "p1 is on the v1" << endl;
  }

  //3.计算向量夹角，要求角度在0-π之间，atan2()用法,注意y在前，x在后，一二象限返回弧度0 ~ π，四三象限返回弧度0 ~ -π
  double angle1 = atan2(v1.y, v1.x), angle2 = atan2(v2.y, v2.x);
  //要求角度在0-π之间，计算夹角时需要考虑正负号,s首先取绝对值，如果大于π，取2π减去这个值
  double angle = fabs(angle2 - angle1);
  if (angle > M_PI)
    angle = 2 * M_PI - angle;
  cout << "degree between v1 and v2: " << angle / M_PI * 180 << endl;
  return 0;
}
