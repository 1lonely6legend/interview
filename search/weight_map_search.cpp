#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <functional>

using namespace std;

class DirectedGraph {
  private:
    vector<vector<pair<int, int> > > adjList; // 邻接表，存储图的边和权重

  public:
    DirectedGraph(int n) : adjList(n + 1) {
    }

    void addEdge(int from, int to, int weight) {
      adjList[from].push_back({to, weight});
    }

    // 生成所有路径及其代价的函数
    vector<pair<vector<int>, int> > generateAllPaths(int start, int end) {
      vector<pair<vector<int>, int> > allPaths; // 存储所有路径及其代价
      vector<int> path;
      int cost = 0;
      dfs(start, end, path, cost, allPaths);
      sort(allPaths.begin(),
           allPaths.end(),
           [](const pair<vector<int>, int> &a, const pair<vector<int>, int> &b) {
             return a.second < b.second; // 按代价从小到大排序
           });
      return allPaths;
    }

    void dfs(int current, int end, vector<int> &path, int cost, vector<pair<vector<int>, int> > &allPaths) {
      path.push_back(current);

      if (current == end) {
        allPaths.push_back({path, cost}); // 找到一条路径，添加到结果中
      } else {
        for (const auto &edge : adjList[current]) {
          int nextNode = edge.first;
          int nextCost = edge.second;
          dfs(nextNode, end, path, cost + nextCost, allPaths);
        }
      }

      path.pop_back(); // 回溯
    }
};

int main() {
  DirectedGraph graph(6); // 创建图实例，假设有6个节点

  // 添加边和权重
  graph.addEdge(1, 2, 3);
  graph.addEdge(1, 3, 2);
  graph.addEdge(1, 4, 1);
  graph.addEdge(2, 5, 2);
  graph.addEdge(3, 6, 1);
  graph.addEdge(4, 6, 4);
  graph.addEdge(4, 5, 3);
  graph.addEdge(6, 5, 3);

  // 生成从节点1到节点5的所有路径及其代价
  vector<pair<vector<int>, int> > allPaths = graph.generateAllPaths(1, 5);

  // 打印所有路径及其代价
  for (const auto &pair : allPaths) {
    for (int node : pair.first) {
      cout << node << " ";
    }
    cout << "Cost: " << pair.second << endl;
  }

  return 0;
}
