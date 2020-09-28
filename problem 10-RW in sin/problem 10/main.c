//
//  main.c
//  problem 10
//
//  Created by Joey on 2019/10/19.
//  Copyright © 2019 杨旭鹏. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define a 16807
#define b 0
#define m 2147483647
#define r (m%a)
#define q (m/a)
#define Pi 3.1415926
#define dt 0.1 //每步间隔时间
#define k 1 //影响因子的大小
#define w 100 //正弦力场的角速度大小
#define len 100  //统计概率分布时的统计范围
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



int my_filewriter_double(char str1[],char str2[],double num[],int n){
    FILE * fp;
    char str[20];
    strcpy(str,str1);
    strcat(str,str2);
    fp = fopen(str,"w+");

    for(int i=0;i<(n-1);i++)
    {
        fprintf(fp,"%lf,",num[i]);

    }
    fprintf(fp,"%lf",num[n-1]);    //最后一个数据后不加 ","
    fclose(fp);
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
int my_schrage_RW(double ran[],double evenx[],double evenx2[],int seed,int n,int x){
    if (seed >= 0) {
        ran[0] = seed / (double) m;
    } else {
        ran[0] = (seed + m) / (double) m;
    }
    if(seed == m-1){
        if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
            seed = m + (b-a) % m;
        }
        else   seed =  (b-a) % m;

    }
    
    else seed = ((a * (seed % q) - r * (seed /  q)) + b % m ) % m;  //递推式
    if (ran[0] < 0.5*( 1 - k*sin(w*dt)) )
        ran[0] = -1;
    else ran[0] = 1;
    evenx[0] += ran[0]/x;
    evenx2[0] += pow(ran[0],2)/x;
   
    for (int i = 1; i < n-1; i++) {
        if (seed >= 0) {
            ran[i] = seed / (double) m;
        } else {
            ran[i] = (seed + m) / (double) m;
        }
        if(seed == m-1){
            if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                seed = m + (b-a) % m;
            }
            else   seed =  (b-a) % m;

        }
        else seed = ((a * (seed % q) - r * (seed /  q)) + b % m ) % m;  //递推式
        if (ran[i] < 0.5*( 1 - k*sin(w*(i+1)*dt)) )
            ran[i] = ran[i-1]- 1;
        else ran[i] = ran[i-1] + 1;
        evenx[i] += ran[i]/x;
        evenx2[i] += pow(ran[i],2)/x;
    }
    
    
    if (seed >= 0) {
        ran[n-1] = seed / (double) m;
    } else {
        ran[n-1] = (seed + m) / (double) m;
    }
    if (ran[n-1] < 0.5*( 1 - k*sin(w*n*dt)) )
        ran[n-1] = ran[n-2]- 1;
    else ran[n-1] = ran[n-2] + 1;
    evenx[n-1] += ran[n-1]/x;
    evenx2[n-1] += pow(ran[n-1],2)/x;
    
    return 0;
}






int main(int argc, const char * argv[]) {
    int N;    //总随机数个数(总步长k个数)
    int n;    //总粒子个数
    int flag = 0; //是否输出每个模拟粒子每步的位置数据文件
    char str[50];
    printf("请输入您所需要的总步数：");
    while (!scanf("%d",&N)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总步数：");
    }
    
    printf("请输入您所需总粒子个数：");
    while (!scanf("%d",&n)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总粒子个数：");
    }
    
    printf("是否输出每个模拟粒子的位置数据至文件？是输1，不是输0:");
    while (!scanf("%d",&flag)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("是否输出每个模拟粒子的位置数据至文件？是输1，不是输0:");
    }

    if(N*n >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");

    double *ran = malloc(sizeof(double) * N);  //用来存放每个粒子每一步的位置
    double *evenx = malloc(sizeof(double) * N);  //用来存放所有粒子每一步位置的平均值
    double *evenx2 = malloc(sizeof(double) * N);  //用来存放所有粒子每一步位置平方的平均值
    double *p = malloc(sizeof(double)*(2*len+1));
    double *var = malloc(sizeof(double)*N);
    int *seed = malloc(sizeof(int) * n);  //用来存放随机种子值
    
    my_realrandom(seed, n);
    

    for(int i=0;i<N;i++){  //对evenx进行初始化
        evenx[i] = 0;
        evenx2[i] = 0;
        var[i] = 0;
    }
    
    for(int i=0;i <= 2*len;i++){  //对evenx进行初始化
        p[i] = 0;
    }
    
    
    char str1[10];
    for(int i = 0;i<n;i++){
        num2str(str1,i+1);
        my_schrage_RW(ran,evenx,evenx2,seed[i],N,n);
        p[round(ran[N-1]) + len]  += (double)1/n;
        if(flag == 1 && n < 20 ) my_filewriter_double(str1, "RW.dat", ran, N);
    }
    num2str(str1, n);
    for(int i=0;i<N;i++){
        var[i] = (evenx2[i]-pow(evenx[i],2))/n;
    }
    my_filewriter_double(str1, "evenx.dat", evenx, N);
    my_filewriter_double(str1, "evenx2.dat", evenx2, N);
    my_filewriter_double(str1, "p.txt", p, (2*len+1));
    my_filewriter_double(str1, "var.txt", var, N);
    return 0;
}


