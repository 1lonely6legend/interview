//
// Created by ogier on 24-4-29.
//
#include <iostream>
#include <vector>

using namespace std;

class Matrix {
 private:
  std::vector<std::vector<int>> data;

 public:
  Matrix(int rows, int cols) : data(rows, std::vector<int>(cols, 0)) {}

  // 使用列表初始化器构造矩阵
  //  Matrix(std::initializer_list<std::initializer_list<int>> init) {
  //    for (auto &row : init) {
  //      data.push_back(std::vector<int>(row));
  //    }
  //  }
  Matrix(vector<vector<int>> init) {
    for (auto& row : init) {
      data.push_back(std::vector<int>(row));
    }
  }

  // 返回矩阵的行数
  size_t rows() const { return data.size(); }

  // 返回矩阵的列数
  size_t cols() const { return rows() ? data[0].size() : 0; }

  // 矩阵乘法，矩阵乘法需要三个for循环
  Matrix operator*(const Matrix& other) const {
    if (cols() != other.rows()) {
      throw std::invalid_argument(
          "Incompatible dimensions for matrix multiplication");
    }
    Matrix result(rows(), other.cols());
    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < other.cols(); ++j) {
        for (size_t k = 0; k < cols(); ++k) {
          result.data[i][j] += data[i][k] * other.data[k][j];
        }
      }
    }
    return result;
  }

  // 矩阵转置，矩阵转置只需要两个for循环
  Matrix transpose() const {
    Matrix result(cols(), rows());
    for (size_t i = 0; i < cols(); ++i) {
      for (size_t j = 0; j < rows(); ++j) {
        result.data[i][j] = data[j][i];
      }
    }
    return result;
  }

  // 重载 << 操作符以打印矩阵
  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (auto& row : matrix.data) {
      for (auto elem : row) {
        os << elem << " ";
      }
      os << std::endl;
    }
    return os;
  }

  // 提供外部访问data的方法
  std::vector<int>& operator[](size_t i) { return data[i]; }

  const std::vector<int>& operator[](size_t i) const { return data[i]; }
};

int main() {
  Matrix m1 = {{{1, 2}, {3, 4}}};
  Matrix m2 = {{{5, 6}, {7, 8}}};
  std::cout << "Matrix m1:" << std::endl << m1 << std::endl;
  std::cout << "Matrix m2:" << std::endl << m2 << std::endl;
  // 矩阵乘法
  Matrix m3 = m1 * m2;
  std::cout << "Matrix m1 * m2:" << std::endl << m3 << std::endl;
  // 矩阵转置
  Matrix m4 = m1.transpose();
  std::cout << "Transpose of m1:" << std::endl << m4 << std::endl;
  return 0;
}
