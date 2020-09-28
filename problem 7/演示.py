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
ax1 = fig.add_subplot(111)

with open('problem 7/F.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Y = [float(i) for i in lines.split(',')] # 将整行数据分割处理
    Y = np.array(Y) # 将数据从list类型转换为array类型。


with open('problem 7/orip.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        oY = [float(i) for i in lines.split(',')] # 将整行数据分割处理
    oY = np.array(oY)  # 将数据从list类型转换为array类型。


X = np.arange(2900, 3014)


plt.bar(x=X, height=Y, width=1, label='actual probability')
ax1.legend(loc=1)
ax1.set_ylabel('actual probability')
ax1.set_ylim([0, 0.12])

ax2 = ax1.twinx()

ax2.plot(X, oY, 'r', label='original probability')
ax2.legend(loc=2)
ax2.set_ylabel('original probability')
ax2.set_ylim([0, 0.12])

plt.xlabel('Energy')


plt.savefig("1.png")

