#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define a 16807
#define b 0
#define m 2147483647
#define r (m%a)
#define q (m/a)
#include <assert.h>

/*
//利用/dev/random 产生"真"随机数
int my_realrandom(double ran[]){
    int *seed = malloc(sizeof(int)*N);
    FILE * fp1 = fopen("/dev/random","r");
    for(int i=0;i<N;i++){
        fread(&seed[i], 1, 4, fp1);
        ran[i] = (seed[i]/(double)m +1)/(double)2 ;
    }
    fclose(fp1);
    return 0;
}

 */


//利用/dev/random 产生随机种子
int my_randomseed(int seed[],int n){     //seed为存储随机种子的数据，n为所需要种子的个数
    FILE * fp1 = fopen("/dev/random","r");
    for(int i=0;i<n;i++){
        fread(&seed[i], 1, 4, fp1);
    }
    fclose(fp1);
    return 0;
}



//写文件子程序，输入写成文件名称字符串str，数据来源于数组num，数据总数n
int my_filewriter(char str[],double num[],int n){
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



//频率检验均匀性
int my_chi_square_check(double ranx[],double rany[],int n,int k){
    double x2 = 0;    //统计量
    double mk=n/(double)(k*k);   //理论频数
    printf("%f\n",mk);
    int nk[k+1][k+1];   //实际频数
    for(int j=0;j<=k;j++){
        for(int e=0;e<=k;e++){
            nk[j][e] = 0;    //初始化数组
        }

    }
    for(int i=0;i<n;i++) {    //计算各个实际频数
        assert(ranx[i] < 1);
        assert(rany[i] < 1);
        int x = floor(ranx[i]*k);
        int y = floor(rany[i]*k);
        nk[x][y]++;
    }

    for(int j=0;j<k;j++){
        for(int e=0;e<k;e++){
            x2 += (double)(nk[j][e]-mk) * (nk[j][e]-mk)/mk;    //计算统计量

            printf("%8d\t", nk[j][e]);
        }
        printf("\n");
    }
    printf("x^2=%lf\n",x2);

    return 0;
}




//线性相关检验
int my_cl_check(double ran[],int n,int l){
    double xy = 0;  //<x*y>
    double x = 0;   //<x>
    double x2 = 0;  //<x^2>
    double cl = 0;

        for(int i = 0;i<n;i++) {
            x += ran[i]/n;
            x2 += pow(ran[i], 2)/n;
        }
            for(int j=1;j <= l;j++) {
                xy = 0;
                for(int i = 0;i < (n-j);i++) {
                    xy += (ran[i] * ran[i + j])/(n-j);
                }
                cl = (xy-pow(x,2))/(x2 -pow(x,2));   //C(l)计算
                printf("所产生的 %d 个随机数的线性相关系数 C(%d) = %E\n",n,j,cl);
            }




    return 0;
}



//<x^k>测试均匀性
int my_xk_check(double ranx[],double rany[],int n,int k){
    double sumxk[k];    //sum(x^k)
    double sumyk[k];    //sum(y^k)
    for(int j = 0;j < k;j++){    //初始化数组
        sumxk[j] = 0;
        sumyk[j] = 0;
    }

    for(int i = 0;i < n;i++){     //数组赋值
        for(int j = 0;j < k;j++){
            sumxk[j] += pow(ranx[i],j+1)/n;
            sumyk[j] += pow(rany[i],j+1)/n;
        }
    }
    for(int j = 0;j < k;j++){    //计算<x^k>,<y^k>
        printf("N = %-8d <x^%d> = %lf  with theoretical number of %lf,the difference is %lf\n",n,j+1,sumxk[j],1.0/(2+j),fabs(sumxk[j]-1.0/(2+j)));
        //printf("N = %-8d <y^%d> = %lf  with theoretical number of %lf\n",n,j+1,sumyk[j],1.0/(2+j));
//此子程序还可用来计算<y^k>
    }


    return 0;
}



int main() {
    int N;    //总随机数个数，即x坐标随机数值+y坐标随机数值（即必须为偶数）
    int l;    //计算线性相关系数C(l)所需的参数l
    char str[50];
    printf("请输入您所需要的总点数：");
    while (!scanf("%d",&N)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总点数：");
    }

    printf("请输入您计算线性相关系数C(l)时参数l的最大值：");
    while (!scanf("%d",&l)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您计算线性相关系数C(l)时参数l的最大值：");
    }


    N =2 * N; //总随机数个数为点数的2倍
    if(N >2000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");

    double *ran = malloc(sizeof(double) * N);  //用来存放随机数

    my_schrage(ran,1,N); //1为种子值

    double *ranx = malloc(sizeof(double) * N/2);
    double *rany = malloc(sizeof(double) * N/2);

    for(int i=0;i<N;i=i+2){     //将ran[]中相邻的两个随机数分别赋值到ranx[]和rany[]
        ranx[i/2]=ran[i];
        rany[i/2]=ran[i+1];
    }
    my_filewriter("ranx.dat",ranx,N/2);
    my_filewriter("rany.dat",rany,N/2);
    //my_chi_square_check(ranx,rany,N/2,10);
    my_cl_check(ran,N/2,l);

    int k;
    printf("Please input the max value of k in <x^k>:");
    while (!scanf("%d",&k)) {   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("Please input the max value of k in <x^k>:");
    }
    printf("以下是<x^k>的均匀性测试:\n");
    for(int j = N/10 ;j >= 1 ;j = j/10){    //进行<x^k>均匀性测试
        my_xk_check(ranx,rany,N/j,k);
    }

    return 0;
}