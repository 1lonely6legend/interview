//
// Created by ogier on 24-4-29.
// 归并排序，将数组分成两部分，分别排序，然后合并
// 时间复杂度：O(nlogn),因为每次都是将数组分成两部分，所以是logn,然后每次合并的时间复杂度是n,所以是nlogn
// 空间复杂度：O(n),因为需要一个临时数组来存放合并后的数组
// 稳定排序,也就是说如果有两个相等的数，排序后他们的相对位置不会改变
#include <iostream>
#include <vector>
using namespace std;
// 归并排序函数，使用左闭右闭的区间 [left, right]
void merge_sort(vector<int> &v, int left, int right) {
  // 如果区间内只有一个元素，则无需排序
  if (left >= right)
    return;
  // 计算中间位置
  int mid = left + (right - left) / 2;
  // 递归排序左半部分 [left, mid]
  merge_sort(v, left, mid);
  // 递归排序右半部分 [mid + 1, right]
  merge_sort(v, mid + 1, right);
  // 创建一个临时数组用于合并
  vector<int> temp;
  // 初始化两个指针，分别指向左右两个子数组的起始位置
  int i = left, j = mid + 1;
  // 比较两个子数组的元素，将较小的元素放入临时数组
  while (i <= mid && j <= right) {
    if (v[i] < v[j]) {
      temp.push_back(v[i++]);
    } else {
      temp.push_back(v[j++]);
    }
  }
  // 将左半部分剩余的元素放入临时数组
  while (i <= mid) {
    temp.push_back(v[i++]);
  }
  // 将右半部分剩余的元素放入临时数组
  while (j <= right) {
    temp.push_back(v[j++]);
  }
  // 将临时数组中的元素复制回原数组的相应位置
  for (int k = 0; k < temp.size(); k++) {
    v[left + k] = temp[k];
  }
}

int main() {
  int a[] = {3, 5, 6, 536, 236, 25, 25, 2, 5, 4545, 66, 7, 34353};
  std::vector<int> v(a, a + sizeof(a) / sizeof(int));
  //使用左闭右闭区间，所以这里是v.size()-1
  merge_sort(v, 0, v.size() - 1);
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  return 0;
}
