# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
X = []


with open('cmake-build-debug/16807_ran.dat', 'r') as f:
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

'''   
with open('cmake-build-debug/Marsaglia_ran.dat', 'r') as f:
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
    '''
    



# 绘制散点图
plt.hist(X,bins=10)
plt.xlabel('X')
plt.ylabel('Y')
plt.savefig("16807.png")

