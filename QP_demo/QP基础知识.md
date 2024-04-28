****参考：https://blog.csdn.net/weixin_42301220/article/details/126267907?spm=1001.2014.3001.5502

#### 文章目录

+ [参考资料](#_2)+ [1. 二次规划形式](#1__11)+ [2. 等式约束二次规划问题](#2__35)+
+ [2.1 变量消去法](#21__51)+
+ [1. 示例](#1__52)+ [2. 具体过程](#2__71)
+ [2.2 Lagrange法](#22_Lagrange_181)+ [2.3 变量消去 vs Lagrange法](#23__vs_Lagrange_221)
+ [3. 不等式约束二次规划问题](#3__231)+
+ [3.1 Lagrange乘数法与KKT条件](#31_LagrangeKKT_235)+
+ [1. 只有不等式约束的一般形式](#1__238)+ [2. 标准约束优化](#2__274)+ [3. 示例](#3__301)
+ [3.2 内点法](#32__468)+ [3.3 积极集法](#33__472)

## 参考资料

+ [二次规划的若干算法研究](https://kreader.cnki.net/Kreader/CatalogViewPage.aspx?dbCode=CMFD&filename=1011025016.nh&tablename=CMFD2012&compose=&first=1&uid=WEEvREcwSlJHSldSdmVqM1BLYmtHZUQ5TWN2Z29STURTMk9hMmRDeVNaZz0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4IQMovwHtwkF4VYPoHbKxJw!!)+ [关于凸二次规划若干算法的研究](https://kreader.cnki.net/Kreader/CatalogViewPage.aspx?dbCode=CMFD&filename=2008049018.nh&tablename=CMFD2008&compose=&first=1&uid=WEEvREcwSlJHSldSdmVqM1BLYmtHZUQ5TWN2Z29STURTMk9hMmRDeVNaZz0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4IQMovwHtwkF4VYPoHbKxJw!!)+ [二次规划](https://reiscarlet.github.io/2021/12/03/%E6%95%B0%E5%80%BC%E6%9C%80%E4%BC%98%E5%8C%96/%E4%BA%8C%E6%AC%A1%E8%A7%84%E5%88%92/)+ [不等式约束的优化问题](https://zhuanlan.zhihu.com/p/146837325)

由于在面试中有被问及QP的原理，所以重点来总结一波QP的原理。

## 1. 二次规划形式

二次规划问题（Quadratic Programming，QP）是一种非线性规划问题，它的目标函数为二次函数，约束条件和线性规划问题的约束条件一样，都是线性等式或线性不等式，即

$$
\tag{1} \begin{aligned} &\min \frac{1}{2} x^{\top} G x+h^{\top} x\\ s.t.\quad &a_{i}^{\top} x \leqslant b_{i}, \quad i\in \mathcal{I}=\{1 \cdots m\}.\\ &a_{i}^{\top} x=b_{i}, \quad i\in\mathcal{\epsilon}=\{m+1, \ldots m + l \}\text {. } \end{aligned}
$$

一般二次规划问题可以分成以下几类：

+ 凸二次规划问题：G半正定，问题有全局解
+ 严格凸二次规划问题：G正定，问题有唯一全局解
+ 一般二次规划问题：G不定，问题有稳定点或局部解

二次规划应用广泛，常见的例如有：求最小二乘法，点到多面体的距离，模型预测控制的求解等。

下面我们分别介绍等式约束和不等式约束下的二次规划的求解。

## 2. 等式约束二次规划问题

等式约束的二次规划问题一般形式如下：

$$
\tag{2} \begin{aligned} \min &\frac{1}{2} x^{\top} G x+h^{\top} x\\ s.t.\quad &A^{\top}x=b \end{aligned}
$$

> 其中

$$
b \in R^{m}, A \in R^{n \times m}, \operatorname{rank}(A)=m, n>m
$$

### 2.1 变量消去法(转为n-m维)

#### 1. 示例

变量消去法思路很简单，就是初中时候学过的消元法（当然，抽象之后还是挺高级的）。例如举个小栗子，假设要求解下面这个二次规划问题：

$$
\begin{array}{ll} \min & \mathrm{x}_{1}^{2}+\mathrm{x}_{2}^{2}+\mathrm{x}_{1}+ \mathrm{x}_{2} \\ \text { s.t. } & \mathrm{x}_{1}+\mathrm{x}_{2}=1 \end{array}
$$

消除一个变量$x_2$，这样就可以很简单的求解出来:

$$
\min \mathrm{x}_{1}^{2}+\left(1-\mathrm{x}_{1}\right)^{2}+1-\mathrm{x}_{1}+ \mathrm{x}_{1}
$$

当然我们还可以用拉格朗日法，推导出KKT条件（后面会讲）:

$$
\min \mathrm{x}_{1}^{2}+\mathrm{x}_{2}^{2}+\mathrm{x}_{1}+\mathrm{x}_{2}+\lambda\left(\mathrm{x}_{1}+\mathrm{x}_{2}-1\right)
$$

#### 2. 具体过程

应用变量消去法求解包括以下3个步骤：

+ **将$xx$分成基本变量 $x_{B}xB$ 与非基本变量 $x_{N}xN$ 两部分，利用等式约束将基本变量用非基本变量表示出来；+ 再将基本变量带入目标函数，从而消去基本变量，把问题化为一个关于非基本变量的无约束最优化问题；+ 最后求解无约束最优化问题的方法解之**

具体来说：

将 $A$ 分块，使其包含一个 $m \times m$ 非奇异矩阵 $A_{B} ， x ， h$ 做对应的分块

$$
\tag{3} x=\left(\begin{array}{c} x_{B} \\ x_{N} \end{array}\right), A=\left(\begin{array}{c} A_{B} \\ A_{N} \end{array}\right), G=\left(\begin{array}{ll} G_{B B} & G_{B N} \\ G_{N B} & G_{N N} \end{array}\right), h=\left(\begin{array}{c} h_{B} \\ h_{N} \end{array}\right)
$$

所以等式约束$A^{\top}x=b$就转化为：

$$
\tag{4} \left(\begin{array}{c} A_{B} \\ A_{N} \end{array}\right)^{\top} \left(\begin{array}{c} x_{B} \\ x_{N} \end{array}\right) =b
$$

将等式(4)写开得

$$
\tag{5} \begin{gathered} A_{B}x_{B} +A_{N}x_{N}=\mathrm{b} \\ \end{gathered}
$$

将基本变量用非基本变量表示出来

$$
\tag{6} x_{B}=A_{B}^{-1}b-A_{B}^{-1}A_{N}x_{N}
$$

这样原变量就可以写成:

$$
\tag{7} \begin{aligned} x=\left(\begin{array}{c} x_{B} \\ x_{N} \end{array}\right)= \left(\begin{array}{c} A_{B}^{-1}b-A_{B}^{-1}A_{N}x_{N} \\ x_{N} \end{array}\right) =\left(\begin{array}{c} A_{B}^{-1}b \\ 0 \end{array}\right)+ \left(\begin{array}{c} -A_{B}^{-1}A_{N} \\ I \end{array}\right)x_{N}=x_0+Zx_{N} \end{aligned}
$$

即写成了一个类似于 $x=x_0+Zx_{N}$ 的形式，这样我们将其代入目标函数，消去基本变量，把问题化为一个关于非基本变量的无约束最优化问题，最后求解无约束最优化问题的方法就能解出答案。

我们将$x=x_0+Zx_{N}$ 带入到目标函数中得：

$$
\tag{8} \begin{aligned} \min f(x)&=\frac{1}{2} x^{T} G x+h^{T} x\\ &=\frac{1}{2}\left(x_0+Zx_{N}\right)^TG\left(x_0+Zx_{N}\right)+h^T\left(x_0+Zx_{N}\right) \end{aligned}
$$

除了$x_N$，其他都是已知的常数项 ，由于常数项不影响优化结果，所以优化过程中省略常数项。另外，找出所有$x_N^TPx_N$和$Qx_N$的形式的项，可得如下形式：

$$
\tag{9} \begin{aligned} \min f(x)&=\frac{1}{2}x_N^TPx_N+Qx_N\\ P&=Z^TGZ\\ Q&=x_0^TGZ+h^TZ \end{aligned}
$$

注意：从式(8)到式(9)的化简形式不太严谨，这里大体是想表示通过化简是可以将式(8)化成$x_N^TPx_N+Qx_N$形式的项（这里为了偷懒，式(8)的$G$和$h$都没有写成分块矩阵的形式）

对式(9)求导等于零:

$$
\tag{10} \left(Z^TGZ\right)x_N+Q=0
$$

如果想要其有唯一最优解，也就必须要满足 $Z^TGZ$ 为正定。

### 2.2 Lagrange法(转为n+m维)

等式约束二次规划的Lagrange函数为

$$
\tag{11} L(x, \lambda)=\frac{1}{2} x^{T} G x+h^{T} x+\lambda\left(A^{T} x-b\right)
$$

**其中$\lambda$称为Lagrange乘数，正负皆有可能。Lagrange乘数法将原本的约束优化问题转换成等价的无约束优化问题**

$$
\tag{12} \min _{x, \lambda} L(x, \lambda)
$$

计算 $L$ 对 $x$ 与 $\lambda$ 的偏导数并设为零，可得最优解的必要条件:

$$
\tag{13} \left\{\begin{array}{l} \frac{\partial L}{\partial x}=G x+h+\lambda A=0 \quad\text{——定常方程式}\\ \\ \frac{\partial L}{\partial \lambda}=A^{T} x-b=0 \quad\text{——约束条件} \end{array}\right.
$$

表示为方程组:

$$
\tag{14} \left[\begin{array}{cc} G & A \\ A^{T} & 0 \end{array}\right]\left[\begin{array}{l} x \\ \lambda \end{array}\right]=\left[\begin{array}{r} -h \\ b \end{array}\right]
$$

这样将这个方程组求解之后就可以求得最优解。

### 2.3 变量消去 vs Lagrange法

根据等式(10)和(14)的维度关系，

**变量消去法其实是转化成了一个 $n-m$维的问题，也就是说求解$n-m$个方程组就能解决这个问题。而 Lagrange法是将其转化成一个 $n+m$维的问题，即 $n$个变量， $m$个乘子。**

如果建模建出来的问题就只需要求解一次等式二次规划问题，那么哪一个其实都可以求解，如果维数太大，建议用变量消去法。

变量消去法很直观，使用非基变量表示基变量，但是由于需要计算$A_B$的逆，当$A_B$接近奇异时会导致误差很大.

## 3. 不等式约束二次规划问题

本节主要来自[参考资料4](https://zhuanlan.zhihu.com/p/146837325).

### 3.1 Lagrange乘数法与KKT条件

#### 1. 只有不等式约束的一般形式

先考虑只有不等式约束的一般形式(对于不等式约束 其对应的拉格朗日乘数 λ 必须满足 ≥0,**KKT条件的一部分**)：

$$
\begin{array}{ll} \min & f(\mathbf{x}) \\ \text { s.t. } & g(\mathbf{x}) \leq 0 . \end{array}
$$

约束不等式 $g(\mathbf{x}) \leq 0$ 称为原始可行性(primal feasibility)，据此我们定义可行域(feasible region)

$$
K=\{\mathbf{x} \in \mathbb{R}^{n} \mid g(\mathbf{x}) \leq 0\}
$$

假设 $\mathbf{x}^{\star}$ 为满足约束条件的最佳解，分开两种情况讨论：

+ $g\left(\mathbf{x}^{\star}\right)<0$ ，**最佳解位于 $K$ 的内部**，称为内部解(interior solution)，这时约束条件是无效的 (inactive);
+ $g\left(\mathbf{x}^{\star}\right)=0$ ，**最佳解落在 $K$ 的边界**，称为边界解(boundary solution)，此时约束条件是有效的(active)。

这两种情况的最佳解具有不同的必要条件。

+ 内部解: 在约束条件无效的情形下， $g(\mathbf{x})$ 不起作用，**约束优化问题退化为无约束优化问题**， 因此驻点 $\mathbf{x}^{\star}$ 满足 $\nabla f=\mathbf{0}$ 且 $\lambda=0$ 。
+ **边界解**：
  + 在约束条件有效的情形下，约束不等式变成等式 $g(\mathbf{x})=0$（**因为如果解没有落在内部的话，一定是在边缘，那么就是在约束上**） ，这与前述Lagrange乘数法的情况相同。
  + 我们可以证明驻点（最优解） $\mathbf{x}^{\star}$ 发生于 $\nabla f \in \operatorname{span}\nabla g$ （[span是生成子空间](https://blog.csdn.net/weixin_46089591/article/details/121294872)，是由$\nabla g$所有可能向量构成的空间），换句话说，存在 $\lambda$ 使得 $\nabla f=-\lambda \nabla g$ (因为lagrange函数包含两项，如果要在边界位置求得解，说明，f和g的梯度方向应该相反，这样才能将解约束在边界位置)（目标函数梯度反方向，也就是迭代方向和约束条件梯度成倍数关系），但这里 $\lambda$ 的正负号是有其意义的。因为我们希望最小化 $f$ ，梯度 $\nabla f$ (函数 $f$ 在点 $\mathbf{x}$ 的最陡上升方向)应该指向可行域 $K$ 的内部(**因为你的最优解最小值是在边界取得的**)，
  + 但 $\nabla g$ 指向 $K$ 的外部(即 $g(\mathbf{x})>0$ 的区域，因为你的约束是小于等于 0 ，目标函数方向），因此 $\lambda \geq 0$，称为对偶可行性(dual feasibility)。


> chargpt关于这部分   存在 $\lambda$ 使得 $\nabla f=-\lambda \nabla g$     理解：
>
> 这段文字描述了在不等式约束优化问题中，Lagrange乘数法下的Karush-Kuhn-Tucker (KKT) 条件的部分内容。以下是详细解释：
>
> 5. **拉格朗日乘数的方向**：这个条件说明了当在可行域的边界上找到一个局部最优解时，目标函数 $f$ 的梯度 $\nabla f$ 方向是可行域外向的，这意味着如果我们沿 $\nabla f$方向移动，我们将离开可行域。所以为了最小化 $f$ ，我们必须朝着 $-\nabla f$的方向移动，但由于我们不能离开可行域，所以这个方向必须被拉格朗日乘数对应的约束梯度$\nabla g$“阻挡”。
>
> 6. **梯度 $\nabla f$ 的方向**：在约束不等式 $g(x) \leq 0 $ 影响优化问题解的边界条件下，目标函数的梯度 $\nabla f $在可行域的边界上不能指向可行域的外部。这是因为我们要找的是最小化 $f $的点，而如果$\nabla f$指向外部，那么沿这个方向移动将会增加$ f  $的值，这与最小化$ f $的目标相违背。所以在边界上，我们希望 $\nabla f $要么指向内部，要么完全由约束的梯度 $\nabla g$ 控制，从而保持在边界上。
>
> 7. **梯度 $\nabla g $的方向和含义**：由于 $ g(x) \leq 0 $定义了一个可行域，$\nabla g $在边界上指向的是可行域的外部，即向$ g(x) $增加的方向。如果$ g(x) $的值增加$ g(x) > 0 $，我们会离开可行域。因此，为了保持在可行域内部或边界上，解的移动方向（即目标函数$  f  $的梯度 $\nabla f $必须与$ \nabla g $的方向相反或者不与 $\nabla g $指向相同的方向。这就是为什么当$ \nabla f $和 $ \nabla g$ 对齐时，拉格朗日乘数$ \lambda $必须为正数，即对偶可行性，以确保移动方向不会离开可行域。

因此，**不论是内部解或边界解， $\lambda g(\mathbf{x})=0$ 恒成立，**称为互补松弛性(complementary slackness)。整合上述两种情况，最佳解的必要条件包括Lagrangian函数 $L(\mathbf{x}, \lambda)$ 的：

- **梯度条件**：在最优点，lagrange函数梯度线性组合为0

- **原始可行性**：所有解必须满足问题中的不等式约束

- **对偶可行性**：对应不等式约束的拉格朗日乘数必须非负，这样保证移动方向不会出可行域

- **互补松弛性**：只有可能是内部解（$\lambda$ = 0）或者边界解($g(x)=0$)

$$
\left\{\begin{array}{l} \begin{aligned} \nabla_{\mathbf{x}} L &=\nabla f+\lambda \nabla g=\mathbf{0} \\ g(\mathbf{x}) & \leq 0 \\ \lambda & \geq 0 \\ \lambda g(\mathbf{x}) &=0 . \end{aligned} \end{array}\right.
$$

这些条件合称为Karush-Kuhn-Tucker (KKT)条件。如果我们要最大化 $f(\mathbf{x})$ 且受限于 $g(\mathbf{x}) \leq 0$ ，那么对偶可行性要改成 $\lambda \leq 0$ 。

#### 2. 标准约束优化

考虑标准约束优化问题(或称非线性规划)：

$$
\begin{array}{ll} \min & f(\mathbf{x}) \\ \text { s.t. } & g_{j}(\mathbf{x})=0, \quad j=1, \ldots, m, \\ & h_{k}(\mathbf{x}) \leq 0, \quad k=1, \ldots, p . \end{array}
$$

定义Lagrangian 函数

$$
L\left(\mathbf{x},\left\{\lambda_{j}\right\},\left\{\mu_{k}\right\}\right)=f(\mathbf{x})+\sum_{j=1}^{m} \lambda_{j} g_{j}(\mathbf{x})+\sum_{k=1}^{p} \mu_{k} h_{k}(\mathbf{x})
$$

其中 $\lambda_{j}$ 是对应 $g_{j}(\mathbf{x})=0$ 的Lagrange乘数， $\mu_{k}$ 是对应 $h_{k}(\mathbf{x}) \leq 0$ 的Lagrange乘数(或称 KKT乘数)。KKT条件包括**定常方程式、原始可行性、对偶可行性，以及互补松弛性**，如下所示：

$$
\left\{\begin{array}{l} \begin{aligned} \nabla_{\mathbf{x}} L &=\mathbf{0} \\ g_{j}(\mathbf{x}) &=0, \quad j=1, \ldots, m, \\ h_{k}(\mathbf{x}) & \leq 0, \\ \mu_{k} & \geq 0, \\ \mu_{k} h_{k}(\mathbf{x}) &=0, \quad k=1, \ldots, p . \end{aligned} \end{array}\right.
$$

#### 3. 示例

+ 考虑这个问题

$$
\left\{\begin{array}{ll} \min & x_{1}^{2}+x_{2}^{2} \\ \text { s.t. } & x_{1}+x_{2}=1 \\ & x_{2} \leq \alpha \end{array}\right.
$$

其中 $\left(x_{1}, x_{2}\right) \in \mathbb{R}^{2}, \alpha$ 为实数。写出Lagrangigan函数

$$
L\left(x_{1}, x_{2}, \lambda, \mu\right)=x_{1}^{2}+x_{2}^{2}+\lambda\left(1-x_{1}-x_{2}\right)+\mu\left(x_{2}-\alpha\right)
$$

KKT 方程组如下:

$$
\left\{\begin{array}{l} \begin{aligned} \frac{\partial L}{\partial x_{i}} &=0, \quad i=1,2 \\ x_{1}+x_{2} &=1 \\ x_{2}-\alpha & \leq 0 \\ \mu & \geq 0 \\ \mu\left(x_{2}-\alpha\right) &=0 \end{aligned} \end{array}\right.
$$

求偏导可得

$$
\left\{\begin{array}{l} \begin{aligned} \frac{\partial L}{\partial x_{1}}&=2 x_{1}-\lambda=0\\ \frac{\partial L}{\partial x_{2}}&=2 x_{2}-\lambda+\mu=0 \end{aligned} \end{array}\right.
$$

分别解出

$$
\left\{\begin{array}{l} \begin{aligned} x_{1}&=\frac{\lambda}{2}\\ x_{2}&=\frac{\lambda}{2}-\frac{\mu}{2} \end{aligned} \end{array}\right.
$$

代入约束等式

$$
x_{1}+x_{2}=\lambda-\frac{\mu}{2}=1
$$

合并上面结果，

$$
\left\{\begin{array}{l} \begin{aligned} x_{1}&=\frac{\mu}{4}+\frac{1}{2}\\ x_{2}&=-\frac{\mu}{4}+\frac{1}{2} \end{aligned} \end{array}\right.
$$

最后再加入约束不等式

$$
-\frac{\mu}{4}+\frac{1}{2} \leq \alpha
$$

即

$$
\mu \geq 2-4 \alpha
$$

底下分开三种情况讨论。

+ $\alpha>\frac{1}{2}$ : 不难验证 $\mu=0>2-4 \alpha$ 满足所有的KKT条件，约束不等式是无效的， $x_{1}^{\star}=x_{2}^{\star}=\frac{1}{2}$ 是内部解，目标函数的极小值是 $\frac{1}{2}$ 。+ $\alpha=\frac{1}{2}$ : 如同 1 ， $\mu=0=2-4 \alpha$ 满足所有的KKT条件， $x_{1}^{\star}=x_{2}^{\star}=\frac{1}{2}$ 是边界解，因为 $x_{2}^{\star}=\alpha$ 。+ $\alpha<\frac{1}{2}$ : 这时约束不等式是有效的， $\mu=2-4 \alpha>0$ ，则 $x_{1}^{\star}=1-\alpha$ 且 $x_{2}^{\star}=\alpha$ ，目 标函数的极小值是 $(1-\alpha)^{2}+\alpha^{2}$ 。
+ 考虑优化问题

$$
\tag{1} \begin{aligned} &\operatorname{min }f(\mathrm{x})=-2 \mathrm{x}_1^2-\mathrm{x}_1^2 \\ &\text { s.t. } \quad \mathrm{x}_1^2+\mathrm{x}_2^2-2=0 \\ &\quad-\mathrm{x}_1+\mathrm{x}_2 \geq 0 \\ &\quad \mathrm{x}_1 \geq 0, \mathrm{x}_2 \geq 0 \end{aligned}
$$

试验证 $x^*=(1,1)^{\mathrm{T}}$ 为 $\mathrm{KKT}$ 点，并求出问题的 $\mathrm{KKT}$ 对。 【解】记

$$
\tag{2} \begin{aligned} \mathrm{f}(\mathrm{x}) &=-2 \mathrm{x}_1^2-\mathrm{x}_1^2 \\ \mathrm{~g}(\mathrm{x}) &=\mathrm{x}_1^2+\mathrm{x}_2^2-2 \\ \mathrm{~h}_1(\mathrm{x}) &=\mathrm{x}_1-\mathrm{x}_2 \\ \mathrm{~h}_2(\mathrm{x}) &=-\mathrm{x}_1 \\ \mathrm{~h}_3(\mathrm{x}) &=-\mathrm{x}_2 \end{aligned}
$$

求梯度（都使用向量的形式写法，更紧凑），得到

$$
\tag{3} \begin{aligned} \nabla \mathrm{f}(\mathrm{x})=\left[\begin{array}{c} -4 \mathrm{x}_1 \\ -2 \mathrm{x}_2 \end{array}\right], \quad \nabla \mathrm{g}(\mathrm{x})=\left[\begin{array}{l} 2 \mathrm{x}_1 \\ 2 \mathrm{x}_2 \end{array}\right] \\ \nabla \mathrm{h}_1(\mathrm{x})=\left[\begin{array}{c} 1 \\ -1 \end{array}\right], \quad \nabla \mathrm{h}_2(\mathrm{x})=\left[\begin{array}{l} -1 \\ 0 \end{array}\right], \quad \nabla \mathrm{h}_3(\mathrm{x})=\left[\begin{array}{l} 0 \\ -1 \end{array}\right] \end{aligned}
$$

把 $x^*=(1,1)^{\mathrm{T}}$ 代入上面5个式子，由 $\mathrm{KKT}$ 条件有，

$$
\tag{4} \left\{\begin{array}{l} -4+2 \lambda+\mu_1-\mu_2=0 \\ -2+2 \lambda-\mu_1+\mu_3=0 \end{array}\right.
$$

因为

$$
\tag{5} \left\{\begin{array} { l } { \mu _ { 2 } \mathrm { h } _ { 2 } ( { \mathrm { x } } ) = 0 } \\ { \mu _ { 3 } \mathrm { h } _ { 3 } ( { \mathrm { x } } ) = 0 } \end{array} \Rightarrow \left\{\begin{array}{l} \mu_2^*=0 \\ \mu_3^*=0 \end{array}\right.\right.
$$

所以(4)变为

$$
\tag{6} \left\{\begin{array}{l} -4+2 \lambda+\mu_1=0 \\ -2+2 \lambda-\mu_1=0 \end{array}\right.
$$

求解 $(6)$ 式，得到

$$
\tag{7} \left\{\begin{array}{l} \lambda^*=1.5 \\ \mu_1^*=1 \end{array}\right.
$$

这表明 $\mathrm{x}^*$ 是 $\mathrm{KKT}$ 点， $\left(\mathrm{x}^*,\left(\lambda^*, \mu^*\right)\right)$ 是 $\mathrm{KKT}$ 对，其中， $\lambda^*=1.5 ， \mu^*=(1,0,0)^{\mathrm{T}}$ 。

分割线，下面待更新

### 3.2 内点法

内点法引入障碍函数将约束条件转化为目标函数，生成等价于原模型的优化问题。

### 3.3 积极集法
