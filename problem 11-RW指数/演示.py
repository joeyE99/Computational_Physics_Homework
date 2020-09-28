# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import math
#from IPython.core.pylabtools import figsize # import figsize
#figsize(12.5, 4) # 设置 figsize
plt.rcParams['savefig.dpi'] = 300 #图片像素
plt.rcParams['figure.dpi'] = 300 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
fig1 = plt.figure()
fig1t = plt.figure()
fig2 = plt.figure()
fig3 = plt.figure()

ax1 = fig1.add_subplot(111)
ax1t = fig1t.add_subplot(111)
ax2 = fig2.add_subplot(111)
ax3 = fig3.add_subplot(111)


N = 1000   # 每个粒子行走的步数N
n = 6     # 模拟的粒子数量，单位为10^n
X = []    # 存储步数N
Y1 = []   # 存储一维每一步回到原点的概率
Y2 = []   # 存储二维每一步回到原点的概率
Y3 = []   # 存储三维每一步回到原点的概率
Yt1 = np.zeros(N)   # 存储一维每一步回到原点的理论概率
Yt2 = np.zeros(N)   # 存储二维每一步回到原点的理论概率
Yt3 = np.zeros(N)   # 存储三维每一步回到原点的理论概率

with open('problem 11/1000step-1p_10'+str(n)+'.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Y1 = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    Y1 = np.array(Y1) # 将数据从list类型转换为array类型。

with open('problem 11/1000step-2p_10'+str(n)+'.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Y2 = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    Y2 = np.array(Y2) # 将数据从list类型转换为array类型。


with open('problem 11/1000step-3p_10'+str(n)+'.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Y3 = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    Y3 = np.array(Y3) # 将数据从list类型转换为array类型。


X = np.arange(1, N+1./2, 1)  # 每一步的数值N

print(np.shape(X))
print(np.shape(Y1))
print(np.shape(Y2))
print(np.shape(Y3))

'''
for i in range(N):   # 计算一维情况下理论上每一步对应的回到原点的概率
    if (i+1) % 2 == 0:
        Yt1[i] = math.factorial((i+1))/(pow(math.factorial((i+1)/2), 2))*pow(0.5, (i+1))
    else:
        Yt1[i] = 0

for i in range(N):   # 计算二维情况下理论上每一步对应的回到原点的概率
    if (i+1) % 2 == 0:
        for j in range(round((i+1)/2)+1):
            Yt2[i] += math.factorial(i+1)/pow(math.factorial(j)*math.factorial(round((i+1)/2)-j), 2)*pow(1./4, (i+1))
    else:
        Yt2[i] = 0

for i in range(N):  # 计算三维情况下理论上每一步对应的回到原点的概率
    if (i+1) % 2 == 0:
        for j in range(round((i+1)/2)+1):
            for k in range(round((i+1)/2)-j+1):
                Yt3[i] += math.factorial(i + 1) / (pow(math.factorial(j) * math.factorial(k) * math.factorial(round((i + 1) / 2) - j - k), 2)) * pow(
                    1./6, (i + 1))
    else:
        Yt3[i] = 0
'''

ax1.scatter(X, Y1, c='r', label='<PN(0)>', s=2, alpha=0.5, marker='x')   # 一维情况下每一步对应的回到原点的概率散点图 数值模拟VS理论
#ax1.scatter(X, Yt1, c='b', label='Theoretical <PN(0)>', s=2, alpha=0.5)
ax1.set_xlabel('N')
ax1.set_ylabel('P')
ax1.legend(loc=1)
fig1.savefig("1.png")


ax2.scatter(X, Y2, c='r', label='<PN(0)>', s=2, alpha=0.5, marker='x')   # 二维情况下每一步对应的回到原点的概率散点图 数值模拟VS理论
#ax2.scatter(X, Yt2, c='b', label='Theoretical <PN(0)>', s=2, alpha=0.5)
ax2.set_xlabel('N')
ax2.set_ylabel('P')
ax2.legend(loc=1)
fig2.savefig("2.png")


ax3.scatter(X, Y3, c='r', label='<PN(0)>', s=2, alpha=0.5, marker='x')   # 三维情况下每一步对应的回到原点的概率散点图 数值模拟VS理论
#ax3.scatter(X, Yt3, c='b', label='Theoretical <PN(0)>', s=2, alpha=0.5)
ax3.set_xlabel('N')
ax3.set_ylabel('P')
ax3.legend(loc=1)
fig3.savefig("3.png")

for i in range(500):   # 将每个维度上奇数步概率为0的数据删掉
    X = np.delete(X, i)
    Y1 = np.delete(Y1, i)
    Y2 = np.delete(Y2, i)
    Y3 = np.delete(Y3, i)

print(np.polyfit(np.log(X), np.log(Y1), 1))   # 对每一维度上的指数值进行线性拟合
print(np.polyfit(np.log(X), np.log(Y2), 1))
print(np.polyfit(np.log(X), np.log(Y3), 1))