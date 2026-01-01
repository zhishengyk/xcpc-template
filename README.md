# 願いが叶う場所 - XCPC Algorithm Template Library

> 何度も背を向けてた

一个用于算法竞赛（ICPC/XCPC/OI）的代码模板库，包含常用数据结构、图论算法和数学公式。

## 📚 项目简介

本项目是一个精心整理的算法竞赛模板库，可以编译生成 PDF 手册方便打印携带。

**作者**: Nrtusea  
**学校**: 重庆移通学院  
**联系**: Urtusea@gmail.com

## 🎯 主要内容

### 数据结构 (Data Structure)
- 并查集（普通、可撤销、倍增）
- ST 表
- 树状数组 (Fenwick Tree)
- 线段树（懒标记、可持久化、Beats、李超树）
- 线段树分治
- 珂朵莉树 (Chtholly Tree)
- 01 字典树 (Bit Trie)
- PBDS 平衡树

### 图论 (Graph)
- LCA（最近公共祖先）
- 环计数
- Tarjan 算法（割边、割点、SCC、EBCC、VBCC）
- 2-SAT
- 虚树 (Virtual Tree)

### 数论 (Number Theory)
- 模运算 (ModInt)
- 素数筛
- 快速幂分块

### 组合数学 (Combinatorics)
- 组合数
- Möbius 变换
- Zeta 变换

### 线性代数 (Linear Algebra)
- 矩阵运算
- 异或空间

### 其他 (Misc)
- 概率论笔记
- 包含-排斥原理
- 和式变换技巧

## 🚀 使用方法

### 1. 生成 PDF 手册

```bash
# 需要安装 XeLaTeX 和 ctex 宏包
xelatex main.tex
xelatex main.tex  # 编译两次以生成目录
```

### 2. 日常训练

复制 `src/misc/main.cpp` 作为你的解题模板：

```cpp
void code() {
  // 在这里编写解题代码
}
```

### 3. 编译脚本

使用提供的 shell 脚本进行测试：

```bash
# 编译并运行测试
sh src/misc/main.sh

# 对拍脚本
sh src/misc/checker.sh

# SPJ 对拍脚本
sh src/misc/checker_spj.sh
```

## 📁 项目结构

```
.
├── main.tex                    # LaTeX 主文件
├── *.md                        # 概率论和数学笔记
├── src/
│   ├── data_structure/        # 数据结构
│   ├── graph/                 # 图论算法
│   ├── number_theory/         # 数论
│   ├── combinatorics/         # 组合数学
│   ├── linear_algebra/        # 线性代数
│   ├── string/                # 字符串
│   ├── xor_magic/             # 异或相关
│   └── misc/                  # 杂项工具
```

## 🛠️ 环境要求

- **C++ 编译器**: 支持 C++20 标准
- **LaTeX**: XeLaTeX + ctex 宏包（用于生成 PDF）
- **字体**: JetBrains Mono Nerd Font（已包含在项目中）

## 📝 性能测试

项目包含多个平台的性能测试结果：

- **Floyd 传递闭包**: 
  - Codeforces: 1421 ms
  - Atcoder: 476 ms
  - QOJ: 328 ms

- **基本运算**: 
  - Codeforces: 3015 ms
  - Atcoder: 1512 ms
  - QOJ: 1132 ms

更多测试数据请参考 `main.tex` 中的 Testing 章节。

## 📖 如何贡献

欢迎提交 Issue 和 Pull Request 来改进这个模板库！

## 📄 License

本项目仅供学习交流使用。

---

**願いが叶う場所** - 愿望实现的地方


