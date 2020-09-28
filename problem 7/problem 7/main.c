//
//  main.c
//  problem 7
//
//  Created by 杨旭鹏 on 2019/9/24.
//  Copyright © 2019 杨旭鹏. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define a 16807
#define m 2147483647
#define b 0
#define r (m%a)
#define q (m/a)
#define k 114 //能量取值个数

//写文件子程序，输入写成文件名称字符串str，数据来源于数组num，数据总数n
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


//写文件子程序，输入写成文件名称字符串str，数据来源于数组num，数据总数n
int my_filewriter_int(char str[],int num[],int n){
    FILE * fp;
    fp = fopen(str,"w+");

    for(int i=0;i<(n-1);i++)
    {
        fprintf(fp,"%d,",num[i]);

    }
    fprintf(fp,"%d",num[n-1]);    //最后一个数据后不加 ","
    fclose(fp);
    return 0;
}





int my_filereader_int(char str[],int num[],int n){
    FILE * fp;
    int N = 0;
    
    if ((fp = fopen(str, "r")) == NULL) {
        printf("Have problem with opening the data file!\n");
        return 1;
    }
    
    int x;
    char buff[20];
    fgets(buff,20, fp); //先读取第一行表头

    for(int i=0;i<n;i++)
    {
        fscanf(fp,"%d",&x);
        fscanf(fp,"%d",&num[i]);
        N += num[i];
    }
    fclose(fp);
    return N;
}



// 16807 之 Schrage 方法产生随机数
int my_schrage(double ran[],int seed,int n){
    for (int i = 0; i < n - 1; i++) {
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
    }
    if (seed >= 0) {
        ran[n-1] = seed / (double) m;
    } else {
        ran[n-1] = (seed + m) / (double) m;
    }
    return 0;
}




// 舍选法抽样
int  my_choose(int seed[], int ran[],double orip[], int n){
    double x;
    double y;
    int flag = 0;  //记录总抽样次数
    for (int j = 0; j <= n; ) {  //j记录舍选成功的次数
        flag++;
        
        if (seed[0] >= 0) {   //产生在[0,2,4199]间均匀抽取的\xi
            x =  2.41994*(seed[0] / (double)m) ;
        }
        else{
            x = 2.41994*((seed[0] + m) / (double)m) ;
        }
        
        if (seed[1] >= 0) {   //产生在[0,1]间均匀抽取的\eta
            y =  (seed[1] / (double)m);
        }
        else{
            y =  ((seed[1] + m) / (double)m);
        }
        if(x <= 1.3536) {   //对于不同区级的\xi对x,y分别赋值
            x = x/0.0144 + 2900;
            y = y*0.0144;
        }
        else if(x <= 2.3997 && x > 1.3536) {
            x = (x-1.3536)/0.0951 + 2994;
            y = y*0.0951;
        }
        else {
            x = (x-2.3997)/0.00253 + 3005;
            y = y*0.00253;
        }
        
        if( y <= orip[(int)floor(x-2900)] ){ //舍选条件判断
           j++;
           ran[j] = (int)floor(x);
        }//满足舍选法条件后写入数据
        seed[0] = ((a * (seed[0] % q) - r * (seed[0] /  q)) + b % m ) % m;
        seed[1] = ((a * (seed[1] % q) - r * (seed[1] /  q)) + b % m ) % m;
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
    }
    return flag;
}






int main(int argc, const char * argv[]) {
    int x[k];
    double p[k];  //存放给定数据的的不同x对应的抽到的概率
    double E[k];  //存放抽样得到的数据的不同x对应的抽到的概率
    int flag;  //舍选法总抽样次数
    int seed[2] = {34028207,1677078722};   //舍选法利用的16807方法所需的初始2种子
    for(int i=0;i<k;i++){  //初始化
        E[i] = 0;
    }
    int N;   //给定数据的计数总数
    N = my_filereader_int("data.txt", x, k);
    for(int i=0;i<k;i++){
        p[i] = (double)x[i]/N;
    }
    my_filewriter_double("orip.txt", p, k);  //输出给定数据的的不同x对应的抽到的概率
    
    
    char str[50];
    printf("请输入您所需要的总点数：");
    while (!scanf("%d",&N)) {   //简单的输入检查，此时N变为需要产生的随机点的总数
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总点数：");
    }
    if(N >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");

    int *ran1 = malloc(sizeof(int) * N);  //用来存放舍选法产生的随机数
   
    flag = my_choose(seed, ran1, p, N);
    //my_filewriter_double("ran1,dat",ran1,N);  //可以输出舍选法抽样得到的数据，此处只计算得到数据的概率分布，故输出略去。
    
    for(int i = 0;i < N;i++){
        E[(int)floor(ran1[i]-2900)] += (double)1/N; //得到离散的x的取值
    }
    
    my_filewriter_double("p-1.txt", E, k);  //输出舍选法得到的数据的概率分布至文件
    printf("舍选法的抽样效率约为%lf\n",(double)N/flag);
    
    
    double * ran2 = malloc(sizeof(double) * N);  //直接抽样法所用的数据存放数组
    
    my_schrage(ran2, 1, N); //种子值设为1   //得到[0，1]均匀抽样的数据点
    
    for(int i=0;i<k;i++){  //初始化
        E[i] = 0;
    }
    
    for(int i=0;i<N;i++){   //离散数据的直接抽样法
        double sump = 0;
        for (int j=0;j<k;j++){
            sump += p[j];
            if(ran2[i] < sump) {
                ran2[i] = j + 2900;
                E[j] += (double)1/N;
                break;
            }
        }
    }
    
    //my_filewriter_double("ran2.dat",ran2,N);  //可以输出直接抽样法抽样得到的数据，此处只计算得到数据的概率分布，故输出略去。
    my_filewriter_double("p-2.txt", E, k);
    
    return 0;
}
