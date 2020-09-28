# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
#from IPython.core.pylabtools import figsize # import figsize
#figsize(12.5, 4) # 设置 figsize
plt.rcParams['savefig.dpi'] = 300 #图片像素
plt.rcParams['figure.dpi'] = 300 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
fig1 = plt.figure()
fig2 = plt.figure()
fig = plt.figure()
pfig = plt.figure()
figvar = plt.figure()
ax1 = fig1.add_subplot(111)
ax2 = fig2.add_subplot(111)
ax = fig.add_subplot(111)
pax = pfig.add_subplot(111)
axvar = figvar.add_subplot(111)

n = 100000
N = 1000
dt = 0.1
w = 100
k = 0.5

X = []
Y1 = []
Y2 = []
p = []
var = []
Y1t = []
Y2t = []

with open('problem 10/w='+str(w)+'/'+str(n)+'evenx_'+str(k)+'.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Y1 = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    Y1 = np.array(Y1) # 将数据从list类型转换为array类型。

with open('problem 10/w='+str(w)+'/'+str(n)+'evenx2_'+str(k)+'.dat', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        Y2 = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    Y2 = np.array(Y2) # 将数据从list类型转换为array类型。


with open('problem 10/'+str(100000)+'p.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        p = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    p = np.array(p) # 将数据从list类型转换为array类型。


with open('problem 10/'+str(10000)+'var.txt', 'r') as f:
    while True:
        lines = f.readline() # 整行读取数据
        if not lines:
            break
        var = [float(i) for i in lines.split(',')]  # 将整行数据分割处理
    var = np.array(var) # 将数据从list类型转换为array类型。


Y2 = np.sqrt(Y2*Y2)
X = np.arange(0, N * dt, dt)
px = np.arange(-100, 101, 1)
varx = np.arange(0, 10000, 1)
print(np.shape(px))
py = 1/np.sqrt(2*np.pi*875.265)*np.exp(-np.power(px-0.56124, 2)/(2*875.265))
Y1t = k*np.sin(X*w/2)*np.sin((X+dt)/2*w)/np.sin(dt*w/2)
Y2t = X/dt*(1-k*k/2)+k*k*(  np.power(  np.sin(w*X/2)*np.sin((X+dt)/2*w)/np.sin(w*dt/2), 2) + np.sin(w*X)*np.cos((X+dt)*w)/np.sin(w*dt)/2 )


ax1.plot(X, Y1, 'r', label='Actual <X(t)>', lw=0.5)
#ax1.plot(X, Y1t, 'b', label='Theoretical <X(t)>', lw=0.5)
ax1.set_xlabel('t(s)')
ax1.set_ylabel('<X(t)>')
ax1.legend(loc=3)
fig1.savefig("1.png")

axvar.plot(varx, var, 'b', label='<X(t)>', lw=0.3)
axvar.set_xlabel('t(s)')
axvar.set_ylabel('var(t)')
figvar.savefig("var.png")


ax2.plot(X, Y2, 'r', label='Actual <X^2(t)>', lw=0.5)
ax2.plot(X, Y2t, 'b', label='Theoretical <X^2(t)>', lw=0.5)
ax2.set_xlabel('t(s)')
ax2.set_ylabel('<X^2(t)>')
ax2.legend(loc=2)
fig2.savefig("2.png")

pax.bar(px, p, width=1.1, label='Actual probability')
pax.plot(px, py, 'r', label='Theoretical probability')
pax.set_xlabel('x(t='+str(N*dt)+')')
pax.set_ylabel('probability')
pax.legend(loc=1)
pfig.savefig("p.png")
'''
Y = [[]]
Y = np.array(Y)

for i in range(n):
    with open('problem 10/'+str(i+1)+'RW.dat', 'r') as f:
        while True:
            lines = f.readline()  # 整行读取数据
            if not lines:
                break
            Y = np.append(Y, [[float(i) for i in lines.split(',')]])  # 将整行数据分割处理

Y = Y.reshape(n, N)

plt_label = 0
for link in range(n):
    ax.plot(X, Y[link], label='particle'+str(plt_label), lw=0.3)
    plt_label += 1

ax.set_xlabel('t(s)')
ax.set_ylabel('X(t)')
fig.savefig("3.png")
'''