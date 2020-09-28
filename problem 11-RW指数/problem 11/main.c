//
//  main.c
//  problem 11
//
//  Created by Joey on 2019/10/27.
//  Copyright © 2019 杨旭鹏. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define a 16807
#define b 0
#define m 2147483647
#define r (m%a)
#define q (m/a)
#define Pi 3.1415926
#define round(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))


//利用/dev/random 产生"真"随机数
int my_realrandom(int ran[],int n){
    FILE *fp1 = fopen("/dev/random","r");
    for(int i=0;i<n;i++){
        fread(&ran[i], 1, 4, fp1);
    }
    fclose(fp1);
    return 0;
}



int my_filewriter_double(char str1[],char str2[],double num,int flag){
    FILE * fp;
    char str[20];
    strcpy(str,str1);
    strcat(str,str2);
    fp = fopen(str,"a+");

    if(flag == 1) fprintf(fp,"%lf",num);    //最后一个数据后不加 ","
    else fprintf(fp,"%lf,",num);
    
    fclose(fp);
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

int num2str(char str[],int num){
    int  n, i = 0;
    char tmp[20];
    n = num % 10;
    while (n>0 || num > 0)
    {
        tmp[i++] = n + '0';
        num = (num - n) / 10;
        n = num % 10;
    }
    tmp[i] = '\0';
    for (i=0; i<=strlen(tmp)-1; i++)
    {
        str[i] = tmp[strlen(tmp)-i-1];
    }
    str[i] = '\0';
    return 0;
}



// Schrage 方法RW
int my_schrage_1DRW(double ran[],int N,int x[]){ //一维随机行走
    for(int i =0;i<3;i++){ //位置坐标初始化
        x[i] = 0;
    }
    
    for (int i = 0; i < N; i++) {
        if (ran[i] < 0.5) x[0] += -1;
        else x[0] += 1;
    }
    return 0;
}


int my_schrage_2DRW(double ran[],int N,int x[]){ //二维随机行走
    for(int i =0;i<3;i++){ //位置坐标初始化
        x[i] = 0;
    }
    
    for (int i = 0; i < N; i++) {
        if (ran[i] < 0.25) x[0] -= 1;
        else if((ran[i] < 0.5) && (ran[i] >= 0.25)) x[0] += 1;
        else if((ran[i] < 0.75) && (ran[i] >= 0.5)) x[1] -= 1;
        else x[1] += 1;
    }
    return 0;
}

int my_schrage_3DRW(double ran[],int N,int x[]){   //三维随机行走
    for(int i =0;i<3;i++){ //位置坐标初始化
        x[i] = 0;
    }
    
    for (int i = 0; i < N; i++) {
        if (ran[i] < (double)1/6 ) x[0] -= 1;
        else if(ran[i] < (double)1/3 && ran[i] >= (double)1/6) x[0] += 1;
        else if(ran[i] < (double)1/2 && ran[i] >= (double)1/3) x[1] -= 1;
        else if(ran[i] < (double)2/3 && ran[i] >= (double)1/2) x[1] += 1;
        else if(ran[i] < (double)5/6 && ran[i] >= (double)2/3) x[2] -= 1;
        else x[2] += 1;
    }
    return 0;
}


int main(int argc, const char * argv[]) {
    int N;    //步长最大值
    int n;    //总粒子个数
    char str[50];
    printf("请输入您所需要的步数最大值：");
    while (!scanf("%d",&N)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的步数最大值：");
    }
    
    printf("请输入您所需总粒子个数：");
    while (!scanf("%d",&n)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总粒子个数：");
    }
    
    if(N*n >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");

    double *ran = malloc(sizeof(double) * N);  //用来存放每个粒子每一步的位置
    int *seed = malloc(sizeof(int) * n);  //用来存放随机种子值
    double p[3]; //存放3个维度返回原点的概率
    int x[3];   //存放粒子最后的坐标值
    
    my_realrandom(seed, n);  //产生随机种子
    
    char str1[10];
    int flag = 0;  //是否为最后一个数据(j=N)的标志
    num2str(str1, N);
    
    for(int j = 1; j<=N ;j++){  //j为步数
        
        for(int i = 0;i<3;i++){  //概率初始化置零
            p[i] = 0;
        }
        
        for(int i=0;i<n;i++){  //i为粒子个数
            my_schrage(ran, seed[i], j);
            my_schrage_1DRW(ran, j, x);
            if(x[0] == 0) p[0] += (double) 1/n;
            my_schrage_2DRW(ran, j, x);
            if((x[0] == 0) && (x[1] == 0) ) p[1] += (double) 1/n;
            my_schrage_3DRW(ran, j, x);
            if(x[0] == 0 && x[1] == 0 && x[2] == 0 ) p[2] += (double) 1/n;
        }
        if (j == N) flag = 1;
        my_filewriter_double(str1, "step-1p.txt", p[0], flag);
        my_filewriter_double(str1, "step-2p.txt", p[1], flag);
        my_filewriter_double(str1, "step-3p.txt", p[2], flag);
    }
    
        
    return 0;
}
