//
// Created by ogier on 24-5-16.
//
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 定义常量N表示最大图片数量
const int N = 900 + 7;
int a[N][N];// 用于存储相似度矩阵
int n;      // 图片数量
int p[N];   // 并查集数组，用于记录每个节点的父节点
int num[N]; // 用于记录每个相似类的相似度之和

// 并查集的查找操作，带路径压缩
int find(int x) {
  if (x != p[x])      // 如果x不是它自己的父节点
    p[x] = find(p[x]);// 递归查找x的祖先节点，并路径压缩
  return p[x];        // 返回x的祖先节点
}

int main() {
  cin >> n;// 输入图片数量
  for (int i = 0; i < n; i++) {
    p[i] = i;  // 初始化并查集，每个节点的父节点指向自己
    num[i] = 0;// 初始化每个相似类的相似度之和为0
  }
  // 输入相似度矩阵
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }
  // 处理相似度矩阵，构建相似类
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (a[i][j] > 0) {               // 如果i和j相似
        int px = find(i);              // 查找i的祖先节点
        int py = find(j);              // 查找j的祖先节点
        if (px != py) {                // 如果i和j不在同一个相似类中
          p[px] = py;                  // 合并i和j的相似类
          num[py] += a[i][j] + num[px];// 更新相似类的相似度之和
        } else {
          num[py] += a[i][j]; // 如果i和j已经在同一个相似类中，直接累加相似度
        }
      }
    }
  }
  // 将相似类的相似度之和存入结果向量
  vector<int> res;
  for (int i = 0; i < n; i++) {
    if (p[i] == i) { // 如果i是一个相似类的代表节点
      res.push_back(num[i]); // 将相似度之和加入结果向量
    }
  }
  // 按照相似度之和从大到小排序
  sort(res.begin(), res.end(), greater<int>());
  // 输出结果
  for (int i = 0; i < res.size(); i++) {
    if (i > 0)
      cout << " ";
    cout << res[i];
  }
  return 0;
}
