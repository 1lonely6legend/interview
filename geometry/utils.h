//
// Created by ogier on 24-7-31.
//

#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <cmath>
struct Point {
  double x, y;
  Point() = default;
  Point(const double x, const double y): x(x), y(y) {
  };
};
class Vector {
  public:
    double x, y;
    Vector(const double x, const double y): x(x), y(y) {
    };
    Vector(const Vector &v) {
      x = v.x;
      y = v.y;
    };
    Vector(const Point &p1, const Point &p2) {
      x = p2.x - p1.x;
      y = p2.y - p1.y;
    }
    Vector operator+(const Vector &other) const {
      return Vector(x + other.x, y + other.y);
    };
    Vector operator-(const Vector &other) const {
      return Vector(x - other.x, y - other.y);
    };
    Vector operator*(const double &k) const {
      return Vector(x * k, y * k);
    };
    double dot_product(const Vector &other) const {
      return x * other.x + y * other.y;
    };
    double cross_product(const Vector &other) const {
      return x * other.y - y * other.x;
    };
    double norm() const {
      return sqrt(x * x + y * y);
    };
    void normalize() {
      double length = sqrt(x * x + y * y);
      x /= length;
      y /= length;
    };
    friend std::ostream &operator<<(std::ostream &os, const Vector &v) {
      os << "vecotr: " << '(' << v.x << ", " << v.y << ')' << std::endl;
      return os;
    }
};
#endif //UTILS_H
