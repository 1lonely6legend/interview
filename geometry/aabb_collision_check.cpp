//
// Created by ogier on 24-7-28.
//
#include <algorithm>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;
//AABB包围盒判断碰撞，AABB包围盒的特性时两个对称轴都是和xy轴平行的。
//对于OBB包围盒要判断角点在四条对称轴(分离轴)上是否重叠，而对于AABB被简化在xy轴上的投影是否重叠
using Point = pair<double, double>;
class Box {
  public:
    std::vector<Point> vertex;
    Box(const Point &p1,
        const Point &p2,
        const Point &p3,
        const Point &p4) {
      vertex = {p1, p2, p3, p4};
    }
    void add_point(const double x, const double y) {
      if (vertex.size() >= 4) {
        std::cerr << "vertex size is 4, can't add more point" << std::endl;
      }
      vertex.emplace_back(make_pair(x, y));
    }
    bool collision_check(const Box &other) {
      //定义自身包围盒和另一个包围盒的xy坐标的最大最小值，也就是AABB包围盒的上下左右边界
      const double min_x = min_element(vertex.begin(),
                                       vertex.end(),
                                       [](const Point &p1, const Point &p2) {
                                         return p1.first < p2.second;
                                       })->first;
      const double max_x = max_element(vertex.begin(),
                                       vertex.end(),
                                       [](const Point &p1, const Point &p2) {
                                         return p1.first < p2.second;
                                       })->first;
      const double min_y = min_element(vertex.begin(),
                                       vertex.end(),
                                       [](const Point &p1, const Point &p2) {
                                         return p1.second < p2.second;
                                       })->second;
      const double max_y = max_element(vertex.begin(),
                                       vertex.end(),
                                       [](const Point &p1, const Point &p2) {
                                         return p1.second < p2.second;
                                       })->second;
      const double min_x_other = min_element(other.vertex.begin(),
                                             other.vertex.end(),
                                             [](const Point &p1, const Point &p2) {
                                               return p1.first < p2.second;
                                             })->first;
      const double max_x_other = max_element(other.vertex.begin(),
                                             other.vertex.end(),
                                             [](const Point &p1, const Point &p2) {
                                               return p1.first < p2.second;
                                             })->first;
      const double min_y_other = min_element(other.vertex.begin(),
                                             other.vertex.end(),
                                             [](const Point &p1, const Point &p2) {
                                               return p1.second < p2.second;
                                             })->second;
      const double max_y_other = max_element(other.vertex.begin(),
                                             other.vertex.end(),
                                             [](const Point &p1, const Point &p2) {
                                               return p1.second < p2.second;
                                             })->second;

      //判断不重叠的条件，分开写，方便理解
      //判断x轴是否发生了重叠，如果自身的最大x值大于另一个包围盒的最小x值，且另一个包围盒的最大x值大于自身的最小x值，说明x轴发生了重叠
      const bool x_axel_overlap = max_x > min_x_other && max_x_other > min_x;
      //判断y轴是否发生了重叠，如果自身的最大y值大于另一个包围盒的最小y值，且另一个包围盒的最大y值大于自身的最小y值，说明y轴发生了重叠
      const bool y_axel_overlap = max_y > min_y_other && max_y_other > min_y;
      //只有当x轴和y轴都发生了重叠，才说明两个AABB包围盒发生了碰撞
      return x_axel_overlap && y_axel_overlap;
    }
};
int main() {
  //定义两个AABB包围盒
  Box box1(make_pair(0, 0), make_pair(1, 0), make_pair(1, 1), make_pair(0, 1));
  Box box2(make_pair(0.5, 0.5), make_pair(1.5, 0.5), make_pair(1.5, 1.5), make_pair(0.5, 1.5));
  //可视化两个AABB包围盒
  plt::plot({0, 1, 1, 0, 0}, {0, 0, 1, 1, 0}, "r-");
  plt::plot({0.5, 1.5, 1.5, 0.5, 0.5}, {0.5, 0.5, 1.5, 1.5, 0.5}, "b-");
  plt::show();
  //判断两个AABB包围盒是否发生碰撞
  cout << "collision check result: " << string("") + (box1.collision_check(box2) ? "collision" : "no collision") << endl;
  return 0;
}
