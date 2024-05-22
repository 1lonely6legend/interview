//
// Created by ogier on 24-5-16.
//
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 30; // 最大网络节点数量
int n; // 网络节点数量
int a[N][N]; // 网络节点之间的访问权限矩阵
bool st[N]; // 访问状态数组，标记节点是否已经被访问


    // 深度优先搜索函数，用于计算从某个节点出发可以影响到的节点数量
int dfs(int id, int ra) {

  int num = 0; // 记录影响的节点数量

  // 遍历所有节点
  for (int i = 0; i < n; i++) {
    if (id == i || !a[id][i]) continue; // 跳过自身以及无法访问的节点
    if (ra >= a[id][i]) { // 如果权限等级足够访问该节点
      if (st[i]) continue; // 如果该节点已经访问过，跳过
      st[i] = true; // 标记该节点为已访问
      num += dfs(i, a[id][i]); // 递归访问该节点，并累加影响的节点数量
      st[i] = false; // 回溯，取消标记
    }
  }

  return num + 1; // 返回包括自身在内的影响节点数量
}

int main() {
  cin >> n; // 输入网络节点数量
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j]; // 输入网络节点之间的访问权限矩阵
    }
  }

  int x;
  int res = -1, ans = 0; // 初始化结果变量，res为最优下线节点，ans为最小影响节点数量
  while (cin >> x) { // 输入暴露在公网上的节点编号，直到输入结束
    for (int i = 0; i < n; i++) {
      if (x == i) continue; // 跳过自身
      st[x] = true; // 标记该节点为已访问
      int t = dfs(x, 10); // 从该节点出发，计算影响节点数量，初始权限等级为10（ROOT权限）
      st[x] = false; // 回溯，取消标记
      if (t > ans) { // 如果当前节点影响数量大于已知最小影响数量
        ans = t; // 更新最小影响数量
        res = x; // 更新最优下线节点
      }
    }
  }

  cout << res; // 输出最优下线节点编号
  return 0;
}
