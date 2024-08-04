//
// Created by ogier on 24-7-28.
//
#include <iostream>
#include <cmath>
#include "utils.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;

Vector vectorProject(Vector &v1, Vector &v2) {
  double dot_res = v1.dot_product(v2); //计算点积，v1*v2=|v1|*|v2|*cos(θ)
  double v2_norm = v2.norm(); //计算向量v2的模长
  //|v1|* (|v2|*cos(θ)/|v2|^2) *v2 = |v1|*cos(θ)*v2/|v2| = v1在v2上的投影长度*v2单位向量
  return v2 * (dot_res / (v2_norm * v2_norm));
}

void vec_position_judge(const Vector &v1, const Vector &v2) {
  //2. 判断点p1在向量v1的左边还是右边,使用叉乘，右手定则，a叉乘b,a向b攥拳，大拇指向下为负，向上为正
  double cross_res = v1.cross_product(v2);
  if (cross_res > 0) {
    cout << "v1 is on the right of v2" << endl;
  } else if (cross_res < 0) {
    cout << "v1 is on the left of v2" << endl;
  } else {
    cout << "v1 is on the v2" << endl;
  }
}

double angleBetweenVectors(const Vector &v1, const Vector &v2) {
  //3.计算向量夹角，要求角度在0-π之间，atan2()用法,注意y在前，x在后，一二象限返回弧度0 ~ π，四三象限返回弧度0 ~ -π
  double angle1 = atan2(v1.y, v1.x);
  double angle2 = atan2(v2.y, v2.x);
  double res = fabs(angle1 - angle2);
  if (res > M_PI)
    return 2 * M_PI - res;
  return res;
}

double disBetweenPointVector(const Vector &v, const Point &p) {
  //4.计算点到直线的距离,二维点乘代表两个向量构成的平行四边形的面积，除以向量的模长，得到高即是点到直线的距离
  //注意考虑点乘可能会有正负号，所以取绝对值
  Vector vp{p.x, p.y};
  return fabs(vp.cross_product(v)) / v.norm();
}

Point IntersectionPoint(const LineSeg &l1, const LineSeg &l2) {
  //5.计算两条线段的交点
  //设l1的起点为p1，终点为p2，l2的起点为p3，终点为p4，l1的方程为p1 + t1*(p2-p1),l2的方程为p3 + t2*(p4-p3)，也就是起点+ t*向量
  //联立方程，得到t1和t2，然后代入l1的方程，得到交点
  Vector v1{l1.pstart, l1.pend}, v2{l2.pstart, l2.pend};
  Vector v3{l1.pstart, l2.pstart};
  //t1 = (v3 x v2) / (v1 x v2),求出t1，带入l1的方程即可得到交点
  double t1 = v3.cross_product(v2) / v1.cross_product(v2);
  //判断点是否在线段上，只需要判断t1和t2是否在0-1之间即可
  double t2 = v3.cross_product(v1) / v1.cross_product(v2);
  if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1) {
    cout << "no intersection point" << endl;
    return Point{0, 0};
  }
  return Point{l1.pstart.x + t1 * v1.x, l1.pstart.y + t1 * v1.y};
}

int main() {
  Vector v1{0, 1}, v2{1, 1};
  Point p1{-1, 1}, p2{-1, 0}, p3{-1, -1};
  LineSeg l1({0, 1}, {1, 0}), l2({0, 0}, {1, 1});
  //可视化向量v1,v2 以及点p1
  plt::plot({0, v1.x}, {0, v1.y}, "r-");
  plt::plot({0, v2.x}, {0, v2.y}, "b-");
  plt::plot({p1.x}, {p1.y}, "go");
  plt::axis("equal");

  //计算向量v1在向量v2上的投影向量
  cout << vectorProject(v1, v2);
  //判断向量v1在向量v2的左边还是右边
  vec_position_judge(v1, v2);
  //计算两个向量v1,v2之间的夹角，返回的角度在0-π之间
  cout << "degree between v1 and v2: " << angleBetweenVectors(v1, v2) / M_PI * 180 << endl;
  //计算点p1到向量v1的距离
  cout << "distance between p1 and v1: " << disBetweenPointVector(v1, p1) << endl;
  //计算两条线段l1,l2的交点
  Point res = IntersectionPoint(l1, l2);
  plt::show();
  return 0;
}
