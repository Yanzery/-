# DES算法与差分攻击

标签（空格分隔）： 密码学实验

[TOC]

---
## 1. 实验目的
- 通过实验更进一步了解DES算法基本工作原理，体会并理解分组密码算法的混淆和扩散概念。
- 了解Sbox工作原理及效果。
- 了解DES的工作模式和填充方式。
- 了解差分攻击 的基本原理。

## 2. 实验题目
DES算法与差分攻击实验# DES算法与差分攻击

标签（空格分隔）： 密码学实验

[TOC]

---
## 1. 实验目的
- 通过实验更进一步了解DES算法基本工作原理，体会并理解分组密码算法的混淆和扩散概念。
- 了解Sbox工作原理及效果。
- 了解DES的工作模式和填充方式。
- 了解差分攻击 的基本原理。

## 2. 实验题目
DES算法与差分攻击实验
## 3. 实验原理与理论基础
### 3.1 DES算法
DES算法是一种典型的明文块加密标准——一种将固定长度的明文通过一系列复杂的操作变成同样长度的密文的算法。对DES而言，块长度为64位。同时，DES使用密钥来自定义变换过程，因此算法认为只有持有加密所用的密钥的用户才能解密密文。密钥表面上是64位的，然而只有其中的56位被实际用于算法，其余8位可以被用于奇偶校验，并在算法中被丢弃。因此，DES的有效密钥长度为56位，通常称DES的密钥长度为56位。

与其它加密算法相似，DES自身并不是加密的实用手段，而必须以某种工作模式进行实际操作。

DES同时使用了代换和置换两种技巧，整个过程分为两大部分：1，加密过程；2，子密钥产生过程。

![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%B8%80/DES%E5%8E%9F%E7%90%86%E5%9B%BE.jpg)

![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%B8%80/%E5%AF%86%E9%92%A5.jpg)

### 3.2差分攻击

	输入差分：△Y = Y ⊕  Y*

	输出差分：△S = S(Y) ⊕ S*(Y*)

## 4. 实验内容 
1. 编程实现DES算法
2. 通过改变DES算法明文和密文内容观察加密后输出统计结果
3. 实现生成指定差分的明文对，实现对特定差分输入的Sbox差分输出分布，观察DES S-box输入差分与密钥无关，输出差分与密钥相关特性。
4. 实现DES各种工作模式和填充方式，实现使用DES算法对数据文件加密(选做P124)
5. 实现简单的GUI界面


