# -*- coding: utf-8 -*-
import matplotlib as matplotlib
import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['savefig.dpi'] = 300 #图片像素
plt.rcParams['figure.dpi'] = 300 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
fig1 = plt.figure()
fig2 = plt.figure()
matplotlib.rcParams['agg.path.chunksize'] = 10000


ax1 = fig1.add_subplot(111)
ax2 = fig2.add_subplot(111)

X = []
Y = []
delta = 50
N = 6



with open('problem 16 Metropolis/'+str(delta)+'-10'+str(N)+'-x.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        X = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    X = np.array(X) # 将数据从list类型转换为array类型。


with open('problem 16 Metropolis/'+str(delta)+'-10'+str(N)+'-y.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Y = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    Y = np.array(Y) # 将数据从list类型转换为array类型。


n = 1500

ax1.scatter(np.delete(X, np.s_[0:n:1]), np.delete(Y, np.s_[0:n:1]), c='b', label='', s=0.05, alpha=0.5, marker='o')  # DLA模拟结果散点图
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_xlim(-5, 5)
ax1.set_ylim(-5, 5)
ax1.set_aspect('equal')
fig1.set_size_inches(6.4, 4.8, forward=True)
fig1.tight_layout()
fig1.savefig(str(delta)+'-10'+str(N)+'-1.png')


ax2.plot(np.delete(X, np.s_[0:n:1]), np.delete(Y, np.s_[0:n:1]), lw=0.5)
ax2.set_xlabel('X')
ax2.set_ylabel('Y')
ax2.set_aspect('equal')
ax2.set_xlim(-5, 5)
ax2.set_ylim(-5, 5)
fig2.set_size_inches(6.4, 4.8, forward=True)
fig2.tight_layout()
fig2.savefig(str(delta)+'-10'+str(N)+'-2.png')


