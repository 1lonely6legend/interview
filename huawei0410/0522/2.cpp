//
// Created by ogier on 24-5-22.
//
/*
 2、矿车运输成本
露天矿采矿作业的特点是规模大，矿石和废料的移动量达到百万吨，运输成本开销较大，需要寻求一种最优的运输路径节省成本。
已知矿场可以划分成N*M的网格图，每个网格存在地形的差异，因此通过不同网格时，成本开销存在差异。
int mai5
网格有以下5种类型:

1、标志为'S'的网格为运输起点;
2、标志为'E'的网格时运输终点
3、标志为B 的网格为阻塞点，不允许通行
4、标志为C的网格为检查点，矿车在运输路径中，至少需要进入一次检查点。
5、标志为数字"的网格，其数字表示经过该网格的成本开销。
运输矿车只能上下左右4个方向运行，不允许斜对角进入其他网格。必要时可重复进入网格。
请根据输入的网格图，寻求一条从S网格到E网格，并且至少经过一次检查点的最低成本运输路径，并输出其成本开销。
*/
#include <bits/stdc++.h>
using namespace std;
struct Node {
  int x, y, cost, passedCheckPoint;
  bool operator>(const Node &other) const {
    return cost > other.cost;
  }
};
int moves[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool isNumber(const string &s) {
  bool res = true;
  for (char c : s) {
    if (!isdigit(c)) {
      res = false;
      break;
    }
  }
  return res;
}
struct cmp {
  bool operator()(const Node &a, const Node &b) {
    return a.cost > b.cost;
  }
};
int minCostPath(vector<vector<string> > &grid) {
  int m = grid.size(), n = grid[0].size();
  //使用一个三维数组来记录到达每个点的最小代价，dis[i][j][0] 表示从起点到网格 (i, j) 且没有经过检查点的最小路径成本。
  // dis[i][j][0] 表示从起点到网格 (i, j) 且没有经过检查点的最小路径成本。
  // dis[i][j][1] 表示从起点到网格 (i, j) 且已经经过至少一个检查点的最小路径成本。
  vector<vector<vector<int> > > dis(m, vector<vector<int> >(n, vector<int>(2, INT_MAX)));
  priority_queue<Node, vector<Node>, cmp> pq; //使用优先队列来进行dijkstra
  int startx = -1, starty = -1, endx = -1, endy = -1;
  bool hasCheckPoint = false;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == "S") {
        startx = i;
        starty = j;
      } else if (grid[i][j] == "E") {
        endx = i;
        endy = j;
      } else if (grid[i][j] == "C") {
        hasCheckPoint = true;
      }
    }
  }
  if (startx == -1 || starty == -1 || endx == -1 || endy == -1 || !hasCheckPoint) {
    return -1;
  } //判断是否找到了起点终点和检查点
  //将起始点加入优先队列
  pq.push({startx, starty, 0, 0});
  //起点没有经过检查点代价设置为0
  dis[startx][starty][0] = 0;
  while (!pq.empty()) {
    //遍历优先队列
    //取出当前代价最小的点
    Node cur = pq.top();
    pq.pop();
    //如果当前点是终点并且经过了检查点，返回当前代价
    if (cur.x == endx && cur.y == endy && cur.passedCheckPoint) {
      return cur.cost;
    }
    for (auto dir : moves) {
      //按照四个方向进行遍历
      int nx = cur.x + dir[0];
      int ny = cur.y + dir[1];
      if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != "B") {
        //位置合法并且不是障碍物
        //计算新的代价如果是数字的话加上数字
        int newCost = cur.cost + (isNumber(grid[nx][ny]) ? stoi(grid[nx][ny]) : 0);
        //check_point代表是否经过了检查点，判断历史是否经过检查点，以及当前点是否是检查点
        int check_point = cur.passedCheckPoint || (grid[nx][ny] == "C");
        if (newCost < dis[nx][ny][check_point]) {
          //如果新的代价小于之前的代价，更新代价并将新的点加入优先队列
          dis[nx][ny][check_point] = newCost;
          pq.push({nx, ny, newCost, check_point});
        }
      }
    }
  }
  return -1;
}
int main() {
  int m, n;
  cin >> m >> n;
  vector<vector<string> > grid(m, vector<string>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> grid[i][j];
    }
  }
  int result = minCostPath(grid);
  if (result == -1) {
    cout << -1 << endl;
  } else {
    cout << result << endl;
  }
  return 0;
}
