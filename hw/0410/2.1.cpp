//
// Created by ogier on 24-5-16.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for std::iota

using namespace std;

// 并查集类，用于处理图片的归类
class UnionFind {
private:
    vector<int> parent, rank, size; // parent存储每个节点的父节点，rank用于优化合并，size用于记录每个集合的大小

public:
    // 构造函数，初始化并查集
    UnionFind(int n) : parent(n), rank(n, 0), size(n, 1) {
        iota(parent.begin(), parent.end(), 0); // 初始化每个节点的父节点为自己
    }

    // 查找操作，带路径压缩
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    // 合并操作，带按秩合并
    void unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                swap(root_x, root_y);
            }
            parent[root_y] = root_x;
            size[root_x] += size[root_y]; // 更新集合大小
            if (rank[root_x] == rank[root_y]) {
                rank[root_x]++;
            }
        }
    }
};

// 处理图片相似度，归类相似图片
void findSimPics(vector<vector<int>> &M) {
    int n = M.size(); // 矩阵的大小，即图片的数量
    UnionFind uf(n); // 并查集对象，用于归类图片
    vector<int> simSum(n, 0); // 用于存储每个集合的相似度之和

    // 合并相似的图片
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (M[i][j] > 0) {
                uf.unite(i, j);
            }
        }
    }

    // 计算每个集合的相似度之和
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (uf.find(i) == uf.find(j)) {
                simSum[uf.find(i)] += M[i][j];
            }
        }
    }

    // 移除相似度为0的集合，并按从大到小排序
    simSum.erase(remove(simSum.begin(), simSum.end(), 0), simSum.end());
    sort(simSum.rbegin(), simSum.rend());

    // 输出结果
    for (int i = 0; i < simSum.size(); ++i) {
        cout << simSum[i] / 2 << " "; // 每个相似度在矩阵中被计算了两次，所以要除以2
    }
    cout << endl;

    return;
}

int main() {
    int N; // 矩阵的大小，即图片的数量
    cin >> N;
    vector<vector<int>> Mat(N, vector<int>(N, 0)); // 存储相似度的矩阵

    // 读取输入数据
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> Mat[i][j];
        }
    }

    // 处理相似图片并输出结果
    findSimPics(Mat);
    return 0;
}
