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
fig4 = plt.figure()

ax1 = fig1.add_subplot(111)
ax2 = fig2.add_subplot(111)
ax3 = fig3.add_subplot(111)
ax4 = fig4.add_subplot(111)

v = []
T = []
vcul = []
Ed = []
Edcul = []
XT = []
delta = 0.01
n = 4
N = 7
step = 1000

XT = np.arange(0, 10**N + step/2, step)

with open('problem 17/v.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        v = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    v = np.array(v) # 将数据从list类型转换为array类型。


with open('problem 17/T.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        T = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    T = np.array(T) # 将数据从list类型转换为array类型。

with open('problem 17/Ed.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Ed = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    Ed = np.array(Ed) # 将数据从list类型转换为array类型。


vcul = (10**n)*0.04*math.sqrt(3/(2*math.pi))*np.exp(-3*np.power(np.arange(-2, 2, 0.05), 2)/2)
Edcul = (10**N/step)*0.04*np.exp(-3*np.arange(0, 4, 0.05))*3


ax1.hist(v, np.arange(-2, 2 + 0.04/2, 0.04), label=r'Actual distribution of $v$')  # DLA模拟结果散点图
ax1.plot(np.arange(-2, 2, 0.05), vcul, label=r'Theoretical distribution of $v$')
ax1.set_xlabel('v')
ax1.set_ylabel('Count')
ax1.legend(loc=1)
ax1.set_ylim(0, 350)
#ax1.set_aspect('equal')
fig1.savefig(str(delta)+'-10'+str(n)+'-10'+str(N)+'-v.png')

ax2.scatter(XT, T, s=0.1)
ax2.set_xlabel('N')
ax2.set_ylabel('<T>')
#ax2.set_aspect('equal')
fig2.savefig(str(delta)+'-10'+str(n)+'-10'+str(N)+'-T.png')


ax3.scatter(XT, Ed, s=0.1, label=r'$Ed$')
ax3.set_xlabel('N')
ax3.set_ylabel('Ed')
#ax3.set_aspect('equal')
fig3.savefig(str(delta)+'-10'+str(n)+'-10'+str(N)+'-Ed.png')

ax4.hist(Ed, np.arange(0, 4 + 0.04/2, 0.04), label=r'Actual distribution of $E_{d}$')  # DLA模拟结果散点图
ax4.plot(np.arange(0, 4, 0.05), Edcul, lw=1, label=r'Theoretical distribution of $E_{d}$')
ax4.set_xlabel('Ed')
ax4.set_ylabel('Count')
ax4.set_xlim(0, 4)
ax4.legend(loc = 1)
fig4.savefig(str(delta)+'-10'+str(n)+'-10'+str(N)+'-Ed-2.png')
