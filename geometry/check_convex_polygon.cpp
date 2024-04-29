//
// Created by ogier on 24-7-31.
// 判断多边形是否为凸多边形
#include <iostream>
#include <vector>
#include <string>
#include "utils.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;
/**
 * @details 判断多边形是否为凸多边形，同过点乘的方式判断，要求每个顶点的转向相同
 * @param vertex 多边形的顶点集合，其中的点的顺序是逆时针或者顺时针的，要连续
 * @return 是否为凸多边形
 */
bool isConvexPloygon(const vector<Point> &vertex) {
  int point_size = vertex.size();
  double cross_pre;
  for (int i = 0; i < point_size; ++i) {
    // 取出相邻的三个点，注意最后会出界，所以取余
    Point p1 = vertex[i], p2 = vertex[(i + 1) % point_size], p3 = vertex[(i + 2) % point_size];
    // 初始化三个点构成的多边形的相邻两条边
    Vector v1{p1, p2}, v2{p2, p3};
    // 计算叉乘，叉乘的结果大于0表示逆时针，小于0表示顺时针，如果有一个叉乘的正负和之前的不一样，说明不是凸多边形
    double cross_res = v1.cross_product(v2);
    if (i == 0) {
      // 初始化cross_pre,第一次不需要比较
      cross_pre = cross_res;
      continue;//跳过第一次比较
    }
    if (cross_res * cross_pre < 0)
      return false;
  }
  return true;
}
int main() {
  // 初始化一个凸六边形以及一个非凸的做例子
  vector<Point> vertex_convex = {
    {0, 0},
    {1, 0},
    {2, 1},
    {1, 2},
    {0, 2},
    {-1, 1}
  };
  vector<Point> vertex_no_convex = {
    {0, 0},
    {1, 0},
    {2, 1},
    {1, 2},
    {0, 2},
    {0.5, 1}
  };
  // 画出两个多边形
  plt::plot({0, 1, 2, 1, 0, -1, 0}, {0, 0, 1, 2, 2, 1, 0},"b-");
  plt::plot({0, 1, 2, 1, 0, 0.5, 0}, {0, 0, 1, 2, 2, 1, 0},"r-");
  plt::show();
  bool check1 = isConvexPloygon(vertex_convex);
  bool check2 = isConvexPloygon(vertex_no_convex);
  cout << "blue polygon is convex: " << string("") + (check1?"yes":"no") << endl;
  cout << "red polygon is convex: " << string("") + (check2?"yes":"no") << endl;
  return 0;
}
