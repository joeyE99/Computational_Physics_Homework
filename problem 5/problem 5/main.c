//
//  main.c
//  problem 4
//
//  Created by 杨旭鹏 on 2019/9/18.
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



int my_filereader_int(char str[],int num[],int n){
    FILE * fp;
    fp = fopen(str,"r");
    
    for(int i=0;i<n-1;i++)
    {
        fscanf(fp,"%d,",&num[i]);
        
    }
    fscanf(fp,"%d",&num[n-1]);    //最后一个数据后不加 ","
    fclose(fp);
    return 0;
}

int my_filewriter(char str[],double num[],int n){
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




int  my_marsaglia_16807_sphere(int seed[],double ranu[],double ranv[],int n){
    for (int j = 0; j <= n; ) {
        if(seed[0] == m-1){
            if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                seed[0] = m + (b-a) % m;
            }
            else   seed[0] =  (b-a) % m;
            
        }
        if(seed[1] == m-1){
            if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                seed[1] = m + (b-a) % m;
            }
            else   seed[1] =  (b-a) % m;
            
        }
        seed[0] = ((a * (seed[0] % q) - r * (seed[0] /  q)) + b % m ) % m;
        seed[1] = ((a * (seed[1] % q) - r * (seed[1] /  q)) + b % m ) % m;
        if (seed[0] >= 0) {
            ranu[j] =  2*(seed[0] / (double)m) -1;
        }
        else{
            ranu[j] = 2*((seed[0] + m) / (double)m)-1 ;
        }
        
        if (seed[1] >= 0) {
            ranv[j] =  2*(seed[1] / (double)m)-1;
        }
        else{
            ranv[j] =  2*((seed[1] + m) / (double)m)-1;
        }
        if( pow(ranu[j],2) + pow(ranv[j],2) < 1 ) j++; //第j+1个元素满足舍选法条件后可继续向后写入数据，否则下一循环重新覆盖此数据
    }
    return 0;
}




//Fibonacci延迟器
int my_fibonacci_sphere(double ranu[],double ranv[],int ranI1[],int ranI2[],int n,int o,int p){
    int temp1;
    int temp2;
    int j = 0;
    for (int i = p; j < n; i++) {   //ranI[i % p]存放的为第i项
        
        temp1 = ranI1[i % p] - ranI1[(i % p+(p-o)) % p];  //递推式
        temp2 = ranI2[i % p] - ranI2[(i % p+(p-o)) % p];  //递推式
        
        if(temp1 >= 0) ranI1[i % p] = temp1 ;
        else ranI1[i % p] = temp1 + 1;  //递推得到的新结果放入ranI中i%p一项
        
        if(temp2 >= 0) ranI2[i % p] = temp2 ;
        else ranI2[i % p] = temp2 + 1;  //递推得到的新结果放入ranI中i%p一项
        
        if (ranI1[i % p] >= 0) {   //计算ran
            ranu[j] = 2*(ranI1[i % p] / (double) m)-1;
        } else {
            ranu[j] = 2*((ranI1[i % p] + m) / (double) m)-1;
        }
        
        if (ranI2[i % p] >= 0) {   //计算ran
            ranv[j] = 2*(ranI2[i % p] / (double) m)-1;
        } else {
            ranv[j] = 2*((ranI2[i % p] + m) / (double) m)-1;
        }
        
        if ( pow(ranu[j],2) + pow(ranv[j],2) < 1 ){
            j++;
        }
        
    }
    return 0;
}



int my_count(double ranx[],double rany[],double nk[][51],int n,int k){
    int x;
    int y;
    
for(int j=0;j<=k;j++){
    for(int e=0;e<=k;e++){
        nk[j][e] = 0;    //初始化数组
    }

}
for(int i=0;i<n;i++) {//计算各个实际频数
    x = floor((ranx[i]+1)/2*k);
    y = floor((rany[i]+1)/2*k);
    nk[x][y] += (double)1/n;
}
    return 0;
}




int main() {
    int N;  //产生总点数
    char str[50];
    printf("请输入您所需要的总点数：");
    while (!scanf("%d",&N)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总点数：");
    }
    
    int o,p;
inputpq:printf("请输入Marsaglia方法的延迟整数对[p,q](建议输入97,33)(英文逗号隔开)：");
    while (!scanf("%d,%d",&o,&p)) {   //相对简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入Marsaglia方法的延迟整数对[p,q](建议值97,33)(英文逗号隔开)：");
    }
    
    
    int temp;
    if(o > p){    //使 p > o
        temp = o;
        o = p;
        p=temp;
    }
    if( N-p < 3 ) {    //排除N相对于p,q太小的情况发生
        printf("输入的p,q值相对于总点数太大了，请重试!\n");
        goto inputpq;
    }

    
    if(N > 100000) printf("您输入的参数已接受，正在计算请稍后~\n");
    
    int seed[2] = {34028207,1677078722};
    
    double * ranu = malloc(sizeof(double)*(N+1));
    double * ranv = malloc(sizeof(double)*(N+1));
    double * ranx = malloc(sizeof(double)*N);
    double * rany = malloc(sizeof(double)*N);
    double * ranz = malloc(sizeof(double)*N);
    
    my_marsaglia_16807_sphere(seed, ranu, ranv, N);
    
    for (int i = 0;i<N;i++){  //计算x,y,z坐标值
        ranx[i] = 2*ranu[i]*pow(1-pow(ranu[i],2)-pow(ranv[i],2),0.5);
        rany[i] = 2*ranv[i]*pow(1-pow(ranu[i],2)-pow(ranv[i],2),0.5);
        ranz[i] = 1 - 2*( pow(ranu[i],2) + pow(ranv[i],2) );
    }
    
    double nk[51][51];
    my_count(ranx,rany,nk,N,50);  //统计在(x,y)平面上的y投影的分布，将[-1,1]*[-1,1]区间剖分为50*50个小区间统计
    
    FILE * fp;
    fp = fopen("hist.txt","w+");  //存放在(x,y)平面上的投影的分布
    
    for(int i=0;i<50;i++){   //统计16807方法产生的点在(x,y)平面上的投影的分布
        for(int j=0;j<50;j++){
            if( i==49 && j==49 ){
                fprintf(fp,"%lf",nk[j][i]);
                break;
            }
            fprintf(fp,"%lf ",nk[j][i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    
    
    my_filewriter("ranx_16807.dat", ranx, N);
    my_filewriter("rany_16807.dat", rany, N);
    my_filewriter("ranz_16807.dat", ranz, N);
    /*    还可利用fibonacci产生器产生随机数方法抽样，此处略去
    int *ranI1 = malloc(sizeof(int) * p);      //用来存放递推数列
    int *ranI2 = malloc(sizeof(int) * p);
    my_filereader_int("ranI-1.txt",ranI1,p);   //读取之前利用"/dev/random"产生的初始随机数组
    my_filereader_int("ranI-2.txt",ranI2,p);
   
    my_fibonacci_sphere(ranu,ranv,ranI1,ranI2,N+1,o,p);
    for (int i = 0;i<N;i++){
        ranx[i] = 2*ranu[i]*pow(1-pow(ranu[i],2)-pow(ranv[i],2),0.5);
        rany[i] = 2*ranv[i]*pow(1-pow(ranu[i],2)-pow(ranv[i],2),0.5);
        ranz[i] = 1 - 2*( pow(ranu[i],2) + pow(ranv[i],2) );
    }

    my_filewriter("ranx_fibo.dat", ranx, N);
    my_filewriter("rany_fibo.dat", rany, N);
    my_filewriter("ranz_fibo.dat", ranz, N);
   */
    return 0;
}
