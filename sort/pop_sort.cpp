//
// Created by ogier on 24-4-29.
// 冒泡排序，每次循环，将最大的数放在最后面，遍历一次后，最大的数就在最后面了，然后再从第一个数开始，继续找最大的数，放在倒数第二个位置，以此类推
// 时间复杂度：O(n^2),因为每次都是将一个数放在最后面，所以是n^2
// 空间复杂度：O(1),因为只需要一个临时变量
// 稳定排序
#include <iostream>
#include <vector>
using namespace std;
void pop_sort(vector<int>& v) {
  int loop = v.size();
  while (loop--) {
    //需要从头到尾冒泡n次
    for (int i = 0; i < v.size() - 1; ++i) {
      if (v[i] > v[i + 1]) {
        int temp = v[i];
        v[i] = v[i + 1];
        v[i + 1] = temp;
      }
    }
  }
}
int main() {
  int a[] = {3, 5, 6, 536, 236, 25, 25, 2, 5, 4545, 66, 7, 34353};
  std::vector<int> v(a, a + sizeof(a) / sizeof(int));
  pop_sort(v);
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  return 0;
}
