# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import math
import csv
#figsize(12.5, 4) # 设置 figsize
from matplotlib.ticker import FuncFormatter
import collections
#from IPython.core.pylabtools import figsize # import figsize

plt.rcParams['savefig.dpi'] = 300 #图片像素
plt.rcParams['figure.dpi'] = 300 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
fig1 = plt.figure()
fig2 = plt.figure()

ax1 = fig1.add_subplot(111)
ax2 = fig2.add_subplot(111)

step = 0.0000001  # 每个lambda取值之间的间隔
max = -0.31831  # lambda的取值区间
min = -0.31832

X = []
Y = []
X1 = []
Y1 = []
flag = 0
i = 0
temp1 = []
temp = 0

csv_file = csv.reader(open('problem 12/7-7.dat', 'r'))
for line in csv_file:
    [tempX, tempY] = line
    i += 1
    if i % 100 == 0 and i != 0:  # 每读100行数据，进行统计（因为C程序输出后100个迭代值）
        temp2 = set(temp1)  # 因为此步骤考虑不同lambda值对应的输出x值中的不同结果数，
                            # 故变为集合形式，使其中只有不同的元素，然后其长度即代表所求
        temp = len(temp2)
        Y1.append(len(temp2))  # 记录不同lambda值对应的输出x值中的不同结果数
        temp1 = []
    else:
        temp1.append(float(tempY))

    X.append(float(tempX))  # lambda 的值
    Y.append(float(tempY))  # 与相应lambda对应的输出结果


X = np.array(X)
Y = np.array(Y)
Yc = 0.5*np.ones(len(Y))


ax1.scatter((X - min), Y, c='b', label='', s=0.08, alpha=0.5, marker='o')  # x-lambda散点图
#ax1.plot((X - min), Yc, '--', lw=0.5, color='r')
ax1.set_xlabel('lambda-('+str(min)+')')
ax1.set_ylabel('X')
ax1.set_xlim(min-min, max-min)
#ax1.set_ylim(0.4, 0.6)
def formatnum(x, pos):
    return '$%1.2f$x$10^{-5}$' % (x/0.00001)
formatter = FuncFormatter(formatnum)
ax1.xaxis.set_major_formatter(formatter)
for label in ax1.xaxis.get_ticklabels():
    label.set_rotation(10)
    label.set_fontsize(7)
fig1.savefig("1.png")

X1 = np.arange(min, max + step/2, step)

ax2.plot(X1-max, Y1, lw=0.3, label='different number of x')  # x不同结果数-lambda折线图
ax2.legend(loc=2)
ax2.set_xlabel('lambda-('+str(max)+')')
ax2.set_ylabel('different number of x')
ax1.set_xlim(min-max, max-max)
def formatnum(x, pos):
    return '$%1.2f$x$10^{-5}$' % (x/0.00001)
formatter = FuncFormatter(formatnum)
ax2.xaxis.set_major_formatter(formatter)
for label in ax2.xaxis.get_ticklabels():
    label.set_rotation(15)
    label.set_fontsize(7)
fig2.savefig("2.png")

if max <= 0:
    Y1.reverse()  # 当参数lambda<0时，需对Y1 List 进行排序上的反转，>0时此步骤不运行

print("*******************************************************")
flag = 0

for i in Y1:   # 输出 lambda值及其对应的输出结果中的x的种类数（用来找分岔值）
    if flag < 1001:
        print(max - flag*step, "\t", i)  # 前面为lambda值，后面为其对应的输出结果中的x的结果数
    flag += 1


X = [-0.3183122, -0.8332658, -0.8586088, -0.8640842, -0.86525894, -0.8655107]
for j in range(4):
    print((X[j+1]-X[j])/(X[j+2]-X[j+1]))

print("*******************************************************")

X = [0.7199599, 0.8332658, 0.8586088, 0.8640842, 0.865259, 0.8655107]
for j in range(4):
    print((X[j+1]-X[j])/(X[j+2]-X[j+1]))
