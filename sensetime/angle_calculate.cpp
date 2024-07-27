//
// Created by ogier on 24-4-25.
// 计算两个向量之间夹角，要求在0到180度之间
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
const float PI = 3.1415926;
class my_vector {
 public:
  my_vector(const float a, const float b) {
    x = a;
    y = b;
  };
  float get_length() { return sqrt(x * x + y * y); }
  float x;
  float y;
};

float calculate_angle(my_vector& a, my_vector& b) {
  float angle1 = atan2(a.x, a.y);
  float angle2 = atan2(b.x, b.y);
  float angle = fabs(angle1 - angle2);
  if (angle > PI)
    angle = 2 * PI - angle;
  return angle;
}
int main() {
  my_vector a{0, -1};
  my_vector b{-1, 1};
  auto res = calculate_angle(a, b);
  std::cout << res / PI * 180 << std::endl;
  return 0;
}
