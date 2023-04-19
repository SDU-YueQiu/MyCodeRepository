# STL 23.1.26

## 1.lower_bound && upper

​	a.lower_bound(x) 指向a中第一个>=x的键值对应的迭代器

​	a.upper_bound(x)指向a中第一个>x的键值对应的迭代器

​	当x∉a时，lower_bound>x。

​	否则$x\in \left [ \text{a.lower\_bound(x)},\text{a.upper\_bound(x)} \right ) $

---

​	用法示例：

```c++
int cor = get<0>(vec[i]), l = get<1>(vec[i]), r = get<2>(vec[i]);
auto it1 = st.lower_bound(l);
auto it2 = st.lower_bound(r);
//it1 到 it2之间就是∈[l,r]的数据
```

## 2.手写queue

## A题

​	图论，之后在做。

---

​	狗寄吧图论，我是傻逼。

​	如果一个贵物比其他贵物更贵物，那么无论整个图里面有没有环，只要排序，最贵物的贵物就会被排序到最边上。

## B题

#### tuple:

#### 1.

	tuple是一个固定大小的不同类型值的集合，是泛化的std::pair。我们也可以把它当做一个通用的结构体来用，不需要创建结构体又获取结构体的特征，在某些情况下可以取代结构体使程序更简洁，直观。std::tuple理论上可以有无数个任意类型的成员变量，而std::pair只能是2个成员，因此在需要保存3个及以上的数据时就需要使用tuple元组了。
使用get获取tuple元素：

```c++
get<num>(tup) 
//tup 表示某个 tuple 对象，num 是一个整数，get() 是 <tuple> 头文件提供的全局函数，功能是返回 tup 对象中第 num+1 个元素。
```

##### 2.对于set，尽量一个个操作，不要用循环操作。

##### 3.发现T~i~+X~i~如果每次处理比较复杂，那么可以把X~i~移动到区间内

##### 4.注意对pair使用XX_bound时候，first相等的情况如何处理

```c++
auto lowerit = copleset.lower_bound(make_pair(get<1>(guards[i]),-1));
auto upperit = copleset.upper_bound(make_pair(get<2>(guards[i]),INF));
```

### 去他妈的endl

**使用endl 700ms**

**换成"\n" 200ms**

**endl死不足惜**

## C题

​	从右往左不行就从左往右；

​	优先队列也是堆；

​	可以边运行边建堆。

## D题

?:运算符优先级非常低，最好括起来

##### 注意无药可救者

#### 干他妈的傻逼long long

注意补血到1

### 反证法过贪心

#### 双端队列底层是分块(map)较慢，一般不建议用

