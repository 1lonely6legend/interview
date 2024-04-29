//
// Created by ogier on 24-4-29.
// 插入排序,每次循环，将一个数插入到已经排好序的数组中，遍历一次后，数组就是有序的了
// 时间复杂度：O(n^2),因为每次都是将一个数插入到有序数组中，所以是n^2
// 空间复杂度：O(1),因为只需要一个临时变量
// 稳定排序,也就是说如果有两个相等的数，排序后他们的相对位置不会改变
#include <vector>
#include <iostream>
using namespace std;
void insert_sort(vector<int> &v) {
  //从第二个数开始，因为第一个数默认是有序的，也就是最开始的有序数组
  for (int i = 1; i < v.size(); ++i) {
    //取出现在要插入的数
    int temp = v[i];
    //从后往前遍历，找到插入的位置,j为有序数组的最后一个数
    int j = i - 1;
    //如果j合法,并且有序数组的最后一个数大于要插入的数，那么就将有序数组的最后一个数往后移动
    while (j >= 0 && v[j] > temp) {
      v[j + 1] = v[j];
      --j;
    }
    //将要插入的数插入到有序数组中
    v[j + 1] = temp;
  }
}
int main() {
  int a[] = {3, 5, 6, 536, 236, 25, 25, 2, 5, 4545, 66, 7, 34353};
  std::vector<int> v(a, a + sizeof(a) / sizeof(int));
  insert_sort(v);
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  return 0;
}
