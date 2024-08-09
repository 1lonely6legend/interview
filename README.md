# 面试自动驾驶规划岗位中遇到的一些实际/数学问题

运行时需要加载对应文件夹下的CMakelists.txt文件，然后编译运行(Clion)

## 项目依赖

- cmake
- matplotlib-cpp(不需要画图的话删除对应代码即可)
- osqp(仅osqp_demo依赖)

## 各文件内容

### sort

常见的排序算法实现(时间复杂度\最坏时间复杂度\空间复杂度\稳定性)，包括：

- 堆排序 
  - O(nlogn)\O(nlogn)\O(nlogn)\不稳定
- 插入排序
  - O(n^2)\O(n^2)\O(1)\稳定
- 归并排序
  - O(nlogn)\O(nlogn)\O(n)\稳定
- 冒泡排序
  - O(n^2)\O(n^2)\O(1)\稳定
- 快排
  - O(nlogn)\O(n^2)\O(long)\稳定
- 选择排序
  - O(n^2)\O(n^2)\O(1)\不稳定

### math

- 牛顿迭代法求一元函数根/极值
- 梯度下降法求多元函数极值，一元函数极值，二次方程根
- 拉格朗日插值
- 矩阵基础运算

## geometry(二维)

- 向量投影、位置关系、夹角计算
- AABB包围盒碰撞检测
- 坐标系旋转矩阵
- 使用点乘判断多边形凸性

### search

- a*算法
- dijkstra算法
- 有向加权图最短路径

### own_class

- shared_ptr简单实现(线程不安全)
- 单例模式简单实现(线程不安全)

### mulit_threads

- 一个简单的多线程demo

### osqp_demo
参考：https://github.com/xinchu911/osqp_demo
- 一个简单的调用osqp求解器的demo
