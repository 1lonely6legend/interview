//
// Created by ogier on 24-4-24.
//
#include <bits/stdc++.h>
using namespace std;

class Node {
 public:
  Node(int x, int y, int index, int cost, int f, Node* pre)
      : x(x), y(y), index(index), cost(cost), f(f), pre(pre){};
  int x, y, index, cost, f;
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
  bool operator()(Node* const a, Node* const b) { return a->f > b->f; }
};
string a_star(const vector<vector<int>>& grid) {
  const int row = grid.size();
  const int col = grid[0].size();
  auto H = [row, col](int x, int y) {
    return row - x + col - y;
  };
  vector<vector<int>> cost_map(row, vector<int>(col, INT_MAX));
  priority_queue<Node*, vector<Node*>, cmp> pq;
  int moves[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

  Node* start = new Node(0, 0, 0, 0, H(0, 0), nullptr);
  pq.push(start);
  cost_map[0][0] = 0;

  while (!pq.empty()) {
    Node* cur = pq.top();
    pq.pop();
    if (cur->x == row - 1 && cur->y == col - 1) {
      return get_path(cur);
    }
    if (cost_map[cur->x][cur->y] < cur->cost) {
      // Avoid processing if a better path is found
      continue;
    }
    for (auto move : moves) {
      int next_x = cur->x + move[0];
      int next_y = cur->y + move[1];
      if (next_x >= 0 && next_y >= 0 && next_x < row && next_y < col) {
        int next_cost = cur->cost + grid[next_x][next_y];
        int f = next_cost + H(next_x, next_y);
        if (next_cost < cost_map[next_x][next_y]) {
          cost_map[next_x][next_y] = next_cost;
          pq.push(new Node(next_x, next_y, next_x * col + next_y, next_cost, f,
                           cur));
        }
      }
    }
  }
  return "Path not found";
}

int main() {
  vector<vector<int>> grid = {
      {1, 9, 1, 9, 1}, {1, 5, 1, 1, 1}, {1, 2, 2, 2, 4}, {1, 2, 3, 4, 5}};

  cout << "path:" << a_star(grid) << endl;
  return 0;
}