## 5. 实验结果 
### 5.1 差分分析
![](https://github.com/Yanzery/Pictures/raw/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%B8%80/%E5%B7%AE%E5%88%86%E5%88%86%E6%9E%90.jpg)

### 5.2 改变DES算法明文
![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%B8%80/%E6%94%B9%E5%8F%98%E6%98%8E%E6%96%87.jpg)

### 5.3 改变DES算法密钥
![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%B8%80/%E6%94%B9%E5%8F%98%E5%AF%86%E9%92%A5.jpg)

## 6. 实验结果分析

1. 通过这次实验掌握了DES算法的加解密流程以及差分攻击流程
2. DES的密钥表面上是64位，但是实际上只有56位用于算法，其余8位作为就校验位，在算法中会被丢弃(置换)。
3. 目前对DES算法的破译方法除了穷举法之外没有更有效的方法，穷举空间决定于密钥的长度，穷举空间为2^56.但随着技术的发展，破解DES的可能性越来越大，因此提出了三重DES算法。
## 3. 实验原理与理论基础
### 3.1 DES算法
DES算法是一种典型的明文块加密标准——一种将固定长度的明文通过一系列复杂的操作变成同样长度的密文的算法。对DES而言，块长度为64位。同时，DES使用密钥来自定义变换过程，因此算法认为只有持有加密所用的密钥的用户才能解密密文。密钥表面上是64位的，然而只有其中的56位被实际用于算法，其余8位可以被用于奇偶校验，并在算法中被丢弃。因此，DES的有效密钥长度为56位，通常称DES的密钥长度为56位。

与其它加密算法相似，DES自身并不是加密的实用手段，而必须以某种工作模式进行实际操作。

DES同时使用了代换和置换两种技巧，整个过程分为两大部分：1，加密过程；2，子密钥产生过程。

![](https://tupian-1255595569.cos.ap-guangzhou.myqcloud.com/%E5%9B%BE%E7%89%87/DES%E5%8E%9F%E7%90%86%E5%9B%BE.jpg?q-sign-algorithm=sha1&q-ak=AKIDtgJkz82ua4MT9erN0RgkdGpDQXVKnToy&q-sign-time=1543286763;1543287663&q-key-time=1543286763;1543287663&q-header-list=&q-url-param-list=&q-signature=75c0d8d607a4ddf7abce955244346b9305cff250)

![](https://tupian-1255595569.cos.ap-guangzhou.myqcloud.com/%E5%9B%BE%E7%89%87/%E5%AF%86%E9%92%A5.jpg?q-sign-algorithm=sha1&q-ak=AKIDtgJkz82ua4MT9erN0RgkdGpDQXVKnToy&q-sign-time=1543286780;1543287680&q-key-time=1543286780;1543287680&q-header-list=&q-url-param-list=&q-signature=f66a1e78c004ca9ac1c153161a95a5784ab00ac2)

### 3.2差分攻击

	输入差分：△Y = Y ⊕  Y*

	输出差分：△S = S(Y) ⊕ S*(Y*)

## 4. 实验内容 
1. 编程实现DES算法
2. 通过改变DES算法明文和密文内容观察加密后输出统计结果
3. 实现生成指定差分的明文对，实现对特定差分输入的Sbox差分输出分布，观察DES S-box输入差分与密钥无关，输出差分与密钥相关特性。
4. 实现DES各种工作模式和填充方式，实现使用DES算法对数据文件加密(选做P124)
5. 实现简单的GUI界面


## 5. 实验结果 
### 5.1 差分分析
![](https://tupian-1255595569.cos.ap-guangzhou.myqcloud.com/%E5%9B%BE%E7%89%87/%E5%B7%AE%E5%88%86%E5%88%86%E6%9E%90.jpg?q-sign-algorithm=sha1&q-ak=AKIDtgJkz82ua4MT9erN0RgkdGpDQXVKnToy&q-sign-time=1543286795;1543287695&q-key-time=1543286795;1543287695&q-header-list=&q-url-param-list=&q-signature=9f10003268e176941c70a3f3601a60e0d0eb1630)

### 5.2 改变DES算法明文
![](https://tupian-1255595569.cos.ap-guangzhou.myqcloud.com/%E5%9B%BE%E7%89%87/%E5%B7%AE%E5%88%86%E5%88%86%E6%9E%90.jpg?q-sign-algorithm=sha1&q-ak=AKIDtgJkz82ua4MT9erN0RgkdGpDQXVKnToy&q-sign-time=1543286795;1543287695&q-key-time=1543286795;1543287695&q-header-list=&q-url-param-list=&q-signature=9f10003268e176941c70a3f3601a60e0d0eb1630)

### 5.3 改变DES算法密钥
![](https://tupian-1255595569.cos.ap-guangzhou.myqcloud.com/%E5%9B%BE%E7%89%87/%E5%B7%AE%E5%88%86%E5%88%86%E6%9E%90.jpg?q-sign-algorithm=sha1&q-ak=AKIDtgJkz82ua4MT9erN0RgkdGpDQXVKnToy&q-sign-time=1543286795;1543287695&q-key-time=1543286795;1543287695&q-header-list=&q-url-param-list=&q-signature=9f10003268e176941c70a3f3601a60e0d0eb1630)

## 6. 实验结果分析

1. 通过这次实验掌握了DES算法的加解密流程以及差分攻击流程
2. DES的密钥表面上是64位，但是实际上只有56位用于算法，其余8位作为就校验位，在算法中会被丢弃(置换)。
3. 目前对DES算法的破译方法除了穷举法之外没有更有效的方法，穷举空间决定于密钥的长度，穷举空间为2^56.但随着技术的发展，破解DES的可能性越来越大，因此提出了三重DES算法。