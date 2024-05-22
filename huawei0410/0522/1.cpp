//
// Created by ogier on 24-5-22.
//
/*
* 给定两个链表，获取两者中相同节点值的最大连续片段，如果没有公共片段，退回-1.
* */
#include <bits/stdc++.h>
using namespace std;

vector<int> func(vector<int>& nums1, vector<int>& nums2) {
  int m = nums1.size(), n = nums2.size();
  //dp[i][j] nums1[i-1]和nums2[j-1] 最长公共子序列长度
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  int MaxLength = 0, EndPos = -1;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (nums1[i - 1] == nums2[j - 1]) {//相等时，dp[i][j] = dp[i-1][j-1]+1
        dp[i][j] = dp[i - 1][j - 1] + 1;
        if (dp[i][j] > MaxLength) {//更新最大长度和结束位置
          MaxLength = dp[i][j];
          EndPos = i - 1;
        }
      }
    }
  }
  if (MaxLength == 0) {
    return {-1};
  } else {
    return vector<int>(nums1.begin() + EndPos - MaxLength + 1, nums1.begin() + EndPos + 1);
  }
}
int main() {
  vector<int> nums1, nums2;
  int num;
  while (cin >> num) {
    nums1.push_back(num);
    if (cin.get() == '\n') break;
  }
  while (cin >> num) {
    nums2.push_back(num);
    if (cin.get() == '\n') break;
  }
  vector<int> res = func(nums1, nums2);
  if (res.size() == 1 && res[0] == -1) {
    cout << -1 << endl;
  } else {
    for (int val : res) {
      cout << val << " ";
    }
    cout << endl;
  }
  return 0;
}