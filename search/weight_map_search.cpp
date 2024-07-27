#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class DirectedGraph {
  private:
    // 定义邻接矩阵，存储图的边和权重，adjList[i][j]代表从节点i到节点j的权重，如果为INT_MAX表示没有边
    vector<vector<int> > adjList;

  public:
    DirectedGraph(int n) : adjList(n + 1, vector<int>(n + 1, INT_MAX)) {
    }

    void addEdge(int from, int to, int weight) {
      adjList[from][to] = weight;
    }

    // 生成所有路径及其代价的函数,返回的结构为vector<pair<vector<int>, int> >
    // 一组路径及其代价:pair<vector<int>, int>，其中vector<int>存储路径，int存储代价
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

    void dfs(const int current,
             const int end,
             vector<int> &path,
             int cost,
             //注意这里代价不要传引用，防止回溯时修改了代价
             vector<pair<vector<int>, int> > &allPaths) {
      path.push_back(current);
      if (current == end) {
        //找到一条路径，添加到结果中
        allPaths.push_back({path, cost}); // 找到一条路径，添加到结果中
      } else {
        //继续深度优先搜索,遍历当前点的所有邻接点，注意从1开始，0是无效点
        for (int nextNode = 1; nextNode < adjList[current].size(); nextNode++) {
          if (adjList[current][nextNode] != INT_MAX) {
            //注意这里要判断是否有边，INT_MAX表示没有边
            int nextCost = adjList[current][nextNode];
            //递归搜索下一个节点
            dfs(nextNode, end, path, cost + nextCost, allPaths);
          }
        }
      }
      //需要弹出记录遍历的节点，进行回溯
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
  auto allPaths = graph.generateAllPaths(1, 5);

  // 打印所有路径及其代价
  for (const auto &[path,cost] : allPaths) {
    for (int node : path) {
      cout << node << " ";
    }
    cout << "Cost: " << cost << endl;
  }

  return 0;
}
