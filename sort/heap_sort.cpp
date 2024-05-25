//
// Created by ogier on 24-5-25.
//  https://www.bilibili.com/video/BV1fp4y1D7cj
#include <bits/stdc++.h>
using namespace std;
/* 下标为i的节点的父节点下标为(i-1)/2
 * 下标为i的节点的左孩子下标为2*i+1
 * 下标为i的节点的右孩子下标为2*i+2
 */
/**
 * 维护堆的性质
 * @param arr 存储堆的数组
 * @param n 数组长度
 * @param i 待维护节点的下标
 */
void heapify(int arr[], int n, int i) {
  int largest = i;//假设父节点是最大的
  int lson = i * 2 + 1;//左孩子
  int rson = i * 2 + 2;//右孩子

  if (lson < n && arr[largest] < arr[lson]) {
    largest = lson;//如果左孩子比父节点大，那么最大的就是左孩子
  }
  if (rson < n && arr[largest] < arr[rson]) {
    largest = rson;//如果右孩子比父节点大，那么最大的就是右孩子
  }
  if (largest != i) {
    //如果最大的不是父节点，那么交换父节点和最大的孩子节点,然后递归的维护
    swap(arr[largest], arr[i]);
    heapify(arr, n, largest);
  }
}
/**
 * 建堆并使用堆排序，每次将堆顶元素和最后一个元素交换，然后维护堆的性质，最后按照从小到大的顺序排序
 * @param arr 存储堆的数组
 * @param n 数组长度
 */
void heap_sort(int arr[], int n) {
  //建堆，从最后一个非叶子节点开始，递归的维护堆的性质
  //最后一个节点是n - 1, 所以最后一个非叶子节点是(n-1-1)/2 = n/2-1
  for (int i = n / 2 - 1; i >= 0; --i) {
    heapify(arr, n, i);//维护堆的性质
  }
  //堆排序，每次将堆顶元素和最后一个元素交换，然后维护堆的性质
  for(int i = n - 1; i > 0; --i) {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}