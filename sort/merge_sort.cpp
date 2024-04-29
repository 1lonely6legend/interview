//
// Created by ogier on 24-4-29.
// 归并排序，将数组分成两部分，分别排序，然后合并
// 时间复杂度：O(nlogn),因为每次都是将数组分成两部分，所以是logn,然后每次合并的时间复杂度是n,所以是nlogn
// 空间复杂度：O(n),因为需要一个临时数组来存放合并后的数组
// 稳定排序,也就是说如果有两个相等的数，排序后他们的相对位置不会改变
#include <vector>
#include <iostream>
using namespace std;
void merge_sort(vector<int> &v, int left, int right) {
  //如果左右区间重合，只有一个数字，那就不需要排序了直接返回
  if (left >= right) return;
  int mid = (left + right) / 2;
  //注意使用左闭右开区间，所以这里是mid和mid+1
  merge_sort(v, left, mid);
  merge_sort(v, mid + 1, right);
  //设置一个临时数组，用来存放合并后的数组
  vector<int> temp;
  //设置两个指针，分别指向两个数组的头部,方便后面比较
  int i = left, j = mid + 1;
  //首先比较两个数组的头部，小的放入临时数组，然后指针后移
  while (i <= mid && j <= right) {
    if (v[i] < v[j]) {
      temp.push_back(v[i++]);
    } else {
      temp.push_back(v[j++]);
    }
  }
  //如果有一个数组已经全部放入临时数组，那么另一个数组剩下的部分直接放入临时数组
  while (i <= mid) {
    temp.push_back(v[i++]);
  }
  //同上
  while (j <= right) {
    temp.push_back(v[j++]);
  }
  //将临时数组的值放回原数组
  for (int i = 0; i < temp.size(); i++) {
    v[left + i] = temp[i];
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
