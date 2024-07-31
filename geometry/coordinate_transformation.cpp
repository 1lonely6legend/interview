//
// Created by ogier on 24-7-28.
//
// 给出两个点a和b，求出旋转矩阵
// 旋转矩阵: x1,y1 = cos(angle) * x0 - sin(angle) * y0, sin(angle) * x0 + cos(angle) * y0
#include <cmath>
#include <iostream>
#include <vector>
#include "utils.h"
using namespace std;
/**
 * @details 计算两个向量之间的夹角，然后根据夹角计算旋转矩阵
 * @param a 起始点
 * @param b 旋转后的点
 * @return 旋转矩阵
 */
vector<vector<double> > rotate_matrix(Point a, Point b) {
  // 计算旋转前后两个点构成的向量的夹角
  float angle = atan2(b.y - a.y, b.x - a.x);
  // 计算旋转角度的cos和sin值
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);
  // 旋转矩阵，有[b.x, b.y]^T = rotate * [a.x, a.y]^T
  // 具体的，旋转之后的点的x坐标为cos(angle) * x0 - sin(angle) * y0
  // 旋转之后的点的y坐标为sin(angle) * x0 + cos(angle) * y0
  vector<vector<double> > rotate = {
    {cos_angle, -sin_angle},
    {sin_angle, cos_angle}
  };
  return rotate;
}
/**
 * @details 计算点p旋转之后的点
 * @param p 旋转前的点
 * @param rotate 旋转矩阵
 * @return 旋转之后的点
 */
Point rotate_point(Point p, vector<vector<double> > rotate) {
  Point p1;
  p1.x = rotate[0][0] * p.x + rotate[0][1] * p.y;
  p1.y = rotate[1][0] * p.x + rotate[1][1] * p.y;
  return p1;
}
int main() {
  //旋转前后的位置点
  Point a = {1, 3};
  Point b = {2, 5};
  //根据两个点求出旋转矩阵
  vector<vector<double> > rotate = rotate_matrix(a, b);
  for (const auto &data : rotate) {
    for (const double d : data) {
      cout << d << " ";
    }
    cout << endl;
  }
  //计算点p3旋转之后的点p4
  Point p3 = {1, 1};
  Point p4;
  p4 = rotate_point(p3, rotate);
  cout << "p4.x = " << p4.x << ", p4.y = " << p4.y << endl;
  return 0;
}
