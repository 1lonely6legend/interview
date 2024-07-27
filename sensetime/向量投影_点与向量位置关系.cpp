//
// Created by ogier on 24-4-25.
// 使用点乘和叉乘计算向量的投影以及位置关系
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
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
// 点乘，物理意义是向量a在向量b上的投影长度乘以向量b的模长
float dot_product(my_vector& a, my_vector& b) {
  return a.x * b.x + a.y * b.y;
}
// 叉乘，物理意义是向量a和向量b构成的平行四边形的面积，正负代表方向
float cross_product(my_vector& a, my_vector& b) {
  return a.x * b.y - a.y * b.x;
}

my_vector vector_projection(my_vector& a, my_vector& b) {
  // 计算向量b在向量a上的投影
  float a_length = a.get_length();
  float dot = dot_product(a, b);
  float a_length_square = dot_product(a, a);
  float scale = dot / a_length_square;
  my_vector res = {a.x * scale, a.y * scale};
  return res;
}

std::string vector_relation(my_vector& a, my_vector& b) {
  // 判断向量a和向量b的关系
  float cross = cross_product(a, b);
  if (cross == 0) {
    return "平行";
  } else if (cross > 0) {
    return "向量a在向量b的顺时针方向";
  } else {
    return "向量a在向量b的逆时针方向";
  }
}
int main() {
  my_vector a{1, 0};
  my_vector b{1, 1};
  auto res1 = vector_projection(a,b);
  auto res2 = vector_relation(a,b);
  std::cout << res2;
  return 0;
}
