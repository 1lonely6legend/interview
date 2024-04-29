//
// Created by ogier on 24-4-29.
// https://blog.csdn.net/weixin_42301220/article/details/130877499?spm=1001.2014.3001.5502
// 给出两个点a和b，求出旋转矩阵
// 旋转矩阵: x1,y1 = cos(angle) * x0 - sin(angle) * y0, sin(angle) * x0 + cos(angle) * y0
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
struct Point {
  float x;
  float y;
};
vector<vector<double> > rotate_matrix(Point a, Point b) {
  // 计算两个向量之间的夹角
  float angle = atan2(b.y - a.y, b.x - a.x);
  // 旋转矩阵
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);
  //
  vector<vector<double> > rotate = {{cos_angle, -sin_angle}, {sin_angle, cos_angle}};
  return rotate;
}
int main() {
  Point a = {1, 3};
  Point b = {2, 5};

  vector<vector<double> > rotate = rotate_matrix(a, b);
  for(const auto &data: rotate) {
    for(const double d: data) {
      cout << d << " ";
    }
    cout << endl;
  }
  return 0;
}
