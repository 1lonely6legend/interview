//
// Created by ogier on 24-4-25.
//
#include <iostream>
#include <vector>
#include <cmath>
struct Point {
  float x;
  float y;
};
class BBox {
  public:
    void func(Point &a, Point &b) {
      float v1[2] = {a.x, a.y};
      float v2[2] = {b.x, b.y};
      float ans1 = atan2(v1[0], v1[1]);
      float ans2 = atan2(v2[0], v2[1]);
      float ans = fabs(ans1 - ans2);
      if (ans > 3.14) ans = 6.28 - ans;
    }
    BBox() = default;
    virtual ~BBox() = default;
    void addPoint(float x, float y) {
      Point temp;
      temp.x = x;
      temp.y = y;
      point_array.emplace_back(temp);
    }
    bool isCollision(BBox other) {
      int max_x_1 = INT_MIN;
      int min_x_1 = INT_MAX;
      int max_y_1 = INT_MIN;
      int min_y_1 = INT_MAX;
      for (auto elem : point_array) {
        if (elem.x < min_x_1) min_x_1 = elem.x;
        if (elem.y < min_y_1) min_y_1 = elem.y;
        if (elem.x > max_x_1) max_x_1 = elem.x;
        if (elem.y > max_y_1) max_y_1 = elem.y;
      }
      int max_x_2 = INT_MIN;
      int min_x_2 = INT_MAX;
      int max_y_2 = INT_MIN;
      int min_y_2 = INT_MAX;
      for (auto elem : other.point_array) {
        if (elem.x < min_x_2) min_x_2 = elem.x;
        if (elem.y < min_y_2) min_y_2 = elem.y;
        if (elem.x > max_x_2) max_x_2 = elem.x;
        if (elem.y > max_y_2) max_y_2 = elem.y;
      }
      bool x_collision = false;
      if (min_x_1 < min_x_2) {
        if (min_x_2 <= max_x_1 && max_x_2 >= max_x_1)
          x_collision = true;
      } else {
        if (min_x_1 >= min_x_2 && max_x_1 >= max_x_1)
          x_collision = true;
      }
      bool y_collision = false;
      if (min_y_1 < min_y_2) {
        if (min_y_2 <= max_y_1 && max_y_2 >= max_y_1)
          y_collision = true;
      } else {
        if (min_y_1 >= min_y_2 && max_y_1 >= max_y_1)
          y_collision = true;
      }
      return x_collision && y_collision;
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
