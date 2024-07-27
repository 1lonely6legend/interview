//
// Created by ogier on 24-4-24.
//
#include <bits/stdc++.h>
using namespace std;
struct Point {
  size_t x, y;
  Point(size_t x, size_t y): x(x), y(y) {
  };
};
//定义节点类
class Node {
  public:
    Node(int x, int y, int index, int cost, Node *pre)
      : x(x), y(y), index(index), cost(cost), pre(pre) {
    };
    int x, y, index, cost;
    Node *pre;
};
//提供给pq的比较函数
struct cmp {
  //注意，搞清楚这部分的逻辑，这里要使用的是小顶堆
  bool operator()(Node *const a, Node *const b) { return a->cost > b->cost; }
};
//找到终点之后，根据pre指针，逆序找到路径，并打印
string get_path(Node *end) {
  string res;
  while (end != nullptr) {
    int x = end->x;
    int y = end->y;
    string temp = "]" + to_string(y + 1) + "," + to_string(x + 1) + "[";
    res += temp;
    end = end->pre;
  }
  reverse(res.begin(), res.end());
  return res;
};

string dijkstra(const vector<vector<int> > &grid,
                const Point &start_point,
                const Point &end_point) {
  const size_t row = grid.size();
  const size_t col = grid[0].size();
  //使用一个哈希表，记录当前遍历过程中，遇到的点的**最小**代价，相当于也记录了哪些点没有被访问过
  unordered_map<int, int> cost_map;
  //使用pq来进行优先级队列的操作，每次取出代价最小的点来进行查找
  priority_queue<Node *, vector<Node *>, cmp> pq;
  int moves[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

  Node *start = new Node(start_point.x, start_point.y, 0, 0, nullptr);
  pq.push(start);
  cost_map[0] = 0;

  while (!pq.empty()) {
    Node *cur = pq.top();
    pq.pop();
    if (cur->x == end_point.x && cur->y == end_point.y) {
      return get_path(cur);
    }
    if (cost_map[cur->index] < cur->cost) {
      //代表这个点之前已被访问，并且之前访问此位置的代价更小，但是这次弹出的pq中的cost是代价更大的一个路径，因此不对这个点进行处理
      continue;
    }
    for (const auto &[dx,dy] : moves) {
      int next_x = cur->x + dx;
      int next_y = cur->y + dy;
      if (next_x >= 0 && next_y >= 0 && next_x < row && next_y < col) {
        int index = next_x * col + next_y;
        int cost = cur->cost + grid[next_x][next_y];
        // 下面两种情况需要更新代价，并压入pq。 1.如果当前发现了还没有被访问过的点，直接加入pq  2.或者如果发现了比之前代价更小的路径
        // 注意要先判断是否存在，然后再判断代价，防止越界
        if (cost_map.find(index) == cost_map.end() || cost_map[index] > cost) {
          pq.push(new Node(next_x, next_y, index, cost, cur));
          cost_map[index] = cost;
        }
      }
    }
  }
  return "path not found";
}

int main() {
  vector<vector<int> > grid = {
    {1, 9, 1, 9, 1},
    {1, 5, 1, 1, 1},
    {1, 2, 2, 2, 4},
    {1, 2, 3, 4, 5}
  };

  cout << "path:" << dijkstra(grid, {0, 0}, {grid.size() - 1, grid[0].size() - 1}) << endl;
  return 0;
}
