# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
#from IPython.core.pylabtools import figsize # import figsize
#figsize(12.5, 4) # 设置 figsize
plt.rcParams['savefig.dpi'] = 300 #图片像素
plt.rcParams['figure.dpi'] = 300 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400

fig = plt.figure()
ax = fig.add_axes([0.13, 0.1, 0.8, 0.8])
X = []
Y = []

with open('cmake-build-debug/ranx.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
            #pass
        tmp = [float(i) for i in lines.split(',')] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        X.append(tmp)  # 添加新读取的数据
        #pass
    X = np.array(X) # 将数据从list类型转换为array类型。
pass

with open('cmake-build-debug/rany.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
            #pass
        tmp = [float(i) for i in lines.split(',')] # 将整行数据分割处理，如果分割符是空格，括号里就不用传入参数，如果是逗号， 则传入‘，'字符。
        Y.append(tmp)  # 添加新读取的数据
        #pass
    Y = np.array(Y) # 将数据从list类型转换为array类型。
pass
    


# 绘制散点图
ax.scatter(X, Y, s = 0.1, linewidths = None)    #画散点图
ax.set_aspect('equal')
ax.set_xlabel('X')
ax.set_ylabel('Y')
plt.savefig("random(x,y)-1.png")

