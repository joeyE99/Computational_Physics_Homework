//
//  main.c
//  problem 6
//
//  Created by 杨旭鹏 on 2019/9/23.
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
#define e  2.718281828
#define o 600  //统计概率所剖分区域的总数


int my_filewriter_double(char str[],double num[],int n){
    FILE * fp;
    fp = fopen(str,"w+");
    
    for(int i=0;i<n;i++)
    {
        if (i == (n-1)){
            fprintf(fp,"%lf",num[i]);
            break;
        }
        fprintf(fp,"%lf,",num[i]);
        
    }
    fclose(fp);
    return 0;
}

int my_filewriter_int(char str[],int num[],int n){
    FILE * fp;
    fp = fopen(str,"w+");
    
    for(int i=0;i<n;i++)
    {
        if (i == (n-1)){
            fprintf(fp,"%d",num[i]);
            break;
        }
        fprintf(fp,"%d,",num[i]);
        
    }
    fclose(fp);
    return 0;
}



// 舍选法抽样
int  my_choose(int seed[], double ran[], int n){
    double x;
    double y;
    double u,v;
    int flag = 0;  //记录总抽样次数
    for (int j = 0; j <= n; ) {
        flag++;
        if (seed[0] >= 0) {   //产生在[0,2,4199]间均匀抽取的\xi
            u = (seed[0] / (double)m) ;
        }
        else{
            u = ((seed[0] + m) / (double)m) ;
        }
        
        if (seed[1] >= 0) {   //产生在[0,1]间均匀抽取的\eta
            v =  2*Pi*(seed[1] / (double)m);
        }
        else{
            v =   2*Pi*((seed[1] + m) / (double)m);
        }
        if (seed[2] >= 0) {   //产生在[0,1]间均匀抽取的\eta
            y =  (seed[2] / (double)m);
        }
        else{
            y =   ((seed[2] + m) / (double)m);
        }
        
        
        x = sqrt(-2*log(u))*cos(v);
        
        if( x <= 3 && x >=-3 && y*1.1*pow(e,-x*x/2) <= (1/(1+pow(x,4))) ){ //舍选条件判断
            ran[j] = x;
            j++;
        }//满足舍选法条件后写入数据

        for(int k = 0;k<3;k++){
            if(seed[k] == m-1){
                if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                    seed[k] = m + (b-a) % m;
                }
                else   seed[k] =  (b-a) % m;
            }
            seed[k] = ((a * (seed[k] % q) - r * (seed[k] /  q)) + b % m ) % m;
        }
    }
    
    return flag;
}




int main() {
    int N;
    int flag; //记录舍选法抽样总次数
    double p[o]; //记录在每(6/o)长度的区间内点出现的概率
    
    char str[50];
    printf("请输入您所需要的总点数：");
    while (!scanf("%d",&N)) {   //简单的输入检查，此时N变为需要产生的随机点的总数
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总点数：");
    }
    if(N >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");
    for(int i = 0;i<o;i++){ //数组初始化
        p[i] = 0;
    }

    int seed[3] = {809576131,-1025892587,558213681}; //设置随机数产生器的初始种子值
    double *ran = malloc(sizeof(double) * N);  //用来存放舍选法产生的随机数
    
    flag = my_choose(seed, ran, N); //舍选法抽样
    //my_filewriter_double("ran,dat",ran,N);   可以选择输出产生的随机数至文件，由于现在只需对产生的随机数做概率统计，故此处略去输出步骤。
    
    printf("抽样效率为：%lf\n",(double)N/flag);
    int j;
    for(int i = 0;i<N;i++){  //对抽样点在每一剖分区间内出现概率进行计算
        j = (int)floor((ran[i]+3)/6*o);
        p[j] += (double)1/N;
    }
    my_filewriter_double("p.txt", p, o);  //输出抽样点在每一剖分区间内出现概率至文件

    return 0;
}
