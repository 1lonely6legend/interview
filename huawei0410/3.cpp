//
// Created by ogier on 24-5-16.
//
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;
int n;
const int N = 30;
int a[N][N];
bool st[N];
int dfs(int id, int ra) {
  int num = 0, sm = 0;
  for (int i = 0; i < n; i++) {
    if (id == i || !a[id][i]) continue;
    if (ra >= a[id][i]) {
      if (st[i]) continue;
      st[i] = true;
      num += dfs(i, a[id][i]);
      st[i] = false;
    }
  }

  return num + 1;
}
int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];

  int x;
  int res = -1, ans = 0;
  while (cin >> x) {
    for (int i = 0; i < n; i++) {
      if (x == i) continue;
      st[x] = true;
      int t = dfs(x, 10);
      st[x] = false;
      if (t > ans) {
        ans = t;
        res = x;
      }
    }
  }
  cout << res;
  return 0;
}