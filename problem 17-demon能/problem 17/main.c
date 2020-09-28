#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define a 16807
#define b 0
#define m 2147483647
#define r (m%a)
#define q (m/a)


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



int main(int argc, const char * argv[]) {
    time_t t;
    srand((unsigned) time(&t));  //给随机函数赋种子值
    int n = 10000;    //一维粒子的总个数
    double *v = malloc(sizeof(double)*n);   //一维粒子的速度数组
    double dE;   //能量差
    double dv;  //某一步对某一粒子速度的改变量
    double delta = 0.01; //每一步每一粒子速度的改变范围在[-delta,delat]之间
    int N = 10000000;   //总步数
    int i;   //粒子的标号
    int flag = 0;
    int flag2 = 0;
    int step = 1000;  //计算粒子平均温度与Ed的步数间隔
    
    double *T = malloc(sizeof(double)*N/step + 1);   //不同步数的一维粒子温度
    double *Td = malloc(sizeof(double)*N/step + 1);  //不同步数的demon能
    double Ed = 0;   //demon能初值为0
 
    for(int j =0;j<N/step;j++){
        T[j] = 0;
    }
    
    for(int j = 0;j<n;j++){
        v[j] = 2*(double)rand()/RAND_MAX - 1;   //粒子速度初始化
    }
    
    
    for(int k = 0;k<n;k++){  //计算模拟后的系统平均温度
        T[0] += pow( v[k],2 )/n;
    }
    Td[0] = 0;
    flag++;
    
    
    for(int j = 0;j<N;){
        i = rand() % n;
        dv = 2*delta*rand()/(double)RAND_MAX-delta;
           
        dE = 0.5*( pow(v[i]+dv,2)-pow(v[i],2) );
        if(dE<0){
            v[i] += dv;
            Ed -= dE;
            j++;
        }
        else{
            if(Ed >= dE){
                v[i] += dv;
                Ed -= dE;
                j++;
            }
        }
        if(j % step == 0 && j != 0 && j!= flag2){  //当步数差了step步时计算T,flag2为判断是否与上步相同的标志
            flag2 = j;
            for(int k = 0;k<n;k++){  //计算模拟后的系统平均温度
                T[flag] += pow( v[k],2 )/n;
            }
            Td[flag] = Ed;
            flag++;
        }
    }
    
    my_filewriter("v.dat", v, n);
    my_filewriter("T.dat", T, N/step + 1);
    my_filewriter("Ed.dat", Td, N/step + 1);
    
    return 0;
}

