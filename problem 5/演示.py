# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
plt.rcParams['savefig.dpi'] = 1000 #图片像素
plt.rcParams['figure.dpi'] = 1000 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400

fig = plt.figure()
ax = Axes3D(fig)
X = []
Y = []
Z = []
'''
with open('problem 5/ranx_16807.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
            pass
        tmp = [float(i) for i in lines.split(',')] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        X.append(tmp)  # 添加新读取的数据
        pass
    X = np.array(X) # 将数据从list类型转换为array类型。
pass

    
with open('problem 5/rany_16807.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
            pass
        tmp = [float(i) for i in lines.split(',')] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        Y.append(tmp)  # 添加新读取的数据
        pass
    Y = np.array(Y) # 将数据从list类型转换为array类型。
pass

with open('problem 5/ranz_16807.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
            pass
        tmp = [float(i) for i in lines.split(',')] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        Z.append(tmp)  # 添加新读取的数据
        pass
    Z = np.array(Z) # 将数据从list类型转换为array类型。
pass
    
       


# 绘制散点图
ax.scatter(X, Y, Z,s=0.00001)    #画散点图
#ax.view_init(elev=90,azim=45)
ax.set_aspect('equal')   #设置三个坐标轴比例尺相同
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.savefig("scatter.png")
'''
Z = []
A = []

with open('problem 5/op.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        temp = [float(i) for i in lines.split()] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        A.append(temp)
    A = np.array(A) # 将数据从list类型转换为array类型。
pass


with open('problem 5/hist.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        temp = [float(i) for i in lines.split()] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        Z.append(temp)
    Z = np.array(Z) # 将数据从list类型转换为array类型。
pass


Z = Z.reshape(50,50)
A = A.reshape(50,50)
Z1 = Z-A


X = np.linspace(-0.99, 0.99, 50)
Y = np.linspace(-0.99, 0.99, 50)
x, y = np.meshgrid(X, Y)
surf = ax.plot_surface(x, y, Z1, rstride=1, cstride=1, cmap='rainbow')

ax.set_aspect('equal')   #设置三个坐标轴比例尺相同
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('P')
ax.set_zticks([-0.006, -0.004, -0.002, 0, 0.001])
#ax.set_zticks([])
ax.set_yticks([-1, -0.5, 0, 0.5, 1])
ax.set_xticks([-1, -0.5, 0, 0.5, 1])
plt.colorbar(surf, shrink = 0.5)
#ax.view_init(elev=90,azim=45)
plt.savefig("p.png")