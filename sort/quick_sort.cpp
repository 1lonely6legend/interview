//
// Created by ogier on 24-4-29.
// 快速排序，每次选择一个基准值，然后将小于基准值的放在左边，大于基准值的放在右边，然后递归的对左右两边进行排序
// 时间复杂度：O(nlogn),因为每次都是将数组分成两部分，所以是logn,然后每次排序的时间复杂度是n,所以是nlogn
// 空间复杂度：O(1),因为只需要一个临时变量
// 不稳定排序
#include <vector>
#include <iostream>
void quick_sort(std::vector<int> &a, int left, int right) {
  //如果左右区间重合，只有一个数字，那就不需要排序了直接返回
  if (left >= right) return;
  //设置这次需要排序的范围，选择基准值
  int i = left, j = right, key_value = a[left];
  //在这个while循环过后，根据key大小，分为左右
  while (i < j) {
    //首先从右边开始，寻找第一个小于key的值，然后与key交换
    while (i < j && a[j] >= key_value) --j;
    a[i] = a[j];
    //从左边开始，寻找第一个大于key的值，然后与key交换
    while (i < j && a[i] <= key_value) ++i;
    a[j] = a[i];
  }
  a[i] = key_value;
  quick_sort(a, left, i - 1);
  quick_sort(a, i + 1, right);
}
int main() {
  int a[] = {3, 5, 6, 536, 236, 25, 25, 2, 5, 4545, 66, 7, 34353};
  std::vector<int> v(a, a + sizeof(a) / sizeof(int));
  //使用左闭右闭区间，所以这里是v.size()-1
  quick_sort(v, 0, v.size() - 1);
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  return 0;
}
