//
//  main.c
//  problem 12
//
//  Created by Joey on 2019/10/27.
//  Copyright © 2019 杨旭鹏. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define Pi 3.1415926535

int my_filewriter_double(char str1[],char str2[],double num[],double y,int n){
    FILE * fp;
    char str[20];
    strcpy(str,str1);
    strcat(str,str2);
    fp = fopen(str,"a+");

    for(int i=0;i<(n);i++)
    {
        fprintf(fp,"%.9lf,%.8lf\n",y,num[i]);

    }
    fclose(fp);
    return 0;
}



int my_fiter(double x[],int N,int n,double y,double x0){
    double temp = x0;  //迭代初值
    for(int i =0;i<N-n;i++){
        temp = y*sin(Pi*temp);
    }
    
    for(int i =0;i<n;i++){  //要输出的结果进行幅值
        temp = y*sin(Pi*temp);
        x[i] = temp;
    }
    
    return 0;
}



int main(int argc, const char * argv[]) {
    double min = 0.86469418;  //lambda的最小值
    double max = 0.86469419;   //lambda的最大值
    int N = 1000000;   //迭代次数
    int n = 100;   //输出迭代结果的后多少个结果
    double step = 0.000000001;  //不同lambda之间的间隔
    
    double *x = malloc(sizeof(double)*n);
    remove("x.dat");
    
    for(double y = min;y < max + (step/(double)2);y += step){ //y为迭代参数lambda
        my_fiter(x, N, n, y, 15);  //迭代初值选为15
        my_filewriter_double("", "x.dat", x, y, n);
    }
    
    return 0;
}
