# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import math

plt.rcParams['savefig.dpi'] = 300 #图片像素
plt.rcParams['figure.dpi'] = 300 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
fig1 = plt.figure()
fig2 = plt.figure()
fig3 = plt.figure()
max = 500  #团簇位置信息二维矩阵半径
ax1 = fig1.add_subplot(111)
ax2 = fig2.add_subplot(111)
ax3 = fig3.add_subplot(111)



X = []
Y = []
y = []
box = []
sandbox = []
xbox = []
xsandbox = []

xtbox = []
xtsandbox = []


with open('problem 13/p-500-104-1.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        y = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    y = np.array(y) # 将数据从list类型转换为array类型。


with open('problem 13/box-5-205.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        box = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    box = np.array(box) # 将数据从list类型转换为array类型。


with open('problem 13/sandbox-5-205.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        sandbox = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    sandbox = np.array(sandbox) # 将数据从list类型转换为array类型。

for i in range(pow(2*max+1, 2)):
    if y[i] != 0:
        X.append(i % (2*max+1)-max)
        Y.append(max - i/(2*max+1))

#box = np.delete(box, 10)   #是否排除盒计数法最后一个数据点
print(box)

box = np.log(box)     # 盒计数法横轴数据点生成
xbox = np.ones(len(box))
for i in range(len(box)):
    xbox[i] = math.log(pow(2, i))

sandbox = np.log(sandbox)  # Sandbox法横轴数据点生成
xsandbox = np.ones(60)
for i in range(60):
    xsandbox[i] = math.log(5 + i*5)


[ab, bb] = np.polyfit(xbox, box, 1)   # 两计算分形维数方法的线性拟合
[asb, bsb] = np.polyfit(xsandbox, sandbox, 1)
print([ab, bb])
print([asb, bsb])


ax1.scatter(X, Y, c='b', label='', s= 1, alpha=0.5, marker='o')  # DLA模拟结果散点图
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_xlim(-max/2, max/2)
ax1.set_ylim(-max/2, max/2)
ax1.set_aspect('equal')
fig1.savefig("1.png")


ax2.scatter(xbox, box, c='b', label='Computing data', s= 1, alpha=0.5, marker='o')  # 盒计数法对数图
ax2.plot(xbox, ab*xbox+bb, lw=0.5, color='r', label='Linear Fitting Curve')
ax2.set_xlabel(r'$ln(1/ \epsilon)$')
ax2.set_ylabel(r'$lnN$')
ax2.legend(loc=2)
ax2.text(0, 9, r"$lnN=$"+str(ab)+r'$\times ln(1/ \epsilon)+$'+str(bb), fontsize=8, color="black")
fig2.savefig("2.png")

ax3.scatter(xsandbox, sandbox, c='b', label='Computing data', s= 1, alpha=0.5, marker='o')  # sandbox对数图
ax3.plot(xsandbox, asb*xsandbox+bsb, lw=0.5, color='r', label='Linear Fitting Curve')
ax3.set_xlabel(r'$lnr$')
ax3.set_ylabel(r'$lnN$')
ax3.text(1.5, 9, r"$lnN=$"+str(asb)+r'$\times ln(r)+$'+str(bsb), fontsize=8, color="black")
ax3.legend(loc=2)
fig3.savefig("3.png")



