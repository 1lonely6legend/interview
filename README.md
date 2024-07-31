# 面试自动驾驶规划岗位中遇到的一些实际/数学问题

运行时需要加载对应文件夹下的CMakelists.txt文件，然后编译运行(Clion)

## 项目依赖

- cmake
- matplotlib-cpp(不需要画图的话删除对应代码即可)

## sort

常见的排序算法

## math

- 牛顿迭代法求一元函数根/极值
- 梯度下降法求多元函数极值，二次方程根
- 拉格朗日插值

## geometry(二维)

- 向量投影、位置关系、夹角计算
- AABB包围盒碰撞检测
- 坐标系旋转矩阵
- 使用点乘判断多边形凸性

## search

- a*算法
- dijkstra算法
- 有向加权图最短路径

## osqp_demo

参考：https://github.com/xinchu911/osqp_demo