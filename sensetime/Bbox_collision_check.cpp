//
// Created by ogier on 24-4-25.
// 计算两个bbox是否发生碰撞，主要思想是判断两个bbox的最大最小值是否有重叠
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
struct Point {
  float x;
  float y;
};
class BBox {
 public:
  BBox() = default;
  virtual ~BBox() = default;
  void addPoint(float x, float y) { point_array.emplace_back(Point{x, y}); }
  bool isCollision(BBox other) {
    int min_x1 = std::min_element(
                     point_array.begin(), point_array.end(),
                     [](const Point& a, const Point& b) { return a.x < b.x; })
                     ->x;
    int max_x1 = std::max_element(
                     point_array.begin(), point_array.end(),
                     [](const Point& a, const Point& b) { return a.x < b.x; })
                     ->x;
    int min_y1 = std::min_element(
                     point_array.begin(), point_array.end(),
                     [](const Point& a, const Point& b) { return a.y < b.y; })
                     ->y;
    int max_y1 = std::max_element(
                     point_array.begin(), point_array.end(),
                     [](const Point& a, const Point& b) { return a.y < b.y; })
                     ->y;

    int min_x2 = std::min_element(
                     other.point_array.begin(), other.point_array.end(),
                     [](const Point& a, const Point& b) { return a.x < b.x; })
                     ->x;
    int max_x2 = std::max_element(
                     other.point_array.begin(), other.point_array.end(),
                     [](const Point& a, const Point& b) { return a.x < b.x; })
                     ->x;
    int min_y2 = std::min_element(
                     other.point_array.begin(), other.point_array.end(),
                     [](const Point& a, const Point& b) { return a.y < b.y; })
                     ->y;
    int max_y2 = std::max_element(
                     other.point_array.begin(), other.point_array.end(),
                     [](const Point& a, const Point& b) { return a.y < b.y; })
                     ->y;

    // 判断不重叠的条件
    bool left_of = max_x1 < min_x2;   // A 在 B 的左边
    bool right_of = min_x1 > max_x2;  // A 在 B 的右边
    bool below = max_y1 < min_y2;     // A 在 B 的下面
    bool above = min_y1 > max_y2;     // A 在 B 的上面

    // 如果 A 不在 B 的左边、右边、下面或上面，那么 A 和 B 相交
    bool no_overlap = left_of || right_of || below || above;
    return !no_overlap;  // 如果没有不重叠的情况，那么它们重叠
  }

  std::vector<Point> point_array;
};
int main() {
  BBox bbox_a, bbox_b;
  bbox_a.addPoint(1, 5);
  bbox_a.addPoint(4, 8);
  bbox_a.addPoint(6, 6);
  bbox_a.addPoint(3, 3);

  bbox_b.addPoint(123, 123);
  bbox_b.addPoint(124, 124);
  bbox_b.addPoint(125, 125);
  bbox_b.addPoint(126, 129);

  std::cout << "isCollision = " << bbox_a.isCollision(bbox_b);
  return 0;
}
