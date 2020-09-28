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
    srand((unsigned) time(&t));
    double x = 10;   //起始点的(x,y)坐标
    double y = 10;
    double sigmax = 1;   //sigmax,sigmay的值
    double sigmay = 1;
    double dE;   //能量差
    double dx,dy;  //坐标x,y某一步的该变量
    double delta = 50; //每一步的步长范围在[-delta,delat]之间
    double flag;
    int N = 1000000;   //总步数
    int n = 1500;    //计算统计量删去起始点数的个数
    double avgx2 = 0;   //计算产生数据点的<x^2>
    double avgy2 = 0;   //计算产生数据点的<y^2>
    double avgsum = 0;  //计算产生数据点的<x^2+y^2>
    
    double *positionx = malloc(sizeof(double)*N);  //存放markov链的节点坐标数组
    double *positiony = malloc(sizeof(double)*N);
    
    
    for(int i=0;i<N;){
        dx = 2*delta*rand()/(double)RAND_MAX-delta;
        dy = 2*delta*rand()/(double)RAND_MAX-delta;
           
        dE = ( pow(x+dx,2)-pow(x,2) )/(2*sigmax) + ( pow(y+dy,2)-pow(y,2) )/(2*sigmay);
        if(dE<0){
            x += dx;
            y += dy;
            positionx[i] = x;
            positiony[i] = y;
            i++;
        }
        else{
            flag = rand()/(double)RAND_MAX;
            if(flag < exp(-dE) ){
                x += dx;
                y += dy;
            }
            positionx[i] = x;
            positiony[i] = y;
            i++;
        }
    }
    
    my_filewriter("x.dat", positionx, N);
    my_filewriter("y.dat", positiony, N);
      
    if(n >= N){   //参数检查
        printf("Parameters wrong!!\n");
        return 0;
    }
    
    for(int i = n-1;i<N;i++){   //计算统计量
        avgx2 += pow(positionx[i],2)/(double)(N-n);
        avgy2 += pow(positiony[i],2)/(double)(N-n);
    }
    avgsum = avgx2 + avgy2;
    printf("average of x2 is:%.5lf\n",avgx2);
    printf("average of y2 is:%.5lf\n",avgy2);
    printf("average of x2+y2 is:%.5lf\n",avgsum);
    
   
    
    return 0;
}
