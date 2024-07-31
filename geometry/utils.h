//
// Created by ogier on 24-7-31.
//

#ifndef UTILS_H
#define UTILS_H
#include <cmath>
typedef struct point {
  double x, y;
  point(const double x, const double y): x(x), y(y) {
  };
} Point;
typedef class vec {
  public:
    double x, y;
    vec(const double x, const double y): x(x), y(y) {
    };
    vec(const vec &v) {
      x = v.x;
      y = v.y;
    };
    vec operator+(const vec &other) {
      return vec(x + other.x, y + other.y);
    };
    vec operator-(const vec &other) {
      return vec(x - other.x, y - other.y);
    };
    vec operator*(const double &k) {
      return vec(x * k, y * k);
    };
    double dot_product(const vec &other) {
      return x * other.x + y * other.y;
    };
    double cross_product(const vec &other) {
      return x * other.y - y * other.x;
    };
    double norm() {
      return sqrt(x * x + y * y);
    };
    void normalize() {
      double length = sqrt(x * x + y * y);
      x /= length;
      y /= length;
    };
} Vector;
#endif //UTILS_H
