[TOC]

# RSA算法 #
## 实验目的 ##


1. 了解公钥算法基本原理和RSA算法的原理
2. 了解RSA算法在数据加密和数字签名中的应用
3. 了解RSA算法中大合数分解的困难性，从而理解单向函数的内涵

## 实验题目 ##
RSA算法实现

## 实验内容及要求 ##

1. 编程实现素数的选择判断
2. 编程实现模逆算法
3. 编程实现快速模指运算
4. 编程实现RSA算法
5. 编程实现利用RSA进行数据加解密
6. 实现利用RSA对较大数据行进加解密 
7. 实现简单的GUI界面

## 实验主要仪器设备和材料 ##

计算机、网络环境、eclipse

## 实验原理与理论基础 ##
###  1. 公钥和私钥的产生

假设Alice想要通过一个不可靠的媒体接收Bob的一条私人信息。她可以用以下的方式来产生一个公钥和一个私钥：

RSA体制生成密钥的过程可以简单描述如下：
   

1. 生成两个大素数p和q。
2. 计算这两个素数的乘积n=p×q。
3. 计算欧拉函数φ(n)=(p-1)(q-1)。
4. 选择一个随机数e满足1<e<φ(n)，并且e和φ(n)互质，即gcd(e, φ(n))=1。
5. 计算ed=1 mod φ(n)。同余：ed-1能被φ(n)整除
6. 保密d，p和q，公开n和e
7. 这里的（n, e）就是公开的加密密钥。（n，d）就是私钥。

Alice將她的公钥(N,e)传給Bob，而將她的私钥(N,d)藏起來。

### 2. 加密消息

假设Bob想给Alice送一个消息m，他知道Alice产生的N和e。他使用起先与Alice约好的格式将m转换为一个小于N的整数n，比如他可以将每一个字转换为这个字的Unicode码，然后将这些数字连在一起组成一个数字。假如他的信息非常长的话，他可以将这个信息分为几段，然后将每一段转换为n。用下面这个公式他可以将n加密为c：

**n^e ≡ c(mod N)**
                                                               

  计算c并不复杂。Bob算出c后就可以将它传递给Alice。

### 3. 解密消息

Alice得到Bob的消息c后就可以利用她的密钥d来解码。她可以用以下这个公式来将c转换为n：
**c^d ≡ n(mod N)**
                                                               

得到n后，她可以将原来的信息m重新复原。
解码的原理是

**c^d ≡ n^(ed)(mod N)**
                                                               

以及ed ≡ 1 (mod p-1)和ed ≡ 1 (mod q-1)。由费马小定理可证明（因为p和q是质数）

**n^(ed) ≡ n(mod p) 和 n^(ed) ≡ n(mod q)**
                                              

这说明（因为p和q是不同的质数，所以p和q互质）

**n^(ed) ≡ n(mod pq)**

## 实验结果 ##

### 1. 判断素数

![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%BA%8C/%E7%B4%A0%E6%95%B0%E7%9A%84%E9%80%89%E6%8B%A9%E5%88%A4%E6%96%AD.png)
![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%BA%8C/%E7%B4%A0%E6%95%B0.png)
### 2. 模逆运算

![](https://github.com/Yanzery/Pictures/raw/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%BA%8C/%E6%A8%A1%E6%8B%9F%E7%AE%97%E6%B3%95.png)
### 3. 模指运算

![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%BA%8C/%E5%BF%AB%E9%80%9F%E6%A8%A1%E6%8C%87%E8%BF%90%E7%AE%97.png)
### 4. 利用RSA算法对数据进行加密及解密
![](https://raw.githubusercontent.com/Yanzery/Pictures/master/%E5%AF%86%E7%A0%81%E5%AD%A6%E5%9B%BE%E7%89%87/%E5%AE%9E%E9%AA%8C%E4%BA%8C/RSA%E7%AE%97%E6%B3%95%E5%8A%A0%E5%AF%86.png)

## 实验结果分析 ##
1. RSA是公钥加解密，所以要保证私钥是保密的，并且保证公钥的真实性，确保第三方的可信性，另外RSA的安全性依赖于“大数分解和素性检测”，为了安全性，n必须是大素数；
2. 相对DES的对称加密算法，公钥加密方案的密钥长度比对称加密的密钥长，RSA要进行大素数的运算，公钥加密比对称密钥加密的速度慢几个数量级；
3. 公钥密码系统的主要目的是提供保密性，它不能提供数据源认证和数据完整性，数据源认证和数据完整性要由其他技术来提供如消息认证码技术、数字签名技术等。

                                                         