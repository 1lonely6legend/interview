//
// Created by ogier on 24-5-16.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;// 输入计费日志的条数

  string a[5];// 用于存储分割后的日志字段

  map<pair<string, string>, int> h1;// 用于记录每个客户的每个计费因子的总计费时长
  set<string> ses;                  // 用于记录已处理的唯一日志（基于时间戳、客户标识和计费因子）

  // 读取计费日志
  while (n--) {
    string s, t;
    cin >> s;// 读取一行日志

    stringstream ss(s);
    int k = 0;
    // 将日志字段分割存入数组 a
    while (getline(ss, t, ','))
      a[k++] = t;

    // 生成唯一标识符（时间戳+客户标识+计费因子）用于去重
    string ts = a[0] + a[1] + a[2];

    // 如果该日志已处理过，则跳过
    if (ses.count(ts))
      continue;
    else
      ses.insert(ts);// 否则记录该日志

    int tt = stoi(a[3]);// 转换计费时长为整数
    // 如果计费时长不在合法范围内，则跳过
    if (tt < 0 || tt > 100) continue;

    // 记录每个客户的每个计费因子的总计费时长
    h1[{a[1], a[2]}] += tt;
  }

  int m;
  cin >> m;                     // 输入计费因子的数量
  unordered_map<string, int> h2;// 用于记录每个计费因子的单价

  // 读取计费因子和对应单价
  while (m--) {
    string s, t;
    cin >> s;// 读取一行计费因子和单价

    int k = 0;
    stringstream ss(s);
    // 将计费因子和单价字段分割存入数组 a
    while (getline(ss, t, ','))
      a[k++] = t;

    // 记录计费因子的单价
    h2[a[0]] = stoi(a[1]);
  }

  map<string, int> h3;  // 用于记录每个客户的总费用

  // 计算每个客户的总费用
  for (auto &[k, v] : h1) {
    string client = k.first, factor = k.second;
    // 计算并累加客户的总费用（单价 * 总计费时长）
    h3[client] += (h2[factor] * v);
  }

  vector<pair<string, int>> res;  // 用于存储最终结果

  // 将客户和总费用存入结果向量
  for (auto &[k, v] : h3)
    res.push_back({k, v});

  // 按客户标识字典序升序排序
  sort(res.begin(), res.end());

  // 输出每个客户的话单总费用
  for (int i = 0; i < res.size(); i++)
    cout << res[i].first << "," << res[i].second << endl;

  return 0;
}
