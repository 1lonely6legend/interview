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
class Node {
  public:
    Node(int x, int y, int index, int cost, int f, Node *pre)
      : x(x), y(y), index(index), cost(cost), f(f), pre(pre) {
    };
    //明确，a*相比较于dijkstra，在pq中需要比较的是f值，也就是cost+H值
    int x, y, index, cost, f;
    Node *pre;
};
struct cmp {
  bool operator()(Node *const a, Node *const b) { return a->f > b->f; }
};
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

string a_star(const vector<vector<int> > &grid, const Point &start_point, const Point &end_point) {
  const size_t row = grid.size();
  const size_t col = grid[0].size();
  //使用匿名函数,输入当前位置，计算与目标点启发式距离，这里使用曼哈顿距离
  auto H = [&](size_t x, size_t y) {
    return (x >= end_point.x)
             ? (x - end_point.x)
             : (end_point.x - x)
               + (y >= end_point.y)
                 ? (y - end_point.y)
                 : (end_point.y - y);
  };
  //之前的使用二维数组存放cost的方法，也可以，但我还是更喜欢用index+hash
  //  vector<vector<int> > cost_map(row, vector<int>(col, INT_MAX));
  unordered_map<int, int> cost_map;
  priority_queue<Node *, vector<Node *>, cmp> pq;
  int moves[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

  Node *start = new Node(0, 0, 0, 0, 0 + H(0, 0), nullptr);
  pq.push(start);
  cost_map[0] = 0;

  while (!pq.empty()) {
    Node *cur = pq.top();
    pq.pop();
    if (cur->x == end_point.x && cur->y == end_point.y) {
      return get_path(cur);
    }
    //如果当前要处理的节点，已经有更小的cost了，那么就不用再处理了
    if (cost_map[cur->index] < cur->cost) {
      continue;
    }
    for (const auto &[dx,dy] : moves) {
      int next_x = cur->x + dx;
      int next_y = cur->y + dy;
      if (next_x >= 0 && next_y >= 0 && next_x < row && next_y < col) {
        int index = next_x * col + next_y;
        int next_cost = cur->cost + grid[next_x][next_y];
        //这里是a*的关键，f = g + h
        int f = next_cost + H(next_x, next_y);
        //如果这个点没有被访问过，或者被访问过，但是这次的代价更小，那么就更新这个点的代价，并且加入pq
        if (cost_map.find(index) == cost_map.end() || cost_map[index] > next_cost) {
          pq.push(new Node(next_x, next_y, index, next_cost, f, cur));
          cost_map[index] = next_cost;
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

  cout << "path:" << a_star(grid, {0, 0}, {grid.size() - 1, grid[0].size() - 1}) << endl;
  return 0;
}
