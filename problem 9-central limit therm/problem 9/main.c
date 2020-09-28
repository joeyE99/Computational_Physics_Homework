//
//  main.c
//  problem 9
//
//  Created by 杨旭鹏 on 2019/9/28.
//  Copyright © 2019 杨旭鹏. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define a 16807
#define b 0
#define m 2147483647
#define r (m%a)
#define q (m/a)
#define Pi 3.1415926
#define k 600
#define GETMATELEM(base,i,j,imax) ((*(base + i * imax + j))) //取二维数组元素



int my_filewriter_double(char str[],double num[],int n){
    FILE * fp;
    fp = fopen(str,"w+");

    for(int i=0;i<(n-1);i++)
    {
        fprintf(fp,"%lf,",num[i]);

    }
    fprintf(fp,"%lf",num[n-1]);    //最后一个数据后不加 ","
    fclose(fp);
    return 0;
}




// Schrage 方法产生随机数
int my_schrage(int seed){
    int x;
    if(seed == m-1){
        if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
            x = m + (b-a) % m;
        }
        else   x =  (b-a) % m;

    }
    else x = ((a * (seed % q) - r * (seed /  q)) + b % m ) % m;  //递推式
    return x;
}


int my_function1(double p[],int N,int n){
    double beta; //存放统计量计算结果
    int x = 1; //16807方法递推数列，初始种子值为1
    double y;  //y为(0,1)均匀抽取的点
    int flag = 0;
    for(int i = 0;i<k;i++){  //概率分布数组初始化
        p[i] = 0;
    }
    for(;flag<N;){  //控制计算次数
        beta = 0;
        for(int i = 0;i<n;i++){  //控制每次计算时抽取的点数
            x = my_schrage(x);   //随机数递推数列
            if(x >= 0) y = (double)x/m;
            else y = (double)(x+m)/m;  //y为(0,1)均匀抽取的点
            if(y <= 0.5){
                beta += (sqrt(2*y)-1)/n;
            }
            else beta += (1-sqrt(2-2*y))/n;  //直接抽样法并计算得到第i次抽样结果的平均值
        }
        beta = beta*sqrt(6*n);  //计算统计量
        
        if(beta <= 3 && beta >= -3){   //统计统计量分布
            p[(int) floor( (beta+3)/6*k) ] += (double)1/N  ;
            flag++;
        }
    }
    return 0;
}

int my_function2(double p[],int N,int n){
    double beta; //存放统计量计算结果
        int x = 1; //16807方法递推数列，初始种子值为1
        double y;  //y为(0,1)均匀抽取的点
        int flag = 0;
        for(int i = 0;i<k;i++){  //概率分布数组初始化
            p[i] = 0;
        }
        for(;flag<N;){  //控制计算次数
            beta = 0;
            for(int i = 0;i<n;i++){  //控制每次计算时抽取的点数
                x = my_schrage(x);   //随机数递推数列
                if(x >= 0) y = (double)x/m;
                else y = (double)(x+m)/m;   //y为(0,1)均匀抽取的点
                beta += (y+1)/n;    //直接抽样法并计算得到第i次抽样结果的平均值
            }
            beta = (beta-1.5)*sqrt(12*n);   //计算统计量
            if(beta <= 3 && beta >= -3){  //统计统计量分布
                p[(int) floor( (beta+3)/6*k) ] += (double)1/N  ;
                flag++;
            }
        }
        return 0;
}



int my_function3(double p[],int N,int n){
    double beta; //存放统计量计算结果
    int x = 1; //16807方法递推数列，初始种子值为1
    double y;  //y为(0,1)均匀抽取的点
    int flag = 0;
    for(int i = 0;i<k;i++){   //概率分布数组初始化
        p[i] = 0;
    }
    for(;flag<N;){   //控制计算次数
        beta = 0;
        for(int i = 0;i<n;i++){  //控制每次计算时抽取的点数
            x = my_schrage(x);   //随机数递推数列
            if(x >= 0) y = (double)x/m;
            else y = (double)(x+m)/m;   //y为(0,1)均匀抽取的点
            if(y <= 0.5){    //直接抽样法并计算得到第i次抽样结果的平均值
                beta += (sqrt(2*y)-1)/n;
            }
            else beta += (2*y-1)/n;
        }
        beta = 12*(beta-(double)1/12)*sqrt(n)/sqrt(35);   //计算统计量
        
        if(beta <= 3 && beta >= -3){   //统计统计量分布
            p[(int) floor( (beta+3)/6*k) ] += (double)1/N  ;
            flag++;
        }
    }
    return 0;
}



int main(int argc, const char * argv[]) {
    int N;    //总计算次数
    int n;   //每此计算所选点数
    double p1[k];
    double p2[k];
    double p3[k];
    char str[50];
    printf("请输入您所需的计算次数：");
    while (!scanf("%d",&N)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需的计算次数：");
    }
    
    printf("请输入您每次计算所用的点数：");
    while (!scanf("%d",&n)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您每次计算所用的点数：");
    }

    if(N*n >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");
    
    //my_function1(p1,N,n);
    my_function2(p2, N, n);
    //my_function3(p3, N, n);
    
   // my_filewriter_double("function1.txt", p1, k);
    my_filewriter_double("function2.txt", p2, k);
    //my_filewriter_double("function3.txt", p3, k);
    
    return 0;
}
