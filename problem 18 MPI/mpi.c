#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define GETMATELEM(base,i,j,imax) ((*(base + (i) * (imax) + (j)))) //取二维数组元素



int matrixform(float *matrix,int m,int n){  //打印矩阵的函数
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%.3f\t", GETMATELEM(matrix,i,j,n) );
        }
        printf("\n");
    }
    return 0;
}




int main(int argc, char* argv[]){
    
    int m;  //求最大值的矩阵元行位置
    int n;  //求最大值的矩阵元列位置
    float *max1 = malloc(sizeof(float)*100); //利用集合通信求得的最大值矩阵
    float *max2 = malloc(sizeof(float)*100); //利用点对点通信求得的最大值矩阵
    int flag = 0; //打印矩阵的标志
    int one = 1;  //值为 （int） 1 的变量
    
    int numprocs, myid, source;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    
    float *max2temp = malloc(sizeof(float)*numprocs);  //点对点通信时比较大小所用的临时数组
    unsigned int seed[numprocs];  //随机种子数组
    
    if(myid == 0){
        
        time_t t;
        srand((unsigned) time(&t));
        int i;
        for(i=0;i < numprocs;i++){  //种子初始化
            seed[i] = rand();
        }
        srand(seed[myid]);
        flag = 1;
        
    }
    
    MPI_Bcast(seed, numprocs, MPI_UNSIGNED, 0, MPI_COMM_WORLD);  //广播主进程求得的随机种子数组
   
    srand(seed[myid]);          //对不同进程赋不同的随机种子
    float *matrix = malloc(sizeof(float)*100);       //为每一个进程定义随机矩阵
    int j,k;
    for(j=0;j<10;j++){      //对随机矩阵赋值
        for(k=0;k<10;k++){
            GETMATELEM(matrix,j,k,10) = rand()/(float)RAND_MAX;  //矩阵元为（0，1）随机f单精度浮点数
        }
    }
    
    
    if(myid != 0){
        MPI_Recv(&flag, 1, MPI_INT, myid -1 , 1, MPI_COMM_WORLD, &status);//接受上一个进程传入的打印矩阵flag参数
    }
    
    
    if(flag != 0){   //若打印flag不为0，则执行打印矩阵命令
        printf("进程号:%d的随机矩阵为:\n",myid);
        matrixform(matrix,10,10);
        if(myid < numprocs -1){
            MPI_Send(&one, 1, MPI_INT, myid + 1, 1, MPI_COMM_WORLD);  //向下一个进程传入的打印矩阵flag参数
        }
    }
   
        
    
    for(m=0;m<10;m++){   //对矩阵行元素循环
           for(n=0;n<10;n++){  //对矩阵列元素循环
               MPI_Reduce(&GETMATELEM(matrix,m,n,10), &GETMATELEM(max1,m,n,10), 1, MPI_FLOAT, MPI_MAX, numprocs-1, MPI_COMM_WORLD); //集合通信求最大值矩阵
               
               if(myid != numprocs -1){
                   MPI_Send(&GETMATELEM(matrix,m,n,10), 1, MPI_FLOAT, numprocs -1, myid+10, MPI_COMM_WORLD); // 点对点通信
               }
               
               if(myid == numprocs-1){  //最后一个进程中利用点对点通信求最大值
                   int i;
                   GETMATELEM(max2,m,n,10) = GETMATELEM(matrix,m,n,10);
                   for(i = 0;i<numprocs-1;i++){    //点对点接受然后求最大值
                        MPI_Recv(&max2temp[i], 1, MPI_FLOAT, i, i+10, MPI_COMM_WORLD, &status);
                        if(max2temp[i] > GETMATELEM(max2,m,n,10) ){
                            GETMATELEM(max2,m,n,10) = max2temp[i];
                        }
                    }
                   
               }
           }
       }
     
    
    if(myid == numprocs-1){  //最后一个进程打印最大值矩阵
        printf("集合通信:\n");
        matrixform(max1,10,10);
        printf("点对点通信:\n");
        matrixform(max2,10,10);
    }
        
    MPI_Finalize();
}
