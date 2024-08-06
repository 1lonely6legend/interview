//
// Created by ogier on 24-4-29.
// 快速排序，每次选择一个基准值，然后将小于基准值的放在左边，大于基准值的放在右边，然后递归的对左右两边进行排序
// 时间复杂度：O(nlogn),因为每次都是将数组分成两部分，所以是logn,然后每次排序的时间复杂度是n,所以是nlogn
// 空间复杂度：O(1),因为只需要一个临时变量
// 不稳定排序
#include <vector>
#include <stack>
#include <iostream>

class non_iteration_quick_sort {
public:
  void sort(std::vector<int> &arr) {
    if (arr.empty()) return;
    quick_sort(arr, 0, arr.size() - 1);
  }

private:
  int partition(std::vector<int> &a, int left, int right) {
    //这里不需要初始判断left<right，因为在调用partition的时候已经保证了left<right
    //对于arr的left到right区间进行排序
    int l = left, r = right, key_value = a[left];
    while (l < r) {
      while (l < r && key_value <= a[r]) r--;
      a[l] = a[r];
      while (l < r && a[l] <= key_value) l++;
      a[r] = a[l];
    }
    a[l] = key_value;
    return l; //返回基准值的位置
  }

  void quick_sort(std::vector<int> &arr, int left, int right) {
    //非递归使用栈来模拟递归
    std::stack<int> stack;
    if (left < right) {
      //如果left==right，说明只有一个元素，不需要排序
      stack.push(left);
      stack.push(right);
    }

    while (!stack.empty()) {
      //栈不为空，说明还有元素需要排序
      int r_pop = stack.top();
      stack.pop();
      int l_pop = stack.top();
      stack.pop();
      //对于l_pop到r_pop区间进行排序,返回本次排序基准点的位置
      int i = partition(arr, l_pop, r_pop);
      //对基准点的两边进行判断，如果有元素，那么就继续排序
      if (l_pop < i - 1) {
        stack.push(l_pop);
        stack.push(i - 1);
      }
      if (r_pop > i + 1) {
        stack.push(i + 1);
        stack.push(r_pop);
      }
    }
  }
};


class iteration_quick_sort {
public:
  void quick_sort(std::vector<int> &a, int left, int right) {
    if (left >= right)
      return;
    int l = left, r = right, kv = a[left];
    while (l < r) {
      while (l < r && kv <= a[r]) r--;
      a[l] = a[r];
      while (l < r && a[l] <= kv) l++;
      a[r] = a[l];
    }
    a[l] = kv;
    quick_sort(a, left, l - 1);
    quick_sort(a, l + 1, right);
  }
};


int main() {
  std::vector<int> v{3, 5, 6, 536, 236, 25, 25, 2, 5, 4545, 66, 7, 34353};
  //使用左闭右闭区间，所以这里是v.size()-1
  iteration_quick_sort().quick_sort(v, 0, v.size() - 1);
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  v = {3, 5, 6, 536, 236, 25, 25, 2, 5, 4545, 66, 7, 34353};
  non_iteration_quick_sort().sort(v);
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  return 0;
}
