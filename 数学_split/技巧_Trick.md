## 技巧/Trick
![image](https://cdn.nlark.com/yuque/__latex/53072c2388d69edc65c2377681e4e87c.svg)，我们在一个空数组中不断加入新的数字，那么该数组的![image](https://cdn.nlark.com/yuque/__latex/62e1b8edc71b5f118c806bac439d870e.svg)单调不升，且最多会出现![image](https://cdn.nlark.com/yuque/__latex/efebabab3622c6221ab8d5cef54f384c.svg)种数字，因为每次![image](https://cdn.nlark.com/yuque/__latex/62e1b8edc71b5f118c806bac439d870e.svg)下降至少除以![image](https://cdn.nlark.com/yuque/__latex/2b89979f54ec02a7bf87aa0c1ea58ff9.svg)



![image](https://cdn.nlark.com/yuque/__latex/2b89979f54ec02a7bf87aa0c1ea58ff9.svg)，我们考虑如何维护区间![image](https://cdn.nlark.com/yuque/__latex/994ff73472bbb2f119d3e4ff653e87e8.svg)，首先直接暴力一直取![image](https://cdn.nlark.com/yuque/__latex/994ff73472bbb2f119d3e4ff653e87e8.svg)会变得很大，取模会使答案错误，因此必须从质因子上着手。

我们考虑怎么修正贡献，我们不妨开一个大小为![image](https://cdn.nlark.com/yuque/__latex/9f493997c33913987175caf4a4849955.svg)的桶，其中![image](https://cdn.nlark.com/yuque/__latex/67ccf3d24c082c818188b0cb4e8ce87d.svg)的位置有效，且权值为![image](https://cdn.nlark.com/yuque/__latex/d4cd21d60552e207f237e82def9029b6.svg),答案乘以该权值![image](https://cdn.nlark.com/yuque/__latex/3bb10f1d5025cd88d0887f887470953a.svg)当且仅当询问区间内![image](https://cdn.nlark.com/yuque/__latex/67ccf3d24c082c818188b0cb4e8ce87d.svg)被覆盖至少一次。

那我们不妨考虑离线询问用莫队来做，这样加减一个数字是做![image](https://cdn.nlark.com/yuque/__latex/efebabab3622c6221ab8d5cef54f384c.svg)次桶修改，过程中即可维护答案，复杂度![image](https://cdn.nlark.com/yuque/__latex/746921736ecff6a5a244982cd18a4a88.svg)

如果![image](https://cdn.nlark.com/yuque/__latex/9f493997c33913987175caf4a4849955.svg)很大我们不妨只考虑有效位置，用哈希的办法映射。



![image](https://cdn.nlark.com/yuque/__latex/a7720a85557fdd660de5e2da1dfa7c07.svg)如何求连续自然数的异或和？我们不妨转化为两个从![image](https://cdn.nlark.com/yuque/__latex/53072c2388d69edc65c2377681e4e87c.svg)开始的前缀异或和

那么前缀异或和有结论

```cpp
// 代码已提取到: code/技巧_Trick_8.cpp
```



![image](https://cdn.nlark.com/yuque/__latex/afb0613a26341d701b3967ba170aa30c.svg)一段连续的自然数同时异或一个相同的数，会得到![image](https://cdn.nlark.com/yuque/__latex/7604614fddf2d8179cfb467a051ec459.svg)段连续的自然数



![image](https://cdn.nlark.com/yuque/__latex/b15983bcda2a67366d095cfeb326717a.svg)<font style="color:rgb(33, 37, 41);">满足</font>![image](https://cdn.nlark.com/yuque/__latex/aff172e49e22d3b84ea1e41b54462b74.svg)<font style="color:rgb(33, 37, 41);">的组合数</font>![image](https://cdn.nlark.com/yuque/__latex/07c6b623165085bbeb7d563261ee7163.svg)<font style="color:rgb(33, 37, 41);">为奇数，否则为偶数</font>

证明我们考虑![image](https://cdn.nlark.com/yuque/__latex/9399b3296c58c6a7b0e4b278b98ac4c1.svg)定理在![image](https://cdn.nlark.com/yuque/__latex/cb6a001c04f839d69e0fd885fec6f7b6.svg)意义下即可

# 随机数
### Miller Rabin
```cpp
// 代码已提取到: code/技巧_Trick_2_5.cpp
```

### **<font style="color:rgb(38, 38, 38);">PollardRho</font>**
<font style="color:rgb(38, 38, 38);">如果 </font>![image](https://cdn.nlark.com/yuque/__latex/df378375e7693bdcf9535661c023c02e.svg)<font style="color:rgb(38, 38, 38);"> 是质数 (</font>_<font style="color:rgb(38, 38, 38);">MillerRabbin</font>_<font style="color:rgb(38, 38, 38);">判) 返回 </font>![image](https://cdn.nlark.com/yuque/__latex/df378375e7693bdcf9535661c023c02e.svg)_<font style="color:rgb(38, 38, 38);">     </font>_<font style="color:rgb(38, 38, 38);">否则返回 </font>![image](https://cdn.nlark.com/yuque/__latex/df378375e7693bdcf9535661c023c02e.svg)_<font style="color:rgb(38, 38, 38);"> </font>_<font style="color:rgb(38, 38, 38);">的随机一个</font>![image](https://cdn.nlark.com/yuque/__latex/ff9cb3f3599c3051cc11c3a3684cc807.svg)<font style="color:rgb(38, 38, 38);">的因子</font>

<font style="color:rgb(38, 38, 38);">复杂度 </font>![image](https://cdn.nlark.com/yuque/__latex/8bd2391fb9e9eab9ca048cdbdf2614f9.svg)

```cpp
// 代码已提取到: code/技巧_Trick_3_5.cpp
```

### 随机数生成
```cpp
// 代码已提取到: code/技巧_Trick_4_5.cpp
```
