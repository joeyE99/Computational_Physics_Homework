//
//  main.c
//  problem 8
//
//  Created by 杨旭鹏 on 2019/9/26.
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



//利用/dev/random 产生"真"随机数
int my_realrandom(int ran[],int n){
    FILE * fp1 = fopen("/dev/random","r");
    for(int i=0;i<n;i++){
        fread(&ran[i], 1, 4, fp1);
    }
    fclose(fp1);
    return 0;
}


// Schrage 方法产生随机数
int my_schrage(double ran[],int seed,int n){
    for (int i = 0; i < n - 1; i++) {
        if (seed >= 0) {
            ran[i] = (seed / (double) m);
        } else {
            ran[i] = ((seed + m) / (double) m);
        }
        if(seed == m-1){
            if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                seed = m + (b-a) % m;
            }
            else   seed =  (b-a) % m;

        }
        else seed = ((a * (seed % q) - r * (seed /  q)) + b % m ) % m;  //递推式
    }
    if (seed >= 0) {
        ran[n-1] = (seed / (double) m);
    } else {
        ran[n-1] = ((seed + m) / (double) m);
    }
    return 0;
}





int main(int argc, const char * argv[]) {
    int N;    //总随机数个数
    double x1,x2,x3,x4,x5,x6,x7;
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    char str[50];
    printf("请输入您计算积分所需要的总点数：");
    while (!scanf("%d",&N)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您计算积分所需要的总点数：");
    }
    if(N >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");
    int seed[5];
    my_realrandom(seed,5); //读取"/dev/random"产生随机种子方便多次调用

    double *ran1 = malloc(sizeof(double) * N);  //用来存放随机数
    double *ran2 = malloc(sizeof(double) * N);  //用来存放随机数
    double *ran3 = malloc(sizeof(double) * N);  //用来存放随机数
    double *ran4 = malloc(sizeof(double) * N);  //用来存放随机数
    double *ran5 = malloc(sizeof(double) * N);  //用来存放随机数

    my_schrage(ran1,seed[0],N);
    my_schrage(ran2,seed[1],N);
    my_schrage(ran3,seed[2],N);
    my_schrage(ran4,seed[3],N);
    my_schrage(ran5,seed[4],N);
    
    
    for(int i = 0;i < N;i++){
        x1 = 3.78834946716848*ran1[i];
        x2 = 2*ran1[i];
        x3 = 0.9*ran1[i];
        x4 = 0.8*ran2[i];
        x5 = 0.9*ran3[i];
        x6 = 2*ran4[i];
        x7 = 1.3*ran5[i];
        result1 += 3.78834946716848*sqrt(x1+sqrt(x1))/(sqrt(x1) + sqrt(sqrt(x1)))/N;  //第一个积分变换方法
        result2 += 2*sqrt(x2+sqrt(x2))/N; //第一个积分直接抽样计算法
        result3 += 1.6848*(6-pow(x3,2)-pow(x4,2)-pow(x5,2)-pow(x6,2)-pow(x7,2))/N;  //第二个积分直接抽样计算法
    }
    
    printf("the integation1-1(with transformation) is %lf,the difference is %lf\n",result1,fabs(result1-2.689521));   //第一个积分变换方法
    printf("the integation1-2 is %lf,the difference is %lf\n",result2,fabs(result2-2.689521));  //第一个积分直接抽样计算法
    printf("the integation2-1 is %lf,the difference is %lf\n",result3,fabs(result3-5.64408));  //第二个积分直接抽样计算法
    return 0;
}
