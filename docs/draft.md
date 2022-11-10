 # 吴洋公式手稿

## 模型

充电速度e， 耗电速度r， 电容量100，




### 约束



#### 每次出发分开来看的公式

出发时的初始电量$e_{i}^k$ 表示第k个无人机第i次出发

第k个无人机第i次出发的时间$et_{i}^k$
第k个无人机第i次到达的时间$rt_{i}^k$

不空电
$$r(t - et_i^k) \leq e_i^k, \forall k = 1,...,M, \forall t < ct_i, i \geq1$$

不溢电
$$e_0^k = 100$$
$$e_i^k = \min \{100, e_{i-1}^k + e * (et_i^k - rt_{i-1}^k)  - r*(rt_{i-1}^k - et_{i-1}^k)\}, i\geq1,\forall k = 1,...,M $$

上面这条不如说是定义，递推计算式，不是约束

不太能写在一起，除非重新定义一个新的求和运算

传统的求和和积分是不考虑求和顺序的，所以单求和肯定8行


#### 想办法把min去了的公式

不空电（中间过程）
$$r(t - et_i^k) \leq e_i^k, \forall k = 1,...,M,\forall t < ct_i, i \geq1$$

不溢电
$$e_0^k = 100, \forall k = 1,...,M$$
$$e * (et_{i}^k-rt_{i-1}^k) \leq 100 -  e_{i-1}^k + r*(rt_{i-1}^k - et_{i-1}^k), \forall k = 1,...,M, i \geq1$$

电量计算式

$$e_i^k = 100 + \sum_{j = 1}^{j=i} e*(et_i^k-rt_{i-1}^k)  -r*(rt_{i-1}^k - et_{i-1}^k), \forall k = 1,...,M, i \geq1$$

这条和不空电合起来

$$r(t - et_i^k) \leq 100 + \sum_{j = 1}^{j=i} e*(et_j^k-rt_{j-1}^k)  -r*(rt_{j-1}^k - et_{j-1}^k), \forall k = 1,...,M, i \geq1$$