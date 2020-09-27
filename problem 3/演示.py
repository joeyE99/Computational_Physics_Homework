# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from IPython.core.pylabtools import figsize # import figsize
figsize(7, 7) # 设置 figsize
plt.rcParams['savefig.dpi'] = 1000 #图片像素
plt.rcParams['figure.dpi'] = 1000 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400

fig = plt.figure()
ax = Axes3D(fig)
theta = []
phi = []

with open('cmake-build-debug/theta.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
            pass
        tmp = [float(i) for i in lines.split(',')] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        theta.append(tmp)  # 添加新读取的数据
        pass
    theta = np.array(theta) # 将数据从list类型转换为array类型。
pass

    
with open('cmake-build-debug/phi.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
            pass
        tmp = [float(i) for i in lines.split(',')] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        phi.append(tmp)  # 添加新读取的数据
        pass
    phi = np.array(phi) # 将数据从list类型转换为array类型。
pass
    
    
    

X = np.sin(theta) * np.cos(phi)
Y= np.sin(theta) * np.sin(phi)
Z = np.cos(theta)


# 绘制散点图
ax.scatter(X, Y, Z,s=5)    #画散点图
#ax.view_init(elev=90,azim=45)
ax.set_aspect('equal')   #设置三个坐标轴比例尺相同
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.savefig("1.png")

