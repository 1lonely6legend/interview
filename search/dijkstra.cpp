//
// Created by ogier on 24-4-24.
//
#include <bits/stdc++.h>
using namespace std;

class Node {
 public:
  Node(int x, int y, int index, int cost, Node* pre)
      : x(x), y(y), index(index), cost(cost), pre(pre){};
  int x, y, index, cost;
  Node* pre;
};
string get_path(Node* end) {
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
struct cmp {
  bool operator()(Node* const a, Node* const b) { return a->cost > b->cost; }
};
string dijkstra(const vector<vector<int>>& grid) {
  const int row = grid.size();
  const int col = grid[0].size();
  unordered_map<int, int> cost_map;
  priority_queue<Node*, vector<Node*>, cmp> pq;
  int moves[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

  Node* start = new Node(0, 0, 0, 0, nullptr);
  pq.push(start);
  cost_map[0] = 0;

  while (!pq.empty()) {
    Node* cur = pq.top();
    pq.pop();
    if (cur->x == row - 1 && cur->y == col - 1) {
      return get_path(cur);
    }
    if (cost_map[cur->index] < cur->cost) {
      //如果遇到这个点之前已经被访问过了，并且更新了更小的cost，但是没有更新压入pq中的cost
      //这里需要判断，如果之前的cost比当前的cost小，就不需要再次访问这个点
      continue;
    }
    for (auto move : moves) {
      int next_x = cur->x + move[0];
      int next_y = cur->y + move[1];
      if (next_x >= 0 && next_y >= 0 && next_x < row && next_y < col) {
        int index = next_x * col + next_y;
        int cost = cur->cost + grid[next_x][next_y];
        if (cost_map.find(index) == cost_map.end() || cost_map[index] > cost) {
          Node* next = new Node(next_x, next_y, index, cost, cur);
          pq.push(next);
          cost_map[index] = cost;
        }
      }
    }
  }
  return "tmd not find";
}

int main() {
  vector<vector<int>> grid = {
      {1, 9, 1, 9, 1}, {1, 5, 1, 1, 1}, {1, 2, 2, 2, 4}, {1, 2, 3, 4, 5}};

  cout << "path:" << dijkstra(grid) << endl;
  return 0;
}
