//
// Created by ogier on 24-4-29.
// 选择排序，每次循环，将最小的数放在最前面，遍历一次后，最小的数就在最前面了，然后再从第二个数开始，继续找最小的数，放在第二个位置，以此类推
// 时间复杂度：O(n^2),因为每次都是将一个数放在前面，所以是n^2
// 空间复杂度：O(1),因为只需要一个临时变量
// 不稳定排序
#include <vector>
#include <iostream>
using namespace std;
void select_sort(vector<int> &v) {
  for (int i = 0; i < v.size(); ++i) {
    int min = i;
    for (int j = i + 1; j < v.size(); ++j) {
      if (v[j] < v[min]) {
        min = j;
      }
    }
    int temp = v[i];
    v[i] = v[min];
    v[min] = temp;
  }
}
int main() {
  int a[] = {3, 5, 6, 536, 236, 25, 25, 2, 5, 4545, 66, 7, 34353};
  std::vector<int> v(a, a + sizeof(a) / sizeof(int));
  select_sort(v);
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  return 0;
}
