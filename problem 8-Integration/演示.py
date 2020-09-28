# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
#from IPython.core.pylabtools import figsize # import figsize
#figsize(12.5, 4) # 设置 figsize
import matplotlib.ticker as ticker
plt.rcParams['savefig.dpi'] = 300 #图片像素
plt.rcParams['figure.dpi'] = 300 #分辨率
# 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
fig = plt.figure()
ax1 = fig.add_subplot(111)
X = [3, 4, 5, 6, 7, 8]
Y = 1/np.sqrt(np.power(10, X))
Y1 = [0.010389, 0.003110, 0.004482, 0.001899, 0.000215, 0.000024]
Y2 = [0.010890, 0.019573, 0.004132, 0.000048, 0.000215, 0.000152]

ax1.plot(X, Y, '-o', color = 'red', label='1/sqrt(N)')
ax1.plot(X, Y1, '-o', color = 'blue', label='difference of integration 1')
ax1.plot(X, Y2, '-o', color = 'yellow', label='difference of integration 2')
ax1.legend(loc=1)

formatter = ticker.FormatStrFormatter('10^%d')
ax1.xaxis.set_major_formatter(formatter)
ax1.set_ylabel('difference')
plt.xlabel('N')


plt.savefig("2.png")

